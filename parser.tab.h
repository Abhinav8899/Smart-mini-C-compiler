/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    FLOAT_TYPE = 259,              /* FLOAT_TYPE  */
    BOOL = 260,                    /* BOOL  */
    STRING_TYPE = 261,             /* STRING_TYPE  */
    VOID = 262,                    /* VOID  */
    IF = 263,                      /* IF  */
    ELSE = 264,                    /* ELSE  */
    WHILE = 265,                   /* WHILE  */
    DO = 266,                      /* DO  */
    FOR = 267,                     /* FOR  */
    FUNC = 268,                    /* FUNC  */
    SWITCH = 269,                  /* SWITCH  */
    CASE = 270,                    /* CASE  */
    DEFAULT = 271,                 /* DEFAULT  */
    PRINT = 272,                   /* PRINT  */
    RETURN = 273,                  /* RETURN  */
    BREAK = 274,                   /* BREAK  */
    CONTINUE = 275,                /* CONTINUE  */
    TRUE = 276,                    /* TRUE  */
    FALSE = 277,                   /* FALSE  */
    ID = 278,                      /* ID  */
    STRING_LIT = 279,              /* STRING_LIT  */
    NUMBER = 280,                  /* NUMBER  */
    FLOAT_NUM = 281,               /* FLOAT_NUM  */
    PLUS = 282,                    /* PLUS  */
    MINUS = 283,                   /* MINUS  */
    MULT = 284,                    /* MULT  */
    DIV = 285,                     /* DIV  */
    MOD = 286,                     /* MOD  */
    INCREMENT = 287,               /* INCREMENT  */
    DECREMENT = 288,               /* DECREMENT  */
    ASSIGN = 289,                  /* ASSIGN  */
    ADD_ASSIGN = 290,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 291,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 292,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 293,              /* DIV_ASSIGN  */
    EQ = 294,                      /* EQ  */
    NE = 295,                      /* NE  */
    LT = 296,                      /* LT  */
    GT = 297,                      /* GT  */
    LE = 298,                      /* LE  */
    GE = 299,                      /* GE  */
    AND = 300,                     /* AND  */
    OR = 301,                      /* OR  */
    NOT = 302,                     /* NOT  */
    LPAREN = 303,                  /* LPAREN  */
    RPAREN = 304,                  /* RPAREN  */
    LBRACE = 305,                  /* LBRACE  */
    RBRACE = 306,                  /* RBRACE  */
    LBRACKET = 307,                /* LBRACKET  */
    RBRACKET = 308,                /* RBRACKET  */
    SEMICOLON = 309,               /* SEMICOLON  */
    COMMA = 310,                   /* COMMA  */
    COLON = 311,                   /* COLON  */
    UMINUS = 312,                  /* UMINUS  */
    LOWER_THAN_ELSE = 313          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "parser.y"

    int         num;
    float       fnum;
    char       *str;
    struct ASTNode    *node;
    struct ExprList   *elist;
    struct ParamList  *plist;
    int         dtype;          /* DataType */

#line 132 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
