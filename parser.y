%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler_utils.h"
#include "semantic.h"

extern int  yylineno;
extern int  current_col;
void yyerror(const char *s);
int  yylex();

ASTNode *root = NULL;

/* Attach line/col to a freshly created node */
static ASTNode *at(ASTNode *n) {
    if (n) { n->line = yylineno; n->col = current_col; }
    return n;
}
%}

/* ── Value union ── */
%union {
    int         num;
    float       fnum;
    char       *str;
    struct ASTNode    *node;
    struct ExprList   *elist;
    struct ParamList  *plist;
    int         dtype;          /* DataType */
}

/* ── Tokens ── */
%token INT FLOAT_TYPE BOOL STRING_TYPE VOID
%token IF ELSE WHILE DO FOR FUNC
%token SWITCH CASE DEFAULT
%token PRINT RETURN BREAK CONTINUE
%token TRUE FALSE

%token <str>  ID STRING_LIT
%token <num>  NUMBER
%token <fnum> FLOAT_NUM

%token PLUS MINUS MULT DIV MOD
%token INCREMENT DECREMENT
%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token EQ NE LT GT LE GE
%token AND OR NOT
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA COLON

/* ── Type mappings ── */
%type <node>  program stmt_list stmt block
%type <node>  declaration assignment print_stmt return_stmt
%type <node>  if_stmt while_stmt do_while_stmt for_stmt
%type <node>  switch_stmt case_list case_item
%type <node>  func_decl func_call_stmt
%type <node>  array_decl array_assign
%type <node>  expr
%type <elist> arg_list arg_list_ne
%type <plist> param_list param_list_ne
%type <dtype> type_spec

/* ── Precedence ── */
%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV MOD
%right NOT UMINUS
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program
    : stmt_list { root = $1; }
    ;

stmt_list
    : stmt_list stmt  { $$ = create_seq_node($2, $1); }
    |                 { $$ = NULL; }
    ;

stmt
    : declaration       { $$ = $1; }
    | assignment        { $$ = $1; }
    | array_decl        { $$ = $1; }
    | array_assign      { $$ = $1; }
    | print_stmt        { $$ = $1; }
    | return_stmt       { $$ = $1; }
    | if_stmt           { $$ = $1; }
    | while_stmt        { $$ = $1; }
    | do_while_stmt     { $$ = $1; }
    | for_stmt          { $$ = $1; }
    | switch_stmt       { $$ = $1; }
    | func_decl         { $$ = $1; }
    | func_call_stmt    { $$ = $1; }
    | block             { $$ = $1; }
    | BREAK SEMICOLON   { $$ = at(create_node(NODE_BREAK)); }
    | CONTINUE SEMICOLON { $$ = at(create_node(NODE_CONTINUE)); }
    ;

block
    : LBRACE {push_scope();} stmt_list RBRACE { pop_scope(); $$ = $3; }
    | LBRACE {push_scope();} RBRACE { pop_scope(); $$ = NULL; }
    ;

/* ── Type specifiers ── */
type_spec
    : INT         { $$ = TYPE_INT;    }
    | FLOAT_TYPE  { $$ = TYPE_FLOAT;  }
    | BOOL        { $$ = TYPE_BOOL;   }
    | STRING_TYPE { $$ = TYPE_STRING; }
    | VOID        { $$ = TYPE_VOID;   }
    ;

/* ── Declarations ── */
declaration
    : type_spec ID SEMICOLON {
        if (lookup_current_scope($2)) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Variable '%s' already declared in this scope.", $2);
            report_error(yylineno, current_col, msg);
        } else {
            insert_symbol($2, (DataType)$1);
        }
        $$ = at(create_node(NODE_DECL));
        $$->data.decl.var_type = $1;
        $$->data.decl.name     = strdup($2);
      }
    | type_spec ID ASSIGN expr SEMICOLON {
        /* Declaration with initializer */
        if (lookup_current_scope($2)) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Variable '%s' already declared in this scope.", $2);
            report_error(yylineno, current_col, msg);
        } else {
            insert_symbol($2, (DataType)$1);
        }
        ASTNode *decl = at(create_node(NODE_DECL));
        decl->data.decl.var_type = $1;
        decl->data.decl.name     = strdup($2);

        ASTNode *asn = at(create_node(NODE_ASSIGN));
        asn->data.assign.name = strdup($2);
        asn->data.assign.expr = $4;

        $$ = create_seq_node(asn, decl);
      }
    ;

/* ── Assignments (plain and compound) ── */
assignment
    : ID ASSIGN expr SEMICOLON {
        if (!lookup_symbol($1)) {
            char msg[256];
            char *sug = closest_symbol($1);
            if (sug) snprintf(msg, sizeof(msg), "Undeclared variable '%s'. Did you mean '%s'?", $1, sug);
            else     snprintf(msg, sizeof(msg), "Undeclared variable '%s'.", $1);
            report_error(yylineno, current_col, msg);
        }
        $$ = at(create_node(NODE_ASSIGN));
        $$->data.assign.name = strdup($1);
        $$->data.assign.expr = $3;
        $$->data.assign.op   = 0;
      }
    | ID ADD_ASSIGN expr SEMICOLON {
        /* Desugar: x += e  →  x = x + e */
        ASTNode *id = at(create_id_node($1));
        ASTNode *rhs = create_binop_node(PLUS, id, $3);
        $$ = at(create_node(NODE_ASSIGN));
        $$->data.assign.name = strdup($1);
        $$->data.assign.expr = rhs;
      }
    | ID SUB_ASSIGN expr SEMICOLON {
        ASTNode *id = at(create_id_node($1));
        ASTNode *rhs = create_binop_node(MINUS, id, $3);
        $$ = at(create_node(NODE_ASSIGN));
        $$->data.assign.name = strdup($1);
        $$->data.assign.expr = rhs;
      }
    | ID MUL_ASSIGN expr SEMICOLON {
        ASTNode *id = at(create_id_node($1));
        ASTNode *rhs = create_binop_node(MULT, id, $3);
        $$ = at(create_node(NODE_ASSIGN));
        $$->data.assign.name = strdup($1);
        $$->data.assign.expr = rhs;
      }
    | ID DIV_ASSIGN expr SEMICOLON {
        ASTNode *id = at(create_id_node($1));
        ASTNode *rhs = create_binop_node(DIV, id, $3);
        $$ = at(create_node(NODE_ASSIGN));
        $$->data.assign.name = strdup($1);
        $$->data.assign.expr = rhs;
      }
    | ID INCREMENT SEMICOLON {
        /* i++  →  i = i + 1 */
        ASTNode *id  = at(create_id_node($1));
        ASTNode *one = create_num_node(1);
        ASTNode *rhs = create_binop_node(PLUS, id, one);
        $$ = at(create_node(NODE_ASSIGN));
        $$->data.assign.name = strdup($1);
        $$->data.assign.expr = rhs;
      }
    | ID DECREMENT SEMICOLON {
        ASTNode *id  = at(create_id_node($1));
        ASTNode *one = create_num_node(1);
        ASTNode *rhs = create_binop_node(MINUS, id, one);
        $$ = at(create_node(NODE_ASSIGN));
        $$->data.assign.name = strdup($1);
        $$->data.assign.expr = rhs;
      }
    ;

/* ── Print ── */
print_stmt
    : PRINT LPAREN expr RPAREN SEMICOLON {
        $$ = at(create_node(NODE_PRINT));
        $$->data.single_expr.expr = $3;
      }
    ;

/* ── Return ── */
return_stmt
    : RETURN expr SEMICOLON {
        $$ = at(create_node(NODE_RETURN));
        $$->data.single_expr.expr = $2;
      }
    | RETURN SEMICOLON {
        $$ = at(create_node(NODE_RETURN));
        $$->data.single_expr.expr = NULL;
      }
    ;

/* ── If / Else ── */
if_stmt
    : IF LPAREN expr RPAREN stmt %prec LOWER_THAN_ELSE {
        $$ = at(create_node(NODE_IF));
        $$->data.if_stmt.cond      = $3;
        $$->data.if_stmt.if_body   = $5;
        $$->data.if_stmt.else_body = NULL;
      }
    | IF LPAREN expr RPAREN stmt ELSE stmt {
        $$ = at(create_node(NODE_IF));
        $$->data.if_stmt.cond      = $3;
        $$->data.if_stmt.if_body   = $5;
        $$->data.if_stmt.else_body = $7;
      }
    ;

/* ── While ── */
while_stmt
    : WHILE LPAREN expr RPAREN stmt {
        $$ = at(create_node(NODE_WHILE));
        $$->data.while_stmt.cond = $3;
        $$->data.while_stmt.body = $5;
      }
    ;

/* ── Do-While ── */
do_while_stmt
    : DO stmt WHILE LPAREN expr RPAREN SEMICOLON {
        $$ = at(create_node(NODE_DO_WHILE));
        $$->data.do_while.body = $2;
        $$->data.do_while.cond = $5;
      }
    ;

/* ── Switch / Case ── */
switch_stmt
    : SWITCH LPAREN expr RPAREN LBRACE case_list RBRACE {
        $$ = at(create_node(NODE_SWITCH));
        $$->data.sw.expr  = $3;
        $$->data.sw.cases = $6;
      }
    ;

case_list
    : case_list case_item { $$ = $1;
        /* Append $2 at tail of linked list */
        ASTNode *c = $1;
        if (!c) { $$ = $2; }
        else {
            while (c->data.cas.next_case) c = c->data.cas.next_case;
            c->data.cas.next_case = $2;
            $$ = $1;
        }
      }
    |             { $$ = NULL; }
    ;

case_item
    : CASE expr COLON stmt_list {
        $$ = at(create_node(NODE_CASE));
        $$->data.cas.is_default = 0;
        $$->data.cas.val        = $2;
        $$->data.cas.body       = $4;
        $$->data.cas.next_case  = NULL;
      }
    | DEFAULT COLON stmt_list {
        $$ = at(create_node(NODE_CASE));
        $$->data.cas.is_default = 1;
        $$->data.cas.val        = NULL;
        $$->data.cas.body       = $3;
        $$->data.cas.next_case  = NULL;
      }
    ;

/* ── Array declaration ── */
array_decl
    : type_spec ID LBRACKET NUMBER RBRACKET SEMICOLON {
        if (lookup_current_scope($2)) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Array '%s' already declared in this scope.", $2);
            report_error(yylineno, current_col, msg);
        } else {
            insert_array_symbol($2, (DataType)$1, $4);
        }
        $$ = at(create_array_decl_node((DataType)$1, $2, $4));
      }
    ;

/* ── Array assignment ── */
array_assign
    : ID LBRACKET expr RBRACKET ASSIGN expr SEMICOLON {
        Symbol *sym = lookup_symbol($1);
        if (!sym) {
            char msg[256];
            char *sug = closest_symbol($1);
            if (sug) snprintf(msg, sizeof(msg), "Undeclared array '%s'. Did you mean '%s'?", $1, sug);
            else     snprintf(msg, sizeof(msg), "Undeclared array '%s'.", $1);
            report_error(yylineno, current_col, msg);
        } else if (!sym->is_array) {
            char msg[128];
            snprintf(msg, sizeof(msg), "'%s' is not an array.", $1);
            report_error(yylineno, current_col, msg);
        }
        $$ = at(create_array_assign_node($1, $3, $6));
      }
    ;

/* ── For ── */
for_stmt
    : FOR LPAREN ID ASSIGN expr SEMICOLON expr SEMICOLON ID ASSIGN expr RPAREN stmt {
        if (!lookup_symbol($3)) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Undeclared variable '%s' in for-init.", $3);
            report_error(yylineno, current_col, msg);
        }
        $$ = at(create_node(NODE_FOR));
        $$->data.for_stmt.init_id   = strdup($3);
        $$->data.for_stmt.init_expr = $5;
        $$->data.for_stmt.cond      = $7;
        $$->data.for_stmt.inc_id    = strdup($9);
        $$->data.for_stmt.inc_expr  = $11;
        $$->data.for_stmt.body      = $13;
      }
    ;

/* ── Function declaration ── */
func_decl
    : FUNC type_spec ID LPAREN param_list RPAREN {
        /* Register function in current (outer) scope */
        ParamList *p = $5;
        DataType ptypes[8]; int pc = 0;
        while (p && pc < 8) { ptypes[pc++] = p->type; p = p->next; }
        insert_func_symbol($3, (DataType)$2, ptypes, pc);
        /* Push scope and insert params BEFORE parsing body */
        push_scope();
        p = $5;
        while (p) { insert_symbol(p->name, p->type); p = p->next; }
      }
      LBRACE stmt_list RBRACE {
        pop_scope();
        $$ = at(create_node(NODE_FUNC_DECL));
        $$->data.func_decl.name     = strdup($3);
        $$->data.func_decl.ret_type = (DataType)$2;
        $$->data.func_decl.params   = $5;
        $$->data.func_decl.body     = $9;
      }
    ;

param_list
    : param_list_ne  { $$ = $1; }
    |                { $$ = NULL; }
    ;

param_list_ne
    : type_spec ID {
        $$ = create_param($2, (DataType)$1, NULL);
      }
    | param_list_ne COMMA type_spec ID {
        $$ = create_param($4, (DataType)$3, $1);
      }
    ;

/* ── Function call as statement ── */
func_call_stmt
    : ID LPAREN arg_list RPAREN SEMICOLON {
        $$ = at(create_node(NODE_FUNC_CALL));
        $$->data.func_call.name = strdup($1);
        $$->data.func_call.args = $3;
      }
    ;

arg_list
    : arg_list_ne  { $$ = $1; }
    |              { $$ = NULL; }
    ;

arg_list_ne
    : expr                       { $$ = create_expr_list($1, NULL); }
    | arg_list_ne COMMA expr     { $$ = create_expr_list($3, $1); }
    ;

/* ── Expressions ── */
expr
    : expr PLUS  expr  { $$ = at(create_binop_node(PLUS,  $1, $3)); }
    | expr MINUS expr  { $$ = at(create_binop_node(MINUS, $1, $3)); }
    | expr MULT  expr  { $$ = at(create_binop_node(MULT,  $1, $3)); }
    | expr DIV   expr  { $$ = at(create_binop_node(DIV,   $1, $3)); }
    | expr MOD   expr  { $$ = at(create_binop_node(MOD,   $1, $3)); }
    | expr EQ    expr  { $$ = at(create_binop_node(EQ,    $1, $3)); }
    | expr NE    expr  { $$ = at(create_binop_node(NE,    $1, $3)); }
    | expr LT    expr  { $$ = at(create_binop_node(LT,    $1, $3)); }
    | expr GT    expr  { $$ = at(create_binop_node(GT,    $1, $3)); }
    | expr LE    expr  { $$ = at(create_binop_node(LE,    $1, $3)); }
    | expr GE    expr  { $$ = at(create_binop_node(GE,    $1, $3)); }
    | expr AND   expr  { $$ = at(create_binop_node(AND,   $1, $3)); }
    | expr OR    expr  { $$ = at(create_binop_node(OR,    $1, $3)); }
    | NOT expr         { $$ = at(create_node(NODE_NOT)); $$->data.single_expr.expr = $2; }
    | MINUS expr %prec UMINUS { $$ = at(create_node(NODE_NEG)); $$->data.single_expr.expr = $2; }
    | LPAREN expr RPAREN { $$ = $2; }
    /* Explicit casts: (int)expr, (float)expr */
    | LPAREN INT RPAREN expr         { $$ = at(create_cast_node(TYPE_INT,    $4)); }
    | LPAREN FLOAT_TYPE RPAREN expr  { $$ = at(create_cast_node(TYPE_FLOAT,  $4)); }
    | LPAREN BOOL RPAREN expr        { $$ = at(create_cast_node(TYPE_BOOL,   $4)); }
    | LPAREN STRING_TYPE RPAREN expr { $$ = at(create_cast_node(TYPE_STRING, $4)); }
    /* Function call as expression */
    | ID LPAREN arg_list RPAREN {
        $$ = at(create_node(NODE_FUNC_CALL));
        $$->data.func_call.name = strdup($1);
        $$->data.func_call.args = $3;
      }
    | NUMBER     { $$ = at(create_num_node($1)); }
    | FLOAT_NUM  { $$ = at(create_float_node($1)); }
    | TRUE       { $$ = at(create_bool_node(1)); }
    | FALSE      { $$ = at(create_bool_node(0)); }
    | STRING_LIT { $$ = at(create_str_node($1)); }
    | ID LBRACKET expr RBRACKET {
        Symbol *sym = lookup_symbol($1);
        if (!sym) {
            char msg[256];
            char *sug = closest_symbol($1);
            if (sug) snprintf(msg, sizeof(msg), "Undeclared array '%s'. Did you mean '%s'?", $1, sug);
            else     snprintf(msg, sizeof(msg), "Undeclared identifier '%s'.", $1);
            report_error(yylineno, current_col, msg);
        } else if (!sym->is_array) {
            char msg[128];
            snprintf(msg, sizeof(msg), "'%s' is not an array, cannot index it.", $1);
            report_error(yylineno, current_col, msg);
        }
        $$ = at(create_array_access_node($1, $3));
      }
    | ID         {
        if (!lookup_symbol($1)) {
            char msg[256];
            char *sug = closest_symbol($1);
            if (sug) snprintf(msg, sizeof(msg), "Undeclared variable '%s'. Did you mean '%s'?", $1, sug);
            else     snprintf(msg, sizeof(msg), "Undeclared variable '%s'.", $1);
            report_error(yylineno, current_col, msg);
        }
        $$ = at(create_id_node($1));
      }
    ;

%%

void yyerror(const char *s) {
    /* Try to give a more helpful message */
    char msg[256];
    if (strstr(s, "syntax error")) {
        snprintf(msg, sizeof(msg),
                 "Syntax error near token. "
                 "Check for a missing ';', mismatched '(' or '{', or wrong keyword.");
    } else {
        snprintf(msg, sizeof(msg), "%s", s);
    }
    report_error(yylineno, current_col, msg);
}
