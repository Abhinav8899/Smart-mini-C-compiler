%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern char *yytext;

void yyerror(const char *s);
int yylex();
%}

/* value types */

%union {
    int num;
}

/* Tokens */

%token INT FLOAT BOOL
%token IF ELSE WHILE FOR
%token PRINT RETURN
%token BREAK CONTINUE
%token TRUE FALSE

%token ID
%token <num> NUMBER

%token PLUS MINUS MULT DIV MOD
%token INCREMENT DECREMENT

%token ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN

%token EQ NE LT GT LE GE
%token AND OR NOT

%token LPAREN RPAREN
%token LBRACE RBRACE
%token SEMICOLON COMMA

/* Operator precedence */

%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV MOD
%right NOT

/* Fix dangling else */

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program:
        stmt_list
        ;

stmt_list:
        stmt_list stmt
        |
        ;

stmt:
        declaration
        | assignment
        | print_stmt
        | if_stmt
        | while_stmt
        | for_stmt
        | block
        ;

block:
        LBRACE stmt_list RBRACE
        ;

/* Declarations */

declaration:
        INT ID SEMICOLON
        | FLOAT ID SEMICOLON
        | BOOL ID SEMICOLON
        ;

/* Assignments */

assignment:
        ID ASSIGN expr SEMICOLON
        ;

/* Print */

print_stmt:
        PRINT LPAREN expr RPAREN SEMICOLON
        ;

/* If statement */

if_stmt:
        IF LPAREN expr RPAREN stmt %prec LOWER_THAN_ELSE
        | IF LPAREN expr RPAREN stmt ELSE stmt
        ;

/* While loop */

while_stmt:
        WHILE LPAREN expr RPAREN stmt
        ;

/* For loop */

for_stmt:
        FOR LPAREN ID ASSIGN expr SEMICOLON expr SEMICOLON ID ASSIGN expr RPAREN stmt
        ;

/* Expressions */

expr:
        expr PLUS expr
        | expr MINUS expr
        | expr MULT expr
        | expr DIV expr
        | expr MOD expr
        | expr EQ expr
        | expr NE expr
        | expr LT expr
        | expr GT expr
        | expr LE expr
        | expr GE expr
        | expr AND expr
        | expr OR expr
        | NOT expr
        | LPAREN expr RPAREN
        | NUMBER
        | ID
        ;

%%

void yyerror(const char *s)
{
    printf("\nSyntax error at line %d near '%s'\n", yylineno, yytext);
}

int main()
{
    printf("Enter program:\n");
    yyparse();
    printf("Parsing completed.\n");
    return 0;
}