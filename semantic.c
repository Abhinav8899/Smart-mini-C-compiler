#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "parser.tab.h"

/* Forward declaration */
static int loop_depth = 0;

/* Helper: map Bison token to operator string for TAC */
const char *token_op_str(int op) {
    switch (op) {
        case PLUS:  return "+";
        case MINUS: return "-";
        case MULT:  return "*";
        case DIV:   return "/";
        case MOD:   return "%";
        case EQ:    return "==";
        case NE:    return "!=";
        case LT:    return "<";
        case GT:    return ">";
        case LE:    return "<=";
        case GE:    return ">=";
        case AND:   return "&&";
        case OR:    return "||";
        default:    return "?";
    }
}

/* =========================================
   TYPE CHECKING
   ========================================= */
DataType type_check(ASTNode *node) {
    if (!node) return TYPE_UNKNOWN;

    /* Sequence / block — process in declaration order (next is older) */
    if (node->type == NODE_BLOCK) {
        type_check(node->data.seq.next);
        type_check(node->data.seq.stmt);
        return TYPE_UNKNOWN;
    }

    switch (node->type) {

        case NODE_NUM:       return TYPE_INT;
        case NODE_FLOAT_NUM: return TYPE_FLOAT;
        case NODE_BOOL_LIT:  return TYPE_BOOL;
        case NODE_STR_LIT:   return TYPE_STRING;

        case NODE_ID: {
            Symbol *sym = lookup_symbol(node->data.id_name);
            if (!sym) {
                char msg[256];
                char *suggestion = closest_symbol(node->data.id_name);
                if (suggestion)
                    snprintf(msg, sizeof(msg),
                             "Undeclared variable '%s'. Did you mean '%s'?",
                             node->data.id_name, suggestion);
                else
                    snprintf(msg, sizeof(msg),
                             "Undeclared variable '%s'.", node->data.id_name);
                report_error(node->line, node->col, msg);
                return TYPE_UNKNOWN;
            }
            return sym->type;
        }

        case NODE_DECL:
            /* Register in the semantic scope so subsequent stmts can find it */
            if (!lookup_current_scope(node->data.decl.name))
                insert_symbol(node->data.decl.name, (DataType)node->data.decl.var_type);
            return TYPE_UNKNOWN;

        case NODE_ASSIGN: {
            Symbol *sym = lookup_symbol(node->data.assign.name);
            if (!sym) {
                char msg[256];
                char *suggestion = closest_symbol(node->data.assign.name);
                if (suggestion)
                    snprintf(msg, sizeof(msg),
                             "Undeclared variable '%s'. Did you mean '%s'?",
                             node->data.assign.name, suggestion);
                else
                    snprintf(msg, sizeof(msg),
                             "Undeclared variable '%s'.", node->data.assign.name);
                report_error(node->line, node->col, msg);
                return TYPE_UNKNOWN;
            }
            DataType expr_type = type_check(node->data.assign.expr);
            if (expr_type != TYPE_UNKNOWN && sym->type != expr_type) {
                /* Allow int -> float implicit widening with warning */
                if (sym->type == TYPE_FLOAT && expr_type == TYPE_INT) {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                             "Implicit int -> float conversion for '%s'. "
                             "Consider using a cast: (float)expr.",
                             sym->name);
                    report_warning(node->line, node->col, msg);
                } else {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                             "Type mismatch: cannot assign %s value to %s variable '%s'. "
                             "Hint: declare '%s' as %s, or cast the expression.",
                             type_name(expr_type), type_name(sym->type),
                             sym->name, sym->name, type_name(expr_type));
                    report_error(node->line, node->col, msg);
                }
            }
            return TYPE_UNKNOWN;
        }

        case NODE_CAST: {
            /* Allow cast to override the inner expression type */
            type_check(node->data.cast.expr);
            return node->data.cast.target;
        }

        case NODE_BINOP: {
            DataType lt = type_check(node->data.binop.left);
            DataType rt = type_check(node->data.binop.right);
            if (lt == TYPE_UNKNOWN || rt == TYPE_UNKNOWN) return TYPE_UNKNOWN;

            int op = node->data.binop.op;

            /* Arithmetic */
            if (op == PLUS || op == MINUS || op == MULT || op == DIV || op == MOD) {
                if (lt == TYPE_STRING || rt == TYPE_STRING) {
                    if (op == PLUS && lt == TYPE_STRING && rt == TYPE_STRING)
                        return TYPE_STRING; /* string concat */
                    report_error(node->line, node->col,
                                 "Arithmetic on string type is not allowed.");
                    return TYPE_UNKNOWN;
                }
                if (lt == TYPE_BOOL || rt == TYPE_BOOL) {
                    report_error(node->line, node->col,
                                 "Arithmetic on bool type is not allowed.");
                    return TYPE_UNKNOWN;
                }
                if (lt != rt) {
                    /* Allow if either side is an explicit cast node */
                    int left_is_cast  = (node->data.binop.left  && node->data.binop.left->type  == NODE_CAST);
                    int right_is_cast = (node->data.binop.right && node->data.binop.right->type == NODE_CAST);
                    if (left_is_cast || right_is_cast) {
                        /* Use the wider type */
                        return (lt == TYPE_FLOAT || rt == TYPE_FLOAT) ? TYPE_FLOAT : lt;
                    }
                    /* Implicit int->float widening */
                    if ((lt == TYPE_INT && rt == TYPE_FLOAT) || (lt == TYPE_FLOAT && rt == TYPE_INT)) {
                        report_warning(node->line, node->col,
                            "Implicit int/float mixed arithmetic. Consider casting explicitly.");
                        return TYPE_FLOAT;
                    }
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                             "Type mismatch in arithmetic: %s vs %s. "
                             "Use a cast to make types explicit.",
                             type_name(lt), type_name(rt));
                    report_error(node->line, node->col, msg);
                    return TYPE_UNKNOWN;
                }
                return lt;
            }

            /* Relational */
            if (op == EQ || op == NE || op == LT || op == GT || op == LE || op == GE) {
                if (lt != rt) {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                             "Type mismatch in comparison: %s vs %s.",
                             type_name(lt), type_name(rt));
                    report_error(node->line, node->col, msg);
                    return TYPE_UNKNOWN;
                }
                return TYPE_BOOL;
            }

            /* Logical */
            if (op == AND || op == OR) {
                if (lt != TYPE_BOOL || rt != TYPE_BOOL) {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                             "Logical operators require bool operands, got %s and %s. "
                             "Use a comparison expression (e.g., x != 0) instead.",
                             type_name(lt), type_name(rt));
                    report_error(node->line, node->col, msg);
                    return TYPE_UNKNOWN;
                }
                return TYPE_BOOL;
            }
            return TYPE_UNKNOWN;
        }

        case NODE_NOT: {
            DataType t = type_check(node->data.single_expr.expr);
            if (t != TYPE_BOOL && t != TYPE_UNKNOWN) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "'!' operator requires bool operand, got %s.", type_name(t));
                report_error(node->line, node->col, msg);
            }
            return TYPE_BOOL;
        }

        case NODE_NEG: {
            DataType t = type_check(node->data.single_expr.expr);
            if (t == TYPE_BOOL || t == TYPE_STRING) {
                report_error(node->line, node->col,
                             "Unary minus not applicable to bool or string.");
                return TYPE_UNKNOWN;
            }
            return t;
        }

        case NODE_PRINT:
            type_check(node->data.single_expr.expr);
            return TYPE_UNKNOWN;

        case NODE_RETURN: {
            /* Return type checking is done inside NODE_FUNC_DECL */
            type_check(node->data.single_expr.expr);
            return TYPE_UNKNOWN;
        }

        case NODE_IF:
        case NODE_WHILE: {
            ASTNode *cond = (node->type == NODE_IF)
                            ? node->data.if_stmt.cond
                            : node->data.while_stmt.cond;
            DataType ct = type_check(cond);
            if (ct != TYPE_BOOL && ct != TYPE_UNKNOWN) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "Condition must be bool, got %s. "
                         "Hint: use a comparison, e.g., 'x != 0'.", type_name(ct));
                report_error(node->line, node->col, msg);
            }
            if (node->type == NODE_WHILE) {
                loop_depth++;
                type_check(node->data.while_stmt.body);
                loop_depth--;
            } else {
                type_check(node->data.if_stmt.if_body);
                if (node->data.if_stmt.else_body)
                    type_check(node->data.if_stmt.else_body);
            }
            return TYPE_UNKNOWN;
        }

        case NODE_FOR: {
            type_check(node->data.for_stmt.init_expr);
            DataType ct = type_check(node->data.for_stmt.cond);
            if (ct != TYPE_BOOL && ct != TYPE_UNKNOWN) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "FOR condition must be bool, got %s.", type_name(ct));
                report_error(node->line, node->col, msg);
            }
            loop_depth++;
            type_check(node->data.for_stmt.inc_expr);
            type_check(node->data.for_stmt.body);
            loop_depth--;
            return TYPE_UNKNOWN;
        }

        case NODE_FUNC_DECL: {
            /* Re-push scope with params for semantic analysis pass */
            push_scope();
            ParamList *p = node->data.func_decl.params;
            while (p) { insert_symbol(p->name, p->type); p = p->next; }
            type_check(node->data.func_decl.body);
            pop_scope();
            return TYPE_UNKNOWN;
        }

        case NODE_FUNC_CALL: {
            Symbol *sym = lookup_symbol(node->data.func_call.name);
            if (!sym) {
                char msg[256];
                char *suggestion = closest_symbol(node->data.func_call.name);
                if (suggestion)
                    snprintf(msg, sizeof(msg),
                             "Undeclared function '%s'. Did you mean '%s'?",
                             node->data.func_call.name, suggestion);
                else
                    snprintf(msg, sizeof(msg),
                             "Undeclared function '%s'.", node->data.func_call.name);
                report_error(node->line, node->col, msg);
                return TYPE_UNKNOWN;
            }
            /* Check arg count */
            ExprList *a = node->data.func_call.args;
            int argc = 0;
            while (a) { argc++; a = a->next; }
            if (argc != sym->param_count) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                         "Function '%s' expects %d argument(s), got %d.",
                         sym->name, sym->param_count, argc);
                report_error(node->line, node->col, msg);
            }
            /* Check arg types */
            a = node->data.func_call.args;
            for (int i = 0; i < sym->param_count && a; i++, a = a->next) {
                DataType at = type_check(a->expr);
                if (at != TYPE_UNKNOWN && at != sym->param_types[i]) {
                    char msg[256];
                    snprintf(msg, sizeof(msg),
                             "Argument %d of '%s': expected %s, got %s.",
                             i + 1, sym->name,
                             type_name(sym->param_types[i]), type_name(at));
                    report_error(node->line, node->col, msg);
                }
            }
            return sym->type;
        }

        case NODE_BREAK:
        case NODE_CONTINUE:
            return TYPE_UNKNOWN;

        case NODE_ARRAY_DECL:
            if (!lookup_current_scope(node->data.arr_decl.name))
                insert_array_symbol(node->data.arr_decl.name,
                                    node->data.arr_decl.elem_type,
                                    node->data.arr_decl.size);
            return TYPE_UNKNOWN;

        case NODE_ARRAY_ACCESS: {
            Symbol *sym = lookup_symbol(node->data.arr_access.name);
            if (!sym) {
                char msg[256];
                char *sug = closest_symbol(node->data.arr_access.name);
                if (sug) snprintf(msg, sizeof(msg),
                    "Undeclared array '%s'. Did you mean '%s'?",
                    node->data.arr_access.name, sug);
                else snprintf(msg, sizeof(msg),
                    "Undeclared array '%s'.", node->data.arr_access.name);
                report_error(node->line, node->col, msg);
                return TYPE_UNKNOWN;
            }
            DataType idx_type = type_check(node->data.arr_access.index);
            if (idx_type != TYPE_INT && idx_type != TYPE_UNKNOWN) {
                report_error(node->line, node->col,
                    "Array index must be int.");
            }
            return sym->type;
        }

        case NODE_ARRAY_ASSIGN: {
            Symbol *sym = lookup_symbol(node->data.arr_assign.name);
            if (!sym) {
                char msg[256];
                char *sug = closest_symbol(node->data.arr_assign.name);
                if (sug) snprintf(msg, sizeof(msg),
                    "Undeclared array '%s'. Did you mean '%s'?",
                    node->data.arr_assign.name, sug);
                else snprintf(msg, sizeof(msg),
                    "Undeclared array '%s'.", node->data.arr_assign.name);
                report_error(node->line, node->col, msg);
                return TYPE_UNKNOWN;
            }
            type_check(node->data.arr_assign.index);
            DataType et = type_check(node->data.arr_assign.expr);
            if (et != TYPE_UNKNOWN && et != sym->type) {
                char msg[256];
                snprintf(msg, sizeof(msg),
                    "Array '%s' has element type %s, cannot assign %s.",
                    sym->name, type_name(sym->type), type_name(et));
                report_error(node->line, node->col, msg);
            }
            return TYPE_UNKNOWN;
        }

        case NODE_DO_WHILE: {
            loop_depth++;
            type_check(node->data.do_while.body);
            loop_depth--;
            DataType ct = type_check(node->data.do_while.cond);
            if (ct != TYPE_BOOL && ct != TYPE_UNKNOWN) {
                report_error(node->line, node->col,
                    "do-while condition must be bool.");
            }
            return TYPE_UNKNOWN;
        }

        case NODE_SWITCH: {
            type_check(node->data.sw.expr);
            ASTNode *c = node->data.sw.cases;
            while (c) {
                if (!c->data.cas.is_default)
                    type_check(c->data.cas.val);
                type_check(c->data.cas.body);
                c = c->data.cas.next_case;
            }
            return TYPE_UNKNOWN;
        }

        default:
            return TYPE_UNKNOWN;
    }
}

/* =========================================
   CONSTANT FOLDING
   ========================================= */
ASTNode *constant_fold(ASTNode *node) {
    if (!node) return NULL;

    /* Recursively fold children first */
    if (node->type == NODE_BLOCK) {
        node->data.seq.next = constant_fold(node->data.seq.next);
        node->data.seq.stmt = constant_fold(node->data.seq.stmt);
        return node;
    }

    switch (node->type) {
        case NODE_ASSIGN:
            node->data.assign.expr = constant_fold(node->data.assign.expr);
            return node;

        case NODE_PRINT:
        case NODE_RETURN:
            node->data.single_expr.expr = constant_fold(node->data.single_expr.expr);
            return node;

        case NODE_IF:
            node->data.if_stmt.cond    = constant_fold(node->data.if_stmt.cond);
            node->data.if_stmt.if_body = constant_fold(node->data.if_stmt.if_body);
            node->data.if_stmt.else_body = constant_fold(node->data.if_stmt.else_body);
            return node;

        case NODE_WHILE:
            node->data.while_stmt.cond = constant_fold(node->data.while_stmt.cond);
            node->data.while_stmt.body = constant_fold(node->data.while_stmt.body);
            return node;

        case NODE_FOR:
            node->data.for_stmt.init_expr = constant_fold(node->data.for_stmt.init_expr);
            node->data.for_stmt.cond      = constant_fold(node->data.for_stmt.cond);
            node->data.for_stmt.inc_expr  = constant_fold(node->data.for_stmt.inc_expr);
            node->data.for_stmt.body      = constant_fold(node->data.for_stmt.body);
            return node;

        case NODE_NOT:
            node->data.single_expr.expr = constant_fold(node->data.single_expr.expr);
            if (node->data.single_expr.expr->type == NODE_BOOL_LIT) {
                int v = !node->data.single_expr.expr->data.bool_val;
                printf("  [fold] !%s => %s\n",
                       node->data.single_expr.expr->data.bool_val ? "true" : "false",
                       v ? "true" : "false");
                return create_bool_node(v);
            }
            return node;

        case NODE_NEG:
            node->data.single_expr.expr = constant_fold(node->data.single_expr.expr);
            if (node->data.single_expr.expr->type == NODE_NUM) {
                int v = -node->data.single_expr.expr->data.num_val;
                printf("  [fold] -(%d) => %d\n",
                       node->data.single_expr.expr->data.num_val, v);
                return create_num_node(v);
            }
            if (node->data.single_expr.expr->type == NODE_FLOAT_NUM) {
                float v = -node->data.single_expr.expr->data.float_val;
                return create_float_node(v);
            }
            return node;

        case NODE_BINOP: {
            node->data.binop.left  = constant_fold(node->data.binop.left);
            node->data.binop.right = constant_fold(node->data.binop.right);

            ASTNode *L = node->data.binop.left;
            ASTNode *R = node->data.binop.right;
            int op     = node->data.binop.op;

            /* Int × Int */
            if (L->type == NODE_NUM && R->type == NODE_NUM) {
                int a = L->data.num_val, b = R->data.num_val, res = 0;
                int ok = 1;
                switch (op) {
                    case PLUS:  res = a + b; break;
                    case MINUS: res = a - b; break;
                    case MULT:  res = a * b; break;
                    case DIV:
                        if (b == 0) { report_warning(node->line, node->col,
                                          "Division by zero in constant expression."); ok = 0; }
                        else res = a / b;
                        break;
                    case MOD:
                        if (b == 0) { ok = 0; }
                        else res = a % b;
                        break;
                    case EQ:  return create_bool_node(a == b);
                    case NE:  return create_bool_node(a != b);
                    case LT:  return create_bool_node(a <  b);
                    case GT:  return create_bool_node(a >  b);
                    case LE:  return create_bool_node(a <= b);
                    case GE:  return create_bool_node(a >= b);
                    default:  ok = 0;
                }
                if (ok) {
                    printf("  [fold] %d %s %d => %d\n", a, token_op_str(op), b, res);
                    return create_num_node(res);
                }
            }

            /* Float × Float */
            if ((L->type == NODE_FLOAT_NUM || L->type == NODE_NUM) &&
                (R->type == NODE_FLOAT_NUM || R->type == NODE_NUM)) {
                float a = (L->type == NODE_FLOAT_NUM) ? L->data.float_val : (float)L->data.num_val;
                float b = (R->type == NODE_FLOAT_NUM) ? R->data.float_val : (float)R->data.num_val;
                if (L->type == NODE_FLOAT_NUM || R->type == NODE_FLOAT_NUM) {
                    switch (op) {
                        case PLUS:  return create_float_node(a + b);
                        case MINUS: return create_float_node(a - b);
                        case MULT:  return create_float_node(a * b);
                        case DIV:
                            if (b == 0.0f) break;
                            return create_float_node(a / b);
                        default: break;
                    }
                }
            }

            /* Bool × Bool */
            if (L->type == NODE_BOOL_LIT && R->type == NODE_BOOL_LIT) {
                int a = L->data.bool_val, b = R->data.bool_val;
                switch (op) {
                    case AND: return create_bool_node(a && b);
                    case OR:  return create_bool_node(a || b);
                    case EQ:  return create_bool_node(a == b);
                    case NE:  return create_bool_node(a != b);
                    default:  break;
                }
            }

            return node;
        }

        case NODE_DO_WHILE:
            node->data.do_while.body = constant_fold(node->data.do_while.body);
            node->data.do_while.cond = constant_fold(node->data.do_while.cond);
            return node;

        case NODE_SWITCH:
            node->data.sw.expr = constant_fold(node->data.sw.expr);
            {
                ASTNode *c = node->data.sw.cases;
                while (c) {
                    if (!c->data.cas.is_default)
                        c->data.cas.val = constant_fold(c->data.cas.val);
                    c->data.cas.body = constant_fold(c->data.cas.body);
                    c = c->data.cas.next_case;
                }
            }
            return node;

        case NODE_ARRAY_ASSIGN:
            node->data.arr_assign.index = constant_fold(node->data.arr_assign.index);
            node->data.arr_assign.expr  = constant_fold(node->data.arr_assign.expr);
            return node;

        case NODE_ARRAY_ACCESS:
            node->data.arr_access.index = constant_fold(node->data.arr_access.index);
            return node;

        default:
            return node;
    }
}

/* =========================================
   TAC CODE GENERATION
   ========================================= */
char *codegen(ASTNode *node) {
    if (!node) return NULL;

    if (node->type == NODE_BLOCK) {
        codegen(node->data.seq.next);
        codegen(node->data.seq.stmt);
        return NULL;
    }

    switch (node->type) {

        case NODE_NUM: {
            char buf[32];
            snprintf(buf, sizeof(buf), "%d", node->data.num_val);
            return strdup(buf);
        }
        case NODE_FLOAT_NUM: {
            char buf[32];
            snprintf(buf, sizeof(buf), "%g", node->data.float_val);
            return strdup(buf);
        }
        case NODE_BOOL_LIT:
            return strdup(node->data.bool_val ? "true" : "false");

        case NODE_STR_LIT: {
            char buf[256];
            snprintf(buf, sizeof(buf), "\"%s\"", node->data.str_val);
            return strdup(buf);
        }

        case NODE_ID:
            return strdup(node->data.id_name);

        case NODE_DECL:
            /* Declarations don't emit TAC; symbol is already in table */
            return NULL;

        case NODE_ASSIGN: {
            char *rhs = codegen(node->data.assign.expr);
            if (rhs) emit(TAC_ASSIGN, node->data.assign.name, rhs, NULL, NULL);
            return NULL;
        }

        case NODE_CAST: {
            char *inner = codegen(node->data.cast.expr);
            char *t = new_temp();
            char buf[64];
            snprintf(buf, sizeof(buf), "(%s)", type_name(node->data.cast.target));
            emit(TAC_UNOP, t, inner, buf, NULL);
            return t;
        }

        case NODE_BINOP: {
            char *left  = codegen(node->data.binop.left);
            char *right = codegen(node->data.binop.right);
            char *t     = new_temp();
            emit(TAC_BINOP, t, left, (char*)token_op_str(node->data.binop.op), right);
            return t;
        }

        case NODE_NOT: {
            char *operand = codegen(node->data.single_expr.expr);
            char *t = new_temp();
            emit(TAC_UNOP, t, operand, "!", NULL);
            return t;
        }

        case NODE_NEG: {
            char *operand = codegen(node->data.single_expr.expr);
            char *t = new_temp();
            emit(TAC_UNOP, t, operand, "-", NULL);
            return t;
        }

        case NODE_PRINT: {
            char *val = codegen(node->data.single_expr.expr);
            emit(TAC_PRINT, NULL, val, NULL, NULL);
            return NULL;
        }

        case NODE_RETURN: {
            char *val = codegen(node->data.single_expr.expr);
            emit(TAC_RETURN, NULL, val, NULL, NULL);
            return NULL;
        }

        case NODE_IF: {
            char *cond   = codegen(node->data.if_stmt.cond);
            char *lfalse = new_label();
            char *lend   = new_label();

            emit(TAC_IF_FALSE, lfalse, cond, NULL, NULL);
            codegen(node->data.if_stmt.if_body);

            if (node->data.if_stmt.else_body) {
                emit(TAC_GOTO, lend, NULL, NULL, NULL);
                emit(TAC_LABEL, lfalse, NULL, NULL, NULL);
                codegen(node->data.if_stmt.else_body);
                emit(TAC_LABEL, lend, NULL, NULL, NULL);
            } else {
                emit(TAC_LABEL, lfalse, NULL, NULL, NULL);
            }
            return NULL;
        }

        case NODE_WHILE: {
            char *lstart = new_label();
            char *lend   = new_label();

            emit(TAC_LABEL, lstart, NULL, NULL, NULL);
            char *cond = codegen(node->data.while_stmt.cond);
            emit(TAC_IF_FALSE, lend, cond, NULL, NULL);
            codegen(node->data.while_stmt.body);
            emit(TAC_GOTO, lstart, NULL, NULL, NULL);
            emit(TAC_LABEL, lend, NULL, NULL, NULL);
            return NULL;
        }

        case NODE_FOR: {
            /* init */
            char *init_val = codegen(node->data.for_stmt.init_expr);
            if (init_val) emit(TAC_ASSIGN, node->data.for_stmt.init_id, init_val, NULL, NULL);

            char *lstart = new_label();
            char *lend   = new_label();

            emit(TAC_LABEL, lstart, NULL, NULL, NULL);
            char *cond = codegen(node->data.for_stmt.cond);
            emit(TAC_IF_FALSE, lend, cond, NULL, NULL);
            codegen(node->data.for_stmt.body);

            /* increment */
            char *inc_val = codegen(node->data.for_stmt.inc_expr);
            if (inc_val) emit(TAC_ASSIGN, node->data.for_stmt.inc_id, inc_val, NULL, NULL);

            emit(TAC_GOTO, lstart, NULL, NULL, NULL);
            emit(TAC_LABEL, lend, NULL, NULL, NULL);
            return NULL;
        }

        case NODE_FUNC_DECL: {
            char func_label[128];
            snprintf(func_label, sizeof(func_label), "func_%s", node->data.func_decl.name);
            emit(TAC_LABEL, func_label, NULL, NULL, NULL);
            codegen(node->data.func_decl.body);
            emit(TAC_RETURN, NULL, NULL, NULL, NULL);
            return NULL;
        }

        case NODE_FUNC_CALL: {
            /* Push args */
            ExprList *a = node->data.func_call.args;
            int argc = 0;
            /* Collect into array to push in order */
            char *args[32];
            while (a && argc < 32) {
                args[argc++] = codegen(a->expr);
                a = a->next;
            }
            for (int i = 0; i < argc; i++)
                emit(TAC_PARAM, NULL, args[i], NULL, NULL);

            char *t = new_temp();
            char cnt[16]; snprintf(cnt, sizeof(cnt), "%d", argc);
            emit(TAC_CALL, t, node->data.func_call.name, NULL, cnt);
            return t;
        }

        case NODE_DO_WHILE: {
            char *lstart = new_label();
            char *lend   = new_label();
            emit(TAC_LABEL, lstart, NULL, NULL, NULL);
            codegen(node->data.do_while.body);
            char *cond = codegen(node->data.do_while.cond);
            emit(TAC_IF_FALSE, lend, cond, NULL, NULL);
            emit(TAC_GOTO, lstart, NULL, NULL, NULL);
            emit(TAC_LABEL, lend, NULL, NULL, NULL);
            return NULL;
        }

        case NODE_SWITCH: {
            char *val    = codegen(node->data.sw.expr);
            char *lend   = new_label();
            ASTNode *c   = node->data.sw.cases;
            /* Generate labels for each case first */
            int  n_cases = 0;
            ASTNode *tmp = c;
            while (tmp) { n_cases++; tmp = tmp->data.cas.next_case; }
            char **case_labels = malloc(sizeof(char*) * (n_cases + 1));
            tmp = c; int ci = 0;
            while (tmp) { case_labels[ci++] = new_label(); tmp = tmp->data.cas.next_case; }
            case_labels[ci] = lend; /* fallthrough to end */
            /* Emit comparisons */
            ci = 0; tmp = c;
            while (tmp) {
                if (!tmp->data.cas.is_default) {
                    char *cv = codegen(tmp->data.cas.val);
                    char *t  = new_temp();
                    emit(TAC_BINOP, t, val, "==", cv);
                    emit(TAC_IF_FALSE, case_labels[ci + 1], t, NULL, NULL);
                } else {
                    emit(TAC_GOTO, case_labels[ci], NULL, NULL, NULL);
                }
                emit(TAC_LABEL, case_labels[ci], NULL, NULL, NULL);
                codegen(tmp->data.cas.body);
                ci++;
                tmp = tmp->data.cas.next_case;
            }
            emit(TAC_LABEL, lend, NULL, NULL, NULL);
            free(case_labels);
            return NULL;
        }

        case NODE_BREAK:
            emit(TAC_GOTO, "BREAK_TARGET", NULL, NULL, NULL);
            return NULL;

        case NODE_CONTINUE:
            emit(TAC_GOTO, "CONTINUE_TARGET", NULL, NULL, NULL);
            return NULL;

        case NODE_ARRAY_DECL:
            /* Declaration — no TAC needed, size info goes in symbol table */
            return NULL;

        case NODE_ARRAY_ACCESS: {
            /* arr[index]  →  t = arr[index] */
            char *idx = codegen(node->data.arr_access.index);
            char *t   = new_temp();
            char lval[128];
            snprintf(lval, sizeof(lval), "%s[%s]", node->data.arr_access.name, idx);
            emit(TAC_ASSIGN, t, lval, NULL, NULL);
            return t;
        }

        case NODE_ARRAY_ASSIGN: {
            /* arr[index] = expr  */
            char *idx = codegen(node->data.arr_assign.index);
            char *rhs = codegen(node->data.arr_assign.expr);
            char lval[128];
            snprintf(lval, sizeof(lval), "%s[%s]", node->data.arr_assign.name, idx);
            emit(TAC_ASSIGN, lval, rhs, NULL, NULL);
            return NULL;
        }

        default:
            return NULL;
    }
}
