#include "compiler_utils.h"

/* =========================================
   TYPE NAME HELPER
   ========================================= */
const char* type_name(DataType type) {
    switch (type) {
        case TYPE_INT:    return "int";
        case TYPE_FLOAT:  return "float";
        case TYPE_BOOL:   return "bool";
        case TYPE_STRING: return "string";
        case TYPE_VOID:   return "void";
        default:          return "unknown";
    }
}

/* =========================================
   SCOPED SYMBOL TABLE
   ========================================= */
Scope *scope_stack[MAX_SCOPES];
int    scope_depth = -1;

int    error_count = 0;
char  *source_lines[MAX_LINES];
int    source_line_count = 0;
int    current_col = 0;

static unsigned int hash_str(char *str) {
    if (!str) return 0;
    unsigned int h = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        h = ((h << 5) + h) + c;
    return h % HASH_SIZE;
}

void push_scope() {
    if (scope_depth + 1 >= MAX_SCOPES) {
        fprintf(stderr, "Internal error: scope stack overflow\n");
        exit(1);
    }
    scope_depth++;
    scope_stack[scope_depth] = (Scope*)calloc(1, sizeof(Scope));
}

void pop_scope() {
    if (scope_depth < 0) return;
    Scope *s = scope_stack[scope_depth];
    for (int i = 0; i < HASH_SIZE; i++) {
        Symbol *sym = s->table[i];
        while (sym) {
            Symbol *next = sym->next;
            free(sym->name);
            free(sym);
            sym = next;
        }
    }
    free(s);
    scope_stack[scope_depth] = NULL;
    scope_depth--;
}

static void _insert(Scope *s, char *name, DataType type, int is_func,
                    int is_array, int array_size,
                    DataType *param_types, int param_count) {
    unsigned int idx = hash_str(name);
    Symbol *sym = (Symbol*)calloc(1, sizeof(Symbol));
    sym->name        = strdup(name);
    sym->type        = type;
    sym->scope_level = scope_depth;
    sym->is_func     = is_func;
    sym->is_array    = is_array;
    sym->array_size  = array_size;
    sym->param_count = param_count;
    for (int i = 0; i < param_count && i < 8; i++)
        sym->param_types[i] = param_types[i];
    sym->next        = s->table[idx];
    s->table[idx]    = sym;
}

void insert_symbol(char *name, DataType type) {
    if (scope_depth < 0) push_scope();
    _insert(scope_stack[scope_depth], name, type, 0, 0, 0, NULL, 0);
}

void insert_func_symbol(char *name, DataType ret_type,
                        DataType *param_types, int param_count) {
    if (scope_depth < 0) push_scope();
    _insert(scope_stack[scope_depth], name, ret_type, 1, 0, 0, param_types, param_count);
}

void insert_array_symbol(char *name, DataType elem_type, int size) {
    if (scope_depth < 0) push_scope();
    _insert(scope_stack[scope_depth], name, elem_type, 0, 1, size, NULL, 0);
}

Symbol *lookup_symbol(char *name) {
    if (!name) return NULL;
    unsigned int idx = hash_str(name);
    for (int d = scope_depth; d >= 0; d--) {
        Symbol *sym = scope_stack[d]->table[idx];
        while (sym) {
            if (strcmp(sym->name, name) == 0) return sym;
            sym = sym->next;
        }
    }
    return NULL;
}

Symbol *lookup_current_scope(char *name) {
    if (!name || scope_depth < 0) return NULL;
    unsigned int idx = hash_str(name);
    Symbol *sym = scope_stack[scope_depth]->table[idx];
    while (sym) {
        if (strcmp(sym->name, name) == 0) return sym;
        sym = sym->next;
    }
    return NULL;
}

void print_symtab() {
    printf("\n=== Symbol Table (all scopes) ===\n");
    int found = 0;
    for (int d = 0; d <= scope_depth; d++) {
        Scope *s = scope_stack[d];
        for (int i = 0; i < HASH_SIZE; i++) {
            Symbol *sym = s->table[i];
            while (sym) {
                if (sym->is_func) {
                    printf("  [scope %d] func  %-12s | returns: %-6s | params: %d\n",
                           d, sym->name, type_name(sym->type), sym->param_count);
                } else if (sym->is_array) {
                    printf("  [scope %d] array %-12s | elem: %-6s | size: %d\n",
                           d, sym->name, type_name(sym->type), sym->array_size);
                } else {
                    printf("  [scope %d] var   %-12s | type: %s\n",
                           d, sym->name, type_name(sym->type));
                }
                found = 1;
                sym = sym->next;
            }
        }
    }
    if (!found) printf("  (empty)\n");
    printf("=================================\n\n");
}

/* =========================================
   AST HELPERS
   ========================================= */
ASTNode *create_node(NodeType type) {
    ASTNode *n = (ASTNode*)calloc(1, sizeof(ASTNode));
    n->type = type;
    return n;
}
ASTNode *create_num_node(int val) {
    ASTNode *n = create_node(NODE_NUM);
    n->data.num_val = val;
    return n;
}
ASTNode *create_float_node(float val) {
    ASTNode *n = create_node(NODE_FLOAT_NUM);
    n->data.float_val = val;
    return n;
}
ASTNode *create_bool_node(int val) {
    ASTNode *n = create_node(NODE_BOOL_LIT);
    n->data.bool_val = val;
    return n;
}
ASTNode *create_str_node(char *val) {
    ASTNode *n = create_node(NODE_STR_LIT);
    n->data.str_val = strdup(val);
    return n;
}
ASTNode *create_id_node(char *name) {
    ASTNode *n = create_node(NODE_ID);
    n->data.id_name = strdup(name);
    return n;
}
ASTNode *create_binop_node(int op, ASTNode *left, ASTNode *right) {
    ASTNode *n = create_node(NODE_BINOP);
    n->data.binop.op    = op;
    n->data.binop.left  = left;
    n->data.binop.right = right;
    return n;
}
ASTNode *create_seq_node(ASTNode *stmt, ASTNode *next) {
    if (!stmt) return next;
    ASTNode *n = create_node(NODE_BLOCK);
    n->data.seq.stmt = stmt;
    n->data.seq.next = next;
    return n;
}
ASTNode *create_cast_node(DataType target, ASTNode *expr) {
    ASTNode *n = create_node(NODE_CAST);
    n->data.cast.target = target;
    n->data.cast.expr   = expr;
    return n;
}
ASTNode *create_array_decl_node(DataType elem_type, char *name, int size) {
    ASTNode *n = create_node(NODE_ARRAY_DECL);
    n->data.arr_decl.elem_type = elem_type;
    n->data.arr_decl.name      = strdup(name);
    n->data.arr_decl.size      = size;
    return n;
}
ASTNode *create_array_access_node(char *name, ASTNode *index) {
    ASTNode *n = create_node(NODE_ARRAY_ACCESS);
    n->data.arr_access.name  = strdup(name);
    n->data.arr_access.index = index;
    return n;
}
ASTNode *create_array_assign_node(char *name, ASTNode *index, ASTNode *expr) {
    ASTNode *n = create_node(NODE_ARRAY_ASSIGN);
    n->data.arr_assign.name  = strdup(name);
    n->data.arr_assign.index = index;
    n->data.arr_assign.expr  = expr;
    return n;
}
ExprList *create_expr_list(ASTNode *expr, ExprList *next) {
    ExprList *el = (ExprList*)malloc(sizeof(ExprList));
    el->expr = expr;
    el->next = next;
    return el;
}
ParamList *create_param(char *name, DataType type, ParamList *next) {
    ParamList *p = (ParamList*)malloc(sizeof(ParamList));
    p->name = strdup(name);
    p->type = type;
    p->next = next;
    return p;
}

/* =========================================
   AST PRINTER
   ========================================= */
static void print_indent(int level) {
    for (int i = 0; i < level; i++) printf("  | ");
}

void print_ast(ASTNode *node, int level) {
    if (!node) return;

    if (node->type == NODE_BLOCK) {
        print_ast(node->data.seq.next, level);
        print_ast(node->data.seq.stmt, level);
        return;
    }

    print_indent(level);

    switch (node->type) {
        case NODE_NUM:
            printf("NUMBER: %d\n", node->data.num_val); break;
        case NODE_FLOAT_NUM:
            printf("FLOAT: %g\n", node->data.float_val); break;
        case NODE_BOOL_LIT:
            printf("BOOL: %s\n", node->data.bool_val ? "true" : "false"); break;
        case NODE_STR_LIT:
            printf("STRING: \"%s\"\n", node->data.str_val); break;
        case NODE_ID:
            printf("ID: %s\n", node->data.id_name); break;
        case NODE_DECL:
            printf("DECL: %s %s\n",
                   type_name((DataType)node->data.decl.var_type),
                   node->data.decl.name);
            break;
        case NODE_ASSIGN:
            printf("ASSIGN: %s =\n", node->data.assign.name);
            print_ast(node->data.assign.expr, level + 1);
            break;
        case NODE_PRINT:
            printf("PRINT:\n");
            print_ast(node->data.single_expr.expr, level + 1);
            break;
        case NODE_RETURN:
            printf("RETURN:\n");
            print_ast(node->data.single_expr.expr, level + 1);
            break;
        case NODE_CAST:
            printf("CAST -> %s:\n", type_name(node->data.cast.target));
            print_ast(node->data.cast.expr, level + 1);
            break;
        case NODE_NOT:
            printf("NOT:\n");
            print_ast(node->data.single_expr.expr, level + 1);
            break;
        case NODE_NEG:
            printf("NEG:\n");
            print_ast(node->data.single_expr.expr, level + 1);
            break;
        case NODE_BINOP: {
            /* We use token values — print them symbolically */
            printf("BINOP: ");
            int op = node->data.binop.op;
            /* Map token numbers to strings at print time */
            /* We use a helper string so we don't depend on parser.tab.h here */
            extern const char *token_op_str(int op);
            printf("%s\n", token_op_str(op));
            print_ast(node->data.binop.left,  level + 1);
            print_ast(node->data.binop.right, level + 1);
            break;
        }
        case NODE_IF:
            printf("IF:\n");
            print_indent(level); printf(" |- Condition:\n");
            print_ast(node->data.if_stmt.cond, level + 1);
            print_indent(level); printf(" |- Then:\n");
            print_ast(node->data.if_stmt.if_body, level + 1);
            if (node->data.if_stmt.else_body) {
                print_indent(level); printf(" |- Else:\n");
                print_ast(node->data.if_stmt.else_body, level + 1);
            }
            break;
        case NODE_WHILE:
            printf("WHILE:\n");
            print_indent(level); printf(" |- Condition:\n");
            print_ast(node->data.while_stmt.cond, level + 1);
            print_indent(level); printf(" |- Body:\n");
            print_ast(node->data.while_stmt.body, level + 1);
            break;
        case NODE_FOR:
            printf("FOR:\n");
            print_indent(level); printf(" |- Init (%s =):\n", node->data.for_stmt.init_id);
            print_ast(node->data.for_stmt.init_expr, level + 1);
            print_indent(level); printf(" |- Condition:\n");
            print_ast(node->data.for_stmt.cond, level + 1);
            print_indent(level); printf(" |- Increment (%s =):\n", node->data.for_stmt.inc_id);
            print_ast(node->data.for_stmt.inc_expr, level + 1);
            print_indent(level); printf(" |- Body:\n");
            print_ast(node->data.for_stmt.body, level + 1);
            break;
        case NODE_FUNC_DECL:
            printf("FUNC DECL: %s -> %s\n",
                   node->data.func_decl.name,
                   type_name(node->data.func_decl.ret_type));
            {
                ParamList *p = node->data.func_decl.params;
                while (p) {
                    print_indent(level + 1);
                    printf("PARAM: %s %s\n", type_name(p->type), p->name);
                    p = p->next;
                }
            }
            print_ast(node->data.func_decl.body, level + 1);
            break;
        case NODE_FUNC_CALL:
            printf("CALL: %s\n", node->data.func_call.name);
            {
                ExprList *a = node->data.func_call.args;
                int idx = 0;
                while (a) {
                    print_indent(level + 1);
                    printf("ARG %d:\n", idx++);
                    print_ast(a->expr, level + 2);
                    a = a->next;
                }
            }
            break;
        case NODE_DO_WHILE:
            printf("DO-WHILE:\n");
            print_indent(level); printf(" |- Body:\n");
            print_ast(node->data.do_while.body, level + 1);
            print_indent(level); printf(" |- Condition:\n");
            print_ast(node->data.do_while.cond, level + 1);
            break;
        case NODE_SWITCH:
            printf("SWITCH:\n");
            print_indent(level); printf(" |- Expr:\n");
            print_ast(node->data.sw.expr, level + 1);
            print_indent(level); printf(" |- Cases:\n");
            {
                ASTNode *c = node->data.sw.cases;
                while (c) {
                    print_indent(level + 1);
                    if (c->data.cas.is_default) printf("DEFAULT:\n");
                    else { printf("CASE "); print_ast(c->data.cas.val, 0); }
                    print_ast(c->data.cas.body, level + 2);
                    c = c->data.cas.next_case;
                }
            }
            break;
        case NODE_BREAK:    printf("BREAK\n");    break;
        case NODE_CONTINUE: printf("CONTINUE\n"); break;
        case NODE_ARRAY_DECL:
            printf("ARRAY DECL: %s %s[%d]\n",
                   type_name(node->data.arr_decl.elem_type),
                   node->data.arr_decl.name,
                   node->data.arr_decl.size);
            break;
        case NODE_ARRAY_ACCESS:
            printf("ARRAY ACCESS: %s[\n", node->data.arr_access.name);
            print_ast(node->data.arr_access.index, level + 1);
            print_indent(level); printf("]\n");
            break;
        case NODE_ARRAY_ASSIGN:
            printf("ARRAY ASSIGN: %s[\n", node->data.arr_assign.name);
            print_ast(node->data.arr_assign.index, level + 1);
            print_indent(level); printf("] =\n");
            print_ast(node->data.arr_assign.expr, level + 1);
            break;
        default:
            printf("(node type %d)\n", node->type);
    }
}

/* =========================================
   THREE-ADDRESS CODE
   ========================================= */
TACList tac_program;

void tac_init() {
    tac_program.head        = NULL;
    tac_program.tail        = NULL;
    tac_program.temp_count  = 0;
    tac_program.label_count = 0;
}

char *new_temp() {
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", tac_program.temp_count++);
    return strdup(buf);
}

char *new_label() {
    char buf[32];
    snprintf(buf, sizeof(buf), "L%d", tac_program.label_count++);
    return strdup(buf);
}

void emit(TACKind kind, char *result, char *arg1, char *op, char *arg2) {
    TACInstr *instr = (TACInstr*)calloc(1, sizeof(TACInstr));
    instr->kind   = kind;
    instr->result = result ? strdup(result) : NULL;
    instr->arg1   = arg1   ? strdup(arg1)   : NULL;
    instr->op     = op     ? strdup(op)      : NULL;
    instr->arg2   = arg2   ? strdup(arg2)    : NULL;
    if (!tac_program.head) {
        tac_program.head = tac_program.tail = instr;
    } else {
        tac_program.tail->next = instr;
        tac_program.tail = instr;
    }
}

void print_tac() {
    printf("\n=== Three-Address Code ===\n");
    TACInstr *instr = tac_program.head;
    while (instr) {
        switch (instr->kind) {
            case TAC_ASSIGN:
                printf("  %s = %s\n", instr->result, instr->arg1);
                break;
            case TAC_BINOP:
                printf("  %s = %s %s %s\n",
                       instr->result, instr->arg1, instr->op, instr->arg2);
                break;
            case TAC_UNOP:
                printf("  %s = %s%s\n", instr->result, instr->op, instr->arg1);
                break;
            case TAC_COPY:
                printf("  %s = %s\n", instr->result, instr->arg1);
                break;
            case TAC_LABEL:
                printf("%s:\n", instr->result);
                break;
            case TAC_GOTO:
                printf("  goto %s\n", instr->result);
                break;
            case TAC_IF_FALSE:
                printf("  if !%s goto %s\n", instr->arg1, instr->result);
                break;
            case TAC_PARAM:
                printf("  param %s\n", instr->arg1);
                break;
            case TAC_CALL:
                printf("  %s = call %s, %s\n",
                       instr->result ? instr->result : "_",
                       instr->arg1, instr->arg2);
                break;
            case TAC_RETURN:
                if (instr->arg1)
                    printf("  return %s\n", instr->arg1);
                else
                    printf("  return\n");
                break;
            case TAC_PRINT:
                printf("  print %s\n", instr->arg1);
                break;
        }
        instr = instr->next;
    }
    printf("==========================\n\n");
}

/* =========================================
   ERROR REPORTING WITH SOURCE POINTER
   ========================================= */
void report_error(int line, int col, const char *msg) {
    error_count++;
    fprintf(stderr, "\n\033[1;31mError\033[0m [line %d, col %d]: %s\n", line, col, msg);
    print_source_pointer(line, col, 1);
}

void report_warning(int line, int col, const char *msg) {
    fprintf(stderr, "\033[1;33mWarning\033[0m [line %d, col %d]: %s\n", line, col, msg);
    print_source_pointer(line, col, 1);
}

void print_source_pointer(int line, int col, int len) {
    if (line <= 0 || line > source_line_count) return;
    fprintf(stderr, "  %s\n", source_lines[line - 1]);
    fprintf(stderr, "  ");
    for (int i = 1; i < col; i++) fprintf(stderr, " ");
    fprintf(stderr, "\033[1;31m");
    for (int i = 0; i < (len < 1 ? 1 : len); i++) fprintf(stderr, "^");
    fprintf(stderr, "\033[0m\n");
}

/* =========================================
   EDIT DISTANCE & "DID YOU MEAN?"
   ========================================= */
int edit_distance(const char *a, const char *b) {
    int la = strlen(a), lb = strlen(b);
    /* Use a small stack matrix — cap at 64 chars */
    if (la > 63 || lb > 63) return 9999;
    int dp[64][64];
    for (int i = 0; i <= la; i++) dp[i][0] = i;
    for (int j = 0; j <= lb; j++) dp[0][j] = j;
    for (int i = 1; i <= la; i++) {
        for (int j = 1; j <= lb; j++) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;
            int del  = dp[i-1][j]   + 1;
            int ins  = dp[i][j-1]   + 1;
            int sub  = dp[i-1][j-1] + cost;
            dp[i][j] = del < ins ? (del < sub ? del : sub)
                                 : (ins < sub ? ins : sub);
        }
    }
    return dp[la][lb];
}

char *closest_symbol(char *name) {
    if (!name || scope_depth < 0) return NULL;
    int   best_dist = 3;   /* only suggest if within distance 3 */
    char *best_name = NULL;
    for (int d = scope_depth; d >= 0; d--) {
        for (int i = 0; i < HASH_SIZE; i++) {
            Symbol *sym = scope_stack[d]->table[i];
            while (sym) {
                int dist = edit_distance(name, sym->name);
                if (dist < best_dist) {
                    best_dist = dist;
                    best_name = sym->name;
                }
                sym = sym->next;
            }
        }
    }
    return best_name;
}
