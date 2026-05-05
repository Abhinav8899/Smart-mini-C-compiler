#ifndef COMPILER_UTILS_H
#define COMPILER_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================
   1. DATA TYPES
   ========================================= */
typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_BOOL, TYPE_STRING, TYPE_VOID, TYPE_UNKNOWN = -1 } DataType;

const char* type_name(DataType type);

/* =========================================
   2. SCOPED SYMBOL TABLE
   ========================================= */
#define HASH_SIZE 211
#define MAX_SCOPES 64

typedef struct Symbol {
    char       *name;
    DataType    type;
    int         scope_level;
    int         is_func;        /* 1 if this is a function */
    int         is_array;       /* 1 if this is an array   */
    int         array_size;
    DataType    param_types[8]; /* parameter types (functions) */
    int         param_count;
    struct Symbol *next;
} Symbol;

typedef struct Scope {
    Symbol *table[HASH_SIZE];
} Scope;

/* Scope stack */
extern Scope  *scope_stack[MAX_SCOPES];
extern int     scope_depth;

void   push_scope();
void   pop_scope();
void   insert_symbol(char *name, DataType type);
void   insert_array_symbol(char *name, DataType elem_type, int size);
void   insert_func_symbol(char *name, DataType ret_type, DataType *param_types, int param_count);
Symbol *lookup_symbol(char *name);      /* searches all scopes */
Symbol *lookup_current_scope(char *name); /* only current scope */
void   print_symtab();

/* =========================================
   3. AST NODE TYPES
   ========================================= */
typedef enum {
    NODE_PROGRAM, NODE_DECL, NODE_ASSIGN, NODE_PRINT,
    NODE_IF, NODE_WHILE, NODE_FOR, NODE_BINOP,
    NODE_NUM, NODE_FLOAT_NUM, NODE_BOOL_LIT, NODE_STR_LIT,
    NODE_ID, NODE_BLOCK, NODE_NOT, NODE_NEG,
    NODE_FUNC_DECL, NODE_FUNC_CALL, NODE_RETURN,
    NODE_CAST,
    NODE_DO_WHILE,          /* do { body } while (cond)          */
    NODE_SWITCH,            /* switch (expr) { cases }           */
    NODE_CASE,              /* case val: stmts  OR  default:     */
    NODE_BREAK,             /* break;                            */
    NODE_CONTINUE,          /* continue;                         */
    NODE_ARRAY_DECL,        /* int arr[10];                      */
    NODE_ARRAY_ACCESS,      /* arr[i]                            */
    NODE_ARRAY_ASSIGN       /* arr[i] = expr;                    */
} NodeType;

/* Linked list of expressions (for function call arguments) */
typedef struct ExprList {
    struct ASTNode  *expr;
    struct ExprList *next;
} ExprList;

/* Linked list of parameter declarations */
typedef struct ParamList {
    char            *name;
    DataType         type;
    struct ParamList *next;
} ParamList;

typedef struct ASTNode {
    NodeType type;
    int      line;          /* source line for error reporting */
    int      col;           /* source column */
    union {
        int   num_val;
        float float_val;
        int   bool_val;     /* 0/1 */
        char *str_val;      /* string literal */
        char *id_name;

        struct { DataType var_type; char *name; } decl;

        struct { char *name; struct ASTNode *expr; int op; } assign;
        /* op == 0 means plain =, else it mirrors the compound token value */

        struct { int op; struct ASTNode *left; struct ASTNode *right; } binop;

        struct { struct ASTNode *cond;
                 struct ASTNode *if_body;
                 struct ASTNode *else_body; } if_stmt;

        struct { struct ASTNode *cond; struct ASTNode *body; } while_stmt;

        struct { char *init_id;   struct ASTNode *init_expr;
                 struct ASTNode *cond;
                 char *inc_id;    struct ASTNode *inc_expr;
                 struct ASTNode *body; } for_stmt;

        struct { struct ASTNode *expr; } single_expr;

        struct { struct ASTNode *stmt; struct ASTNode *next; } seq;

        /* Functions */
        struct { char *name; DataType ret_type;
                 ParamList *params;
                 struct ASTNode *body; } func_decl;

        struct { char *name; ExprList *args; } func_call;

        /* Cast */
        struct { DataType target; struct ASTNode *expr; } cast;

        /* do-while */
        struct { struct ASTNode *body; struct ASTNode *cond; } do_while;

        /* switch */
        struct { struct ASTNode *expr; struct ASTNode *cases; } sw;

        /* case / default  (is_default==1 means default:) */
        struct { int is_default; struct ASTNode *val;
                 struct ASTNode *body; struct ASTNode *next_case; } cas;

        /* Arrays */
        struct { DataType elem_type; char *name; int size; } arr_decl;
        struct { char *name; struct ASTNode *index; } arr_access;
        struct { char *name; struct ASTNode *index; struct ASTNode *expr; } arr_assign;
    } data;
} ASTNode;

/* AST helpers */
ASTNode *create_node(NodeType type);
ASTNode *create_num_node(int val);
ASTNode *create_float_node(float val);
ASTNode *create_bool_node(int val);
ASTNode *create_str_node(char *val);
ASTNode *create_id_node(char *name);
ASTNode *create_binop_node(int op, ASTNode *left, ASTNode *right);
ASTNode *create_seq_node(ASTNode *stmt, ASTNode *next);
ASTNode *create_cast_node(DataType target, ASTNode *expr);
ASTNode *create_array_decl_node(DataType elem_type, char *name, int size);
ASTNode *create_array_access_node(char *name, ASTNode *index);
ASTNode *create_array_assign_node(char *name, ASTNode *index, ASTNode *expr);

ExprList  *create_expr_list(ASTNode *expr, ExprList *next);
ParamList *create_param(char *name, DataType type, ParamList *next);

/* AST printer */
void print_ast(ASTNode *node, int level);

/* =========================================
   4. THREE-ADDRESS CODE (TAC)
   ========================================= */
typedef enum {
    TAC_ASSIGN,        /* x = y          */
    TAC_BINOP,         /* x = y op z     */
    TAC_UNOP,          /* x = op y       */
    TAC_COPY,          /* x = y (copy)   */
    TAC_LABEL,         /* label:         */
    TAC_GOTO,          /* goto label     */
    TAC_IF_FALSE,      /* if !cond goto  */
    TAC_PARAM,         /* param x        */
    TAC_CALL,          /* x = call f n   */
    TAC_RETURN,        /* return x       */
    TAC_PRINT          /* print x        */
} TACKind;

typedef struct TACInstr {
    TACKind kind;
    char   *result;
    char   *arg1;
    char   *arg2;
    char   *op;
    struct TACInstr *next;
} TACInstr;

typedef struct {
    TACInstr *head;
    TACInstr *tail;
    int       temp_count;
    int       label_count;
} TACList;

extern TACList tac_program;

void   tac_init();
char  *new_temp();
char  *new_label();
void   emit(TACKind kind, char *result, char *arg1, char *op, char *arg2);
void   print_tac();

/* =========================================
   5. ERROR HANDLING WITH SUGGESTIONS
   ========================================= */

/* Column tracking — set in lexer */
extern int current_col;
extern int error_count;

/* Levenshtein distance for "did you mean?" */
int  edit_distance(const char *a, const char *b);
char *closest_symbol(char *name);   /* returns closest name or NULL */

void report_error(int line, int col, const char *msg);
void report_warning(int line, int col, const char *msg);

/* Underline helper: prints source line with a ^^^ pointer */
/* source_lines[] must be populated during lexing            */
#define MAX_LINES 4096
extern char *source_lines[MAX_LINES];
extern int   source_line_count;

void print_source_pointer(int line, int col, int len);

#endif /* COMPILER_UTILS_H */
