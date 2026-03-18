%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
%}

%option noyywrap
%option yylineno

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*

%%

int             { return INT; }
float           { return FLOAT; }
bool            { return BOOL; }

if              { return IF; }
else            { return ELSE; }
while           { return WHILE; }
for             { return FOR; }

print           { return PRINT; }
return          { return RETURN; }

break           { return BREAK; }
continue        { return CONTINUE; }

true            { return TRUE; }
false           { return FALSE; }

"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }

"&&"            { return AND; }
"||"            { return OR; }

"++"            { return INCREMENT; }
"--"            { return DECREMENT; }

"+="            { return ADD_ASSIGN; }
"-="            { return SUB_ASSIGN; }
"*="            { return MUL_ASSIGN; }
"/="            { return DIV_ASSIGN; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }
"%"             { return MOD; }

"="             { return ASSIGN; }

"<"             { return LT; }
">"             { return GT; }

"!"             { return NOT; }

";"             { return SEMICOLON; }
","             { return COMMA; }

"("             { return LPAREN; }
")"             { return RPAREN; }

"{"             { return LBRACE; }
"}"             { return RBRACE; }

{DIGIT}+        { yylval.num = atoi(yytext); return NUMBER; }

{ID}            { return ID; }

"//".*          { }

[ \t\r\n]+      { }

. { printf("Unknown character '%s' at line %d\n", yytext, yylineno); }

%%