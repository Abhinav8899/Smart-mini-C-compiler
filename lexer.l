%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler_utils.h"
#include "parser.tab.h"

/* Column tracking (defined in compiler_utils.c) */
static void advance_col() { current_col += yyleng; }

/* Source line capture */
static char line_buf[4096];
static int  line_buf_pos = 0;

static void record_char(const char *text, int len) {
    for (int i = 0; i < len && line_buf_pos < (int)sizeof(line_buf) - 1; i++)
        line_buf[line_buf_pos++] = text[i];
}
%}

%option noyywrap
%option yylineno

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*
FLOAT   {DIGIT}+"."{DIGIT}*|"."{DIGIT}+

%%

\n {
    /* Store the completed line */
    line_buf[line_buf_pos] = '\0';
    if (source_line_count < MAX_LINES)
        source_lines[source_line_count++] = strdup(line_buf);
    line_buf_pos = 0;
    current_col = 1;
}

int             { advance_col(); record_char(yytext, yyleng); return INT; }
float           { advance_col(); record_char(yytext, yyleng); return FLOAT_TYPE; }
bool            { advance_col(); record_char(yytext, yyleng); return BOOL; }
string          { advance_col(); record_char(yytext, yyleng); return STRING_TYPE; }
void            { advance_col(); record_char(yytext, yyleng); return VOID; }

if              { advance_col(); record_char(yytext, yyleng); return IF; }
else            { advance_col(); record_char(yytext, yyleng); return ELSE; }
while           { advance_col(); record_char(yytext, yyleng); return WHILE; }
do              { advance_col(); record_char(yytext, yyleng); return DO; }
for             { advance_col(); record_char(yytext, yyleng); return FOR; }
switch          { advance_col(); record_char(yytext, yyleng); return SWITCH; }
case            { advance_col(); record_char(yytext, yyleng); return CASE; }
default         { advance_col(); record_char(yytext, yyleng); return DEFAULT; }

print           { advance_col(); record_char(yytext, yyleng); return PRINT; }
return          { advance_col(); record_char(yytext, yyleng); return RETURN; }
break           { advance_col(); record_char(yytext, yyleng); return BREAK; }
continue        { advance_col(); record_char(yytext, yyleng); return CONTINUE; }
func            { advance_col(); record_char(yytext, yyleng); return FUNC; }

true            { advance_col(); record_char(yytext, yyleng); return TRUE; }
false           { advance_col(); record_char(yytext, yyleng); return FALSE; }

"=="            { advance_col(); record_char(yytext, yyleng); return EQ; }
"!="            { advance_col(); record_char(yytext, yyleng); return NE; }
"<="            { advance_col(); record_char(yytext, yyleng); return LE; }
">="            { advance_col(); record_char(yytext, yyleng); return GE; }
"&&"            { advance_col(); record_char(yytext, yyleng); return AND; }
"||"            { advance_col(); record_char(yytext, yyleng); return OR; }
"++"            { advance_col(); record_char(yytext, yyleng); return INCREMENT; }
"--"            { advance_col(); record_char(yytext, yyleng); return DECREMENT; }
"+="            { advance_col(); record_char(yytext, yyleng); return ADD_ASSIGN; }
"-="            { advance_col(); record_char(yytext, yyleng); return SUB_ASSIGN; }
"*="            { advance_col(); record_char(yytext, yyleng); return MUL_ASSIGN; }
"/="            { advance_col(); record_char(yytext, yyleng); return DIV_ASSIGN; }

"+"             { advance_col(); record_char(yytext, yyleng); return PLUS; }
"-"             { advance_col(); record_char(yytext, yyleng); return MINUS; }
"*"             { advance_col(); record_char(yytext, yyleng); return MULT; }
"/"             { advance_col(); record_char(yytext, yyleng); return DIV; }
"%"             { advance_col(); record_char(yytext, yyleng); return MOD; }
"="             { advance_col(); record_char(yytext, yyleng); return ASSIGN; }
"<"             { advance_col(); record_char(yytext, yyleng); return LT; }
">"             { advance_col(); record_char(yytext, yyleng); return GT; }
"!"             { advance_col(); record_char(yytext, yyleng); return NOT; }
";"             { advance_col(); record_char(yytext, yyleng); return SEMICOLON; }
","             { advance_col(); record_char(yytext, yyleng); return COMMA; }
"("             { advance_col(); record_char(yytext, yyleng); return LPAREN; }
")"             { advance_col(); record_char(yytext, yyleng); return RPAREN; }
"{"             { advance_col(); record_char(yytext, yyleng); return LBRACE; }
"}"             { advance_col(); record_char(yytext, yyleng); return RBRACE; }
"["             { advance_col(); record_char(yytext, yyleng); return LBRACKET; }
"]"             { advance_col(); record_char(yytext, yyleng); return RBRACKET; }
":"             { advance_col(); record_char(yytext, yyleng); return COLON; }

{FLOAT}         {
                  yylval.fnum = atof(yytext);
                  advance_col();
                  record_char(yytext, yyleng);
                  return FLOAT_NUM;
                }

{DIGIT}+        {
                  yylval.num = atoi(yytext);
                  advance_col();
                  record_char(yytext, yyleng);
                  return NUMBER;
                }

\"([^\"\\]|\\.)*\" {
                  /* String literal — strip surrounding quotes */
                  char *s = strdup(yytext + 1);
                  s[strlen(s) - 1] = '\0';
                  yylval.str = s;
                  advance_col();
                  record_char(yytext, yyleng);
                  return STRING_LIT;
                }

{ID}            {
                  yylval.str = strdup(yytext);
                  advance_col();
                  record_char(yytext, yyleng);
                  return ID;
                }

"//".*          { advance_col(); record_char(yytext, yyleng); /* line comment */ }

[ \t\r]+        { advance_col(); record_char(yytext, yyleng); }

.               {
                  char msg[128];
                  snprintf(msg, sizeof(msg),
                           "Unknown character '%s'.", yytext);
                  report_error(yylineno, current_col, msg);
                  advance_col();
                  record_char(yytext, yyleng);
                }

%%
