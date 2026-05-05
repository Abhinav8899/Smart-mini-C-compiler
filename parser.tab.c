/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 92 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT_TYPE = 4,                 /* FLOAT_TYPE  */
  YYSYMBOL_BOOL = 5,                       /* BOOL  */
  YYSYMBOL_STRING_TYPE = 6,                /* STRING_TYPE  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_DO = 11,                        /* DO  */
  YYSYMBOL_FOR = 12,                       /* FOR  */
  YYSYMBOL_FUNC = 13,                      /* FUNC  */
  YYSYMBOL_SWITCH = 14,                    /* SWITCH  */
  YYSYMBOL_CASE = 15,                      /* CASE  */
  YYSYMBOL_DEFAULT = 16,                   /* DEFAULT  */
  YYSYMBOL_PRINT = 17,                     /* PRINT  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_BREAK = 19,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 20,                  /* CONTINUE  */
  YYSYMBOL_TRUE = 21,                      /* TRUE  */
  YYSYMBOL_FALSE = 22,                     /* FALSE  */
  YYSYMBOL_ID = 23,                        /* ID  */
  YYSYMBOL_STRING_LIT = 24,                /* STRING_LIT  */
  YYSYMBOL_NUMBER = 25,                    /* NUMBER  */
  YYSYMBOL_FLOAT_NUM = 26,                 /* FLOAT_NUM  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_MULT = 29,                      /* MULT  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_MOD = 31,                       /* MOD  */
  YYSYMBOL_INCREMENT = 32,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 33,                 /* DECREMENT  */
  YYSYMBOL_ASSIGN = 34,                    /* ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 35,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 36,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 37,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 38,                /* DIV_ASSIGN  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_NE = 40,                        /* NE  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_OR = 46,                        /* OR  */
  YYSYMBOL_NOT = 47,                       /* NOT  */
  YYSYMBOL_LPAREN = 48,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 49,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 50,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 51,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 52,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 53,                  /* RBRACKET  */
  YYSYMBOL_SEMICOLON = 54,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 55,                     /* COMMA  */
  YYSYMBOL_COLON = 56,                     /* COLON  */
  YYSYMBOL_UMINUS = 57,                    /* UMINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 58,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_program = 60,                   /* program  */
  YYSYMBOL_stmt_list = 61,                 /* stmt_list  */
  YYSYMBOL_stmt = 62,                      /* stmt  */
  YYSYMBOL_block = 63,                     /* block  */
  YYSYMBOL_64_1 = 64,                      /* $@1  */
  YYSYMBOL_65_2 = 65,                      /* $@2  */
  YYSYMBOL_type_spec = 66,                 /* type_spec  */
  YYSYMBOL_declaration = 67,               /* declaration  */
  YYSYMBOL_assignment = 68,                /* assignment  */
  YYSYMBOL_print_stmt = 69,                /* print_stmt  */
  YYSYMBOL_return_stmt = 70,               /* return_stmt  */
  YYSYMBOL_if_stmt = 71,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 72,                /* while_stmt  */
  YYSYMBOL_do_while_stmt = 73,             /* do_while_stmt  */
  YYSYMBOL_switch_stmt = 74,               /* switch_stmt  */
  YYSYMBOL_case_list = 75,                 /* case_list  */
  YYSYMBOL_case_item = 76,                 /* case_item  */
  YYSYMBOL_array_decl = 77,                /* array_decl  */
  YYSYMBOL_array_assign = 78,              /* array_assign  */
  YYSYMBOL_for_stmt = 79,                  /* for_stmt  */
  YYSYMBOL_func_decl = 80,                 /* func_decl  */
  YYSYMBOL_81_3 = 81,                      /* $@3  */
  YYSYMBOL_param_list = 82,                /* param_list  */
  YYSYMBOL_param_list_ne = 83,             /* param_list_ne  */
  YYSYMBOL_func_call_stmt = 84,            /* func_call_stmt  */
  YYSYMBOL_arg_list = 85,                  /* arg_list  */
  YYSYMBOL_arg_list_ne = 86,               /* arg_list_ne  */
  YYSYMBOL_expr = 87                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   699

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    82,    83,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   106,   106,   107,   107,   112,   113,   114,   115,   116,
     121,   133,   156,   169,   177,   184,   191,   198,   207,   219,
     227,   231,   239,   245,   255,   264,   273,   281,   291,   295,
     302,   313,   327,   346,   364,   364,   386,   387,   391,   394,
     401,   409,   410,   414,   415,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   437,   438,   439,   440,   442,   447,   448,   449,   450,
     451,   452,   467
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT_TYPE",
  "BOOL", "STRING_TYPE", "VOID", "IF", "ELSE", "WHILE", "DO", "FOR",
  "FUNC", "SWITCH", "CASE", "DEFAULT", "PRINT", "RETURN", "BREAK",
  "CONTINUE", "TRUE", "FALSE", "ID", "STRING_LIT", "NUMBER", "FLOAT_NUM",
  "PLUS", "MINUS", "MULT", "DIV", "MOD", "INCREMENT", "DECREMENT",
  "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "EQ",
  "NE", "LT", "GT", "LE", "GE", "AND", "OR", "NOT", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "SEMICOLON", "COMMA",
  "COLON", "UMINUS", "LOWER_THAN_ELSE", "$accept", "program", "stmt_list",
  "stmt", "block", "$@1", "$@2", "type_spec", "declaration", "assignment",
  "print_stmt", "return_stmt", "if_stmt", "while_stmt", "do_while_stmt",
  "switch_stmt", "case_list", "case_item", "array_decl", "array_assign",
  "for_stmt", "func_decl", "$@3", "param_list", "param_list_ne",
  "func_call_stmt", "arg_list", "arg_list_ne", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -65,     5,   206,   -65,   -65,   -65,   -65,   -65,   -65,   -41,
     -23,   206,    -6,     6,     1,    11,    68,   -34,     7,   209,
     -65,   -65,   -65,    20,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,    -7,    -7,    50,
      60,    72,    -7,    -7,   -65,   -65,   -14,   -65,   -65,   -65,
      -7,    -7,   227,   -65,   257,   -65,   -65,    52,    53,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,   -65,    62,   -28,   136,
     497,    69,    74,    70,   520,   543,    -7,    -7,   -65,   -65,
      71,    75,    76,    77,   566,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,   -65,   -65,
     -65,   277,   297,   317,   337,   357,    78,    64,   635,   457,
     133,   -65,    -7,    96,   -65,   206,   206,    -7,    -7,     6,
      73,    80,    79,   477,    -7,    -7,    -7,    -7,   -65,    27,
      27,   -65,   -65,   -65,    57,    57,     2,     2,     2,     2,
     655,    24,   -65,   -65,   -65,   -65,   -65,    88,    -7,    97,
     -65,   377,    95,   121,   -65,   589,   397,   126,   105,   102,
     -65,   -65,   -65,   -65,   635,   635,   635,   635,   -65,   635,
      -7,   -65,   104,   206,   107,    -7,   -65,   -65,     6,   -12,
     417,   -65,   -65,   -65,   437,   109,   145,    -7,   113,   -65,
     -65,   -65,   147,   -65,   -65,   237,   -65,   137,   185,   -65,
     206,    -7,   -65,   206,   612,   206,   -65
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    25,    26,    27,    28,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     3,    18,     0,     5,     6,     9,    10,    11,    12,
      13,    15,     7,     8,    14,    16,    17,     0,     0,     0,
       0,     0,     0,     0,    88,    89,    92,    90,    86,    87,
       0,     0,     0,    41,     0,    19,    20,     0,     0,     0,
       0,     0,     0,     0,    62,     0,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    62,     0,    79,    78,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    40,    37,
      38,     0,     0,     0,     0,     0,     0,    61,    63,     0,
       0,    24,     0,     0,    30,     0,     0,     0,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,    80,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    32,    33,    34,    35,    36,     0,     0,     0,
      22,     0,     0,    42,    44,     0,     0,     0,     0,    56,
      48,    39,    85,    91,    81,    82,    83,    84,    60,    64,
       0,    31,     0,     0,     0,     0,    58,    54,     0,     0,
       0,    51,    43,    45,     0,     0,     0,     0,     0,    46,
      47,    52,     0,     4,    59,     0,     4,     0,     0,     4,
      50,     0,    55,    49,     0,     0,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,   -65,   -64,   -11,   -65,   -65,   -65,    -5,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,    98,   -65,   -15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    21,    22,    66,    67,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   179,   190,    32,    33,
      34,    35,   185,   158,   159,    36,   106,   107,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      39,    54,   110,   187,   188,     3,   112,    37,    41,     4,
       5,     6,     7,     8,    44,    45,    46,    47,    48,    49,
      55,    50,    69,    70,   113,    38,   114,    74,    75,    85,
      86,    87,    88,    89,    76,    78,    79,    84,    77,   189,
      51,    52,    40,    68,   101,   102,   103,   104,   105,    42,
     109,    85,    86,    87,    88,    89,    87,    88,    89,    43,
      71,    56,   123,    90,    91,    92,    93,    94,    95,    96,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,    72,    85,    86,    87,    88,    89,    44,
      45,    46,    47,    48,    49,    73,    50,   151,    92,    93,
      94,    95,   155,   156,   153,   154,    99,   100,   118,   164,
     165,   166,   167,   111,   157,    51,    52,   117,   119,   148,
     124,   152,    53,   160,   125,   126,   127,   147,   162,   198,
     173,   170,   200,   169,   161,   203,     4,     5,     6,     7,
       8,     9,   168,    10,    11,    12,    13,    14,   172,   176,
      15,    16,    17,    18,   177,   180,    19,   178,   181,   193,
     184,   183,   182,    85,    86,    87,    88,    89,   194,   196,
     197,   201,   195,   186,   122,    90,    91,    92,    93,    94,
      95,    96,    97,    20,   150,   115,   204,     0,     4,     5,
       6,     7,     8,     9,   206,    10,    11,    12,    13,    14,
       0,     0,    15,    16,    17,    18,     0,     0,    19,     4,
       5,     6,     7,     8,     9,     0,    10,    11,    12,    13,
      14,     0,     0,    15,    16,    17,    18,     0,     0,    19,
      80,    81,    82,    83,     0,    20,   202,     0,     0,     0,
       0,    57,    58,    59,    60,    61,    62,    63,    44,    45,
      46,    47,    48,    49,     0,    50,    20,    64,     0,     0,
       0,    65,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,     0,    51,    52,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,     0,     0,   199,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,    98,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   142,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   143,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   144,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   145,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   146,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   171,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   175,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   191,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
       0,   192,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
     149,     0,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,    85,    86,    87,    88,    89,     0,
     163,     0,     0,     0,     0,     0,    90,    91,    92,    93,
      94,    95,    96,    97,     0,     0,   116,    85,    86,    87,
      88,    89,     0,     0,     0,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,    96,    97,     0,     0,   120,
      85,    86,    87,    88,    89,     0,     0,     0,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,    96,    97,
       0,     0,   121,    85,    86,    87,    88,    89,     0,     0,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,    96,    97,     0,     0,   128,    85,    86,    87,    88,
      89,     0,     0,     0,     0,     0,     0,     0,    90,    91,
      92,    93,    94,    95,    96,    97,     0,     0,   174,    85,
      86,    87,    88,    89,     0,     0,     0,     0,     0,     0,
       0,    90,    91,    92,    93,    94,    95,    96,    97,     0,
       0,   205,    85,    86,    87,    88,    89,     0,     0,     0,
       0,     0,     0,     0,    90,    91,    92,    93,    94,    95,
      96,    97,    85,    86,    87,    88,    89,     0,     0,     0,
       0,     0,     0,     0,    90,    91,    92,    93,    94,    95
};

static const yytype_int16 yycheck[] =
{
      11,    16,    66,    15,    16,     0,    34,    48,    13,     3,
       4,     5,     6,     7,    21,    22,    23,    24,    25,    26,
      54,    28,    37,    38,    52,    48,    54,    42,    43,    27,
      28,    29,    30,    31,    48,    50,    51,    52,    52,    51,
      47,    48,    48,    23,    59,    60,    61,    62,    63,    48,
      65,    27,    28,    29,    30,    31,    29,    30,    31,    48,
      10,    54,    77,    39,    40,    41,    42,    43,    44,    45,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    23,    27,    28,    29,    30,    31,    21,
      22,    23,    24,    25,    26,    23,    28,   112,    41,    42,
      43,    44,   117,   118,   115,   116,    54,    54,    34,   124,
     125,   126,   127,    51,   119,    47,    48,    48,    48,    55,
      49,    25,    54,    50,    49,    49,    49,    49,    49,   193,
       9,    34,   196,   148,    54,   199,     3,     4,     5,     6,
       7,     8,    54,    10,    11,    12,    13,    14,    53,    23,
      17,    18,    19,    20,    49,   170,    23,    55,    54,    50,
     175,    54,   173,    27,    28,    29,    30,    31,    23,    56,
      23,    34,   187,   178,    76,    39,    40,    41,    42,    43,
      44,    45,    46,    50,    51,    49,   201,    -1,     3,     4,
       5,     6,     7,     8,   205,    10,    11,    12,    13,    14,
      -1,    -1,    17,    18,    19,    20,    -1,    -1,    23,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
      14,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    23,
       3,     4,     5,     6,    -1,    50,    51,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    36,    37,    38,    21,    22,
      23,    24,    25,    26,    -1,    28,    50,    48,    -1,    -1,
      -1,    52,    -1,    -1,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    47,    48,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    27,    28,    29,    30,    31,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    -1,    49,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    49,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    49,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    49,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    -1,    -1,    49,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    49,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    60,    61,     0,     3,     4,     5,     6,     7,     8,
      10,    11,    12,    13,    14,    17,    18,    19,    20,    23,
      50,    62,    63,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    77,    78,    79,    80,    84,    48,    48,    62,
      48,    66,    48,    48,    21,    22,    23,    24,    25,    26,
      28,    47,    48,    54,    87,    54,    54,    32,    33,    34,
      35,    36,    37,    38,    48,    52,    64,    65,    23,    87,
      87,    10,    23,    23,    87,    87,    48,    52,    87,    87,
       3,     4,     5,     6,    87,    27,    28,    29,    30,    31,
      39,    40,    41,    42,    43,    44,    45,    46,    54,    54,
      54,    87,    87,    87,    87,    87,    85,    86,    87,    87,
      61,    51,    34,    52,    54,    49,    49,    48,    34,    48,
      49,    49,    85,    87,    49,    49,    49,    49,    49,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    54,    54,    54,    54,    54,    49,    55,    53,
      51,    87,    25,    62,    62,    87,    87,    66,    82,    83,
      50,    54,    49,    53,    87,    87,    87,    87,    54,    87,
      34,    54,    53,     9,    49,    54,    23,    49,    55,    75,
      87,    54,    62,    54,    87,    81,    66,    15,    16,    51,
      76,    54,    54,    50,    23,    87,    56,    23,    61,    56,
      61,    34,    51,    61,    87,    49,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    64,    63,    65,    63,    66,    66,    66,    66,    66,
      67,    67,    68,    68,    68,    68,    68,    68,    68,    69,
      70,    70,    71,    71,    72,    73,    74,    75,    75,    76,
      76,    77,    78,    79,    81,    80,    82,    82,    83,    83,
      84,    85,    85,    86,    86,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     0,     4,     0,     3,     1,     1,     1,     1,     1,
       3,     5,     4,     4,     4,     4,     4,     3,     3,     5,
       3,     2,     5,     7,     5,     7,     7,     2,     0,     4,
       3,     6,     7,    13,     0,    10,     1,     0,     2,     4,
       5,     1,     0,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     4,     4,     4,     4,     4,     1,     1,     1,     1,
       1,     4,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmt_list  */
#line 78 "parser.y"
                { root = (yyvsp[0].node); }
#line 1399 "parser.tab.c"
    break;

  case 3: /* stmt_list: stmt_list stmt  */
#line 82 "parser.y"
                      { (yyval.node) = create_seq_node((yyvsp[0].node), (yyvsp[-1].node)); }
#line 1405 "parser.tab.c"
    break;

  case 4: /* stmt_list: %empty  */
#line 83 "parser.y"
                      { (yyval.node) = NULL; }
#line 1411 "parser.tab.c"
    break;

  case 5: /* stmt: declaration  */
#line 87 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1417 "parser.tab.c"
    break;

  case 6: /* stmt: assignment  */
#line 88 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1423 "parser.tab.c"
    break;

  case 7: /* stmt: array_decl  */
#line 89 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1429 "parser.tab.c"
    break;

  case 8: /* stmt: array_assign  */
#line 90 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1435 "parser.tab.c"
    break;

  case 9: /* stmt: print_stmt  */
#line 91 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1441 "parser.tab.c"
    break;

  case 10: /* stmt: return_stmt  */
#line 92 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1447 "parser.tab.c"
    break;

  case 11: /* stmt: if_stmt  */
#line 93 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1453 "parser.tab.c"
    break;

  case 12: /* stmt: while_stmt  */
#line 94 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1459 "parser.tab.c"
    break;

  case 13: /* stmt: do_while_stmt  */
#line 95 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1465 "parser.tab.c"
    break;

  case 14: /* stmt: for_stmt  */
#line 96 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1471 "parser.tab.c"
    break;

  case 15: /* stmt: switch_stmt  */
#line 97 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1477 "parser.tab.c"
    break;

  case 16: /* stmt: func_decl  */
#line 98 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1483 "parser.tab.c"
    break;

  case 17: /* stmt: func_call_stmt  */
#line 99 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1489 "parser.tab.c"
    break;

  case 18: /* stmt: block  */
#line 100 "parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1495 "parser.tab.c"
    break;

  case 19: /* stmt: BREAK SEMICOLON  */
#line 101 "parser.y"
                        { (yyval.node) = at(create_node(NODE_BREAK)); }
#line 1501 "parser.tab.c"
    break;

  case 20: /* stmt: CONTINUE SEMICOLON  */
#line 102 "parser.y"
                         { (yyval.node) = at(create_node(NODE_CONTINUE)); }
#line 1507 "parser.tab.c"
    break;

  case 21: /* $@1: %empty  */
#line 106 "parser.y"
             {push_scope();}
#line 1513 "parser.tab.c"
    break;

  case 22: /* block: LBRACE $@1 stmt_list RBRACE  */
#line 106 "parser.y"
                                              { pop_scope(); (yyval.node) = (yyvsp[-1].node); }
#line 1519 "parser.tab.c"
    break;

  case 23: /* $@2: %empty  */
#line 107 "parser.y"
             {push_scope();}
#line 1525 "parser.tab.c"
    break;

  case 24: /* block: LBRACE $@2 RBRACE  */
#line 107 "parser.y"
                                    { pop_scope(); (yyval.node) = NULL; }
#line 1531 "parser.tab.c"
    break;

  case 25: /* type_spec: INT  */
#line 112 "parser.y"
                  { (yyval.dtype) = TYPE_INT;    }
#line 1537 "parser.tab.c"
    break;

  case 26: /* type_spec: FLOAT_TYPE  */
#line 113 "parser.y"
                  { (yyval.dtype) = TYPE_FLOAT;  }
#line 1543 "parser.tab.c"
    break;

  case 27: /* type_spec: BOOL  */
#line 114 "parser.y"
                  { (yyval.dtype) = TYPE_BOOL;   }
#line 1549 "parser.tab.c"
    break;

  case 28: /* type_spec: STRING_TYPE  */
#line 115 "parser.y"
                  { (yyval.dtype) = TYPE_STRING; }
#line 1555 "parser.tab.c"
    break;

  case 29: /* type_spec: VOID  */
#line 116 "parser.y"
                  { (yyval.dtype) = TYPE_VOID;   }
#line 1561 "parser.tab.c"
    break;

  case 30: /* declaration: type_spec ID SEMICOLON  */
#line 121 "parser.y"
                             {
        if (lookup_current_scope((yyvsp[-1].str))) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Variable '%s' already declared in this scope.", (yyvsp[-1].str));
            report_error(yylineno, current_col, msg);
        } else {
            insert_symbol((yyvsp[-1].str), (DataType)(yyvsp[-2].dtype));
        }
        (yyval.node) = at(create_node(NODE_DECL));
        (yyval.node)->data.decl.var_type = (yyvsp[-2].dtype);
        (yyval.node)->data.decl.name     = strdup((yyvsp[-1].str));
      }
#line 1578 "parser.tab.c"
    break;

  case 31: /* declaration: type_spec ID ASSIGN expr SEMICOLON  */
#line 133 "parser.y"
                                         {
        /* Declaration with initializer */
        if (lookup_current_scope((yyvsp[-3].str))) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Variable '%s' already declared in this scope.", (yyvsp[-3].str));
            report_error(yylineno, current_col, msg);
        } else {
            insert_symbol((yyvsp[-3].str), (DataType)(yyvsp[-4].dtype));
        }
        ASTNode *decl = at(create_node(NODE_DECL));
        decl->data.decl.var_type = (yyvsp[-4].dtype);
        decl->data.decl.name     = strdup((yyvsp[-3].str));

        ASTNode *asn = at(create_node(NODE_ASSIGN));
        asn->data.assign.name = strdup((yyvsp[-3].str));
        asn->data.assign.expr = (yyvsp[-1].node);

        (yyval.node) = create_seq_node(asn, decl);
      }
#line 1602 "parser.tab.c"
    break;

  case 32: /* assignment: ID ASSIGN expr SEMICOLON  */
#line 156 "parser.y"
                               {
        if (!lookup_symbol((yyvsp[-3].str))) {
            char msg[256];
            char *sug = closest_symbol((yyvsp[-3].str));
            if (sug) snprintf(msg, sizeof(msg), "Undeclared variable '%s'. Did you mean '%s'?", (yyvsp[-3].str), sug);
            else     snprintf(msg, sizeof(msg), "Undeclared variable '%s'.", (yyvsp[-3].str));
            report_error(yylineno, current_col, msg);
        }
        (yyval.node) = at(create_node(NODE_ASSIGN));
        (yyval.node)->data.assign.name = strdup((yyvsp[-3].str));
        (yyval.node)->data.assign.expr = (yyvsp[-1].node);
        (yyval.node)->data.assign.op   = 0;
      }
#line 1620 "parser.tab.c"
    break;

  case 33: /* assignment: ID ADD_ASSIGN expr SEMICOLON  */
#line 169 "parser.y"
                                   {
        /* Desugar: x += e  →  x = x + e */
        ASTNode *id = at(create_id_node((yyvsp[-3].str)));
        ASTNode *rhs = create_binop_node(PLUS, id, (yyvsp[-1].node));
        (yyval.node) = at(create_node(NODE_ASSIGN));
        (yyval.node)->data.assign.name = strdup((yyvsp[-3].str));
        (yyval.node)->data.assign.expr = rhs;
      }
#line 1633 "parser.tab.c"
    break;

  case 34: /* assignment: ID SUB_ASSIGN expr SEMICOLON  */
#line 177 "parser.y"
                                   {
        ASTNode *id = at(create_id_node((yyvsp[-3].str)));
        ASTNode *rhs = create_binop_node(MINUS, id, (yyvsp[-1].node));
        (yyval.node) = at(create_node(NODE_ASSIGN));
        (yyval.node)->data.assign.name = strdup((yyvsp[-3].str));
        (yyval.node)->data.assign.expr = rhs;
      }
#line 1645 "parser.tab.c"
    break;

  case 35: /* assignment: ID MUL_ASSIGN expr SEMICOLON  */
#line 184 "parser.y"
                                   {
        ASTNode *id = at(create_id_node((yyvsp[-3].str)));
        ASTNode *rhs = create_binop_node(MULT, id, (yyvsp[-1].node));
        (yyval.node) = at(create_node(NODE_ASSIGN));
        (yyval.node)->data.assign.name = strdup((yyvsp[-3].str));
        (yyval.node)->data.assign.expr = rhs;
      }
#line 1657 "parser.tab.c"
    break;

  case 36: /* assignment: ID DIV_ASSIGN expr SEMICOLON  */
#line 191 "parser.y"
                                   {
        ASTNode *id = at(create_id_node((yyvsp[-3].str)));
        ASTNode *rhs = create_binop_node(DIV, id, (yyvsp[-1].node));
        (yyval.node) = at(create_node(NODE_ASSIGN));
        (yyval.node)->data.assign.name = strdup((yyvsp[-3].str));
        (yyval.node)->data.assign.expr = rhs;
      }
#line 1669 "parser.tab.c"
    break;

  case 37: /* assignment: ID INCREMENT SEMICOLON  */
#line 198 "parser.y"
                             {
        /* i++  →  i = i + 1 */
        ASTNode *id  = at(create_id_node((yyvsp[-2].str)));
        ASTNode *one = create_num_node(1);
        ASTNode *rhs = create_binop_node(PLUS, id, one);
        (yyval.node) = at(create_node(NODE_ASSIGN));
        (yyval.node)->data.assign.name = strdup((yyvsp[-2].str));
        (yyval.node)->data.assign.expr = rhs;
      }
#line 1683 "parser.tab.c"
    break;

  case 38: /* assignment: ID DECREMENT SEMICOLON  */
#line 207 "parser.y"
                             {
        ASTNode *id  = at(create_id_node((yyvsp[-2].str)));
        ASTNode *one = create_num_node(1);
        ASTNode *rhs = create_binop_node(MINUS, id, one);
        (yyval.node) = at(create_node(NODE_ASSIGN));
        (yyval.node)->data.assign.name = strdup((yyvsp[-2].str));
        (yyval.node)->data.assign.expr = rhs;
      }
#line 1696 "parser.tab.c"
    break;

  case 39: /* print_stmt: PRINT LPAREN expr RPAREN SEMICOLON  */
#line 219 "parser.y"
                                         {
        (yyval.node) = at(create_node(NODE_PRINT));
        (yyval.node)->data.single_expr.expr = (yyvsp[-2].node);
      }
#line 1705 "parser.tab.c"
    break;

  case 40: /* return_stmt: RETURN expr SEMICOLON  */
#line 227 "parser.y"
                            {
        (yyval.node) = at(create_node(NODE_RETURN));
        (yyval.node)->data.single_expr.expr = (yyvsp[-1].node);
      }
#line 1714 "parser.tab.c"
    break;

  case 41: /* return_stmt: RETURN SEMICOLON  */
#line 231 "parser.y"
                       {
        (yyval.node) = at(create_node(NODE_RETURN));
        (yyval.node)->data.single_expr.expr = NULL;
      }
#line 1723 "parser.tab.c"
    break;

  case 42: /* if_stmt: IF LPAREN expr RPAREN stmt  */
#line 239 "parser.y"
                                                       {
        (yyval.node) = at(create_node(NODE_IF));
        (yyval.node)->data.if_stmt.cond      = (yyvsp[-2].node);
        (yyval.node)->data.if_stmt.if_body   = (yyvsp[0].node);
        (yyval.node)->data.if_stmt.else_body = NULL;
      }
#line 1734 "parser.tab.c"
    break;

  case 43: /* if_stmt: IF LPAREN expr RPAREN stmt ELSE stmt  */
#line 245 "parser.y"
                                           {
        (yyval.node) = at(create_node(NODE_IF));
        (yyval.node)->data.if_stmt.cond      = (yyvsp[-4].node);
        (yyval.node)->data.if_stmt.if_body   = (yyvsp[-2].node);
        (yyval.node)->data.if_stmt.else_body = (yyvsp[0].node);
      }
#line 1745 "parser.tab.c"
    break;

  case 44: /* while_stmt: WHILE LPAREN expr RPAREN stmt  */
#line 255 "parser.y"
                                    {
        (yyval.node) = at(create_node(NODE_WHILE));
        (yyval.node)->data.while_stmt.cond = (yyvsp[-2].node);
        (yyval.node)->data.while_stmt.body = (yyvsp[0].node);
      }
#line 1755 "parser.tab.c"
    break;

  case 45: /* do_while_stmt: DO stmt WHILE LPAREN expr RPAREN SEMICOLON  */
#line 264 "parser.y"
                                                 {
        (yyval.node) = at(create_node(NODE_DO_WHILE));
        (yyval.node)->data.do_while.body = (yyvsp[-5].node);
        (yyval.node)->data.do_while.cond = (yyvsp[-2].node);
      }
#line 1765 "parser.tab.c"
    break;

  case 46: /* switch_stmt: SWITCH LPAREN expr RPAREN LBRACE case_list RBRACE  */
#line 273 "parser.y"
                                                        {
        (yyval.node) = at(create_node(NODE_SWITCH));
        (yyval.node)->data.sw.expr  = (yyvsp[-4].node);
        (yyval.node)->data.sw.cases = (yyvsp[-1].node);
      }
#line 1775 "parser.tab.c"
    break;

  case 47: /* case_list: case_list case_item  */
#line 281 "parser.y"
                          { (yyval.node) = (yyvsp[-1].node);
        /* Append $2 at tail of linked list */
        ASTNode *c = (yyvsp[-1].node);
        if (!c) { (yyval.node) = (yyvsp[0].node); }
        else {
            while (c->data.cas.next_case) c = c->data.cas.next_case;
            c->data.cas.next_case = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
      }
#line 1790 "parser.tab.c"
    break;

  case 48: /* case_list: %empty  */
#line 291 "parser.y"
                  { (yyval.node) = NULL; }
#line 1796 "parser.tab.c"
    break;

  case 49: /* case_item: CASE expr COLON stmt_list  */
#line 295 "parser.y"
                                {
        (yyval.node) = at(create_node(NODE_CASE));
        (yyval.node)->data.cas.is_default = 0;
        (yyval.node)->data.cas.val        = (yyvsp[-2].node);
        (yyval.node)->data.cas.body       = (yyvsp[0].node);
        (yyval.node)->data.cas.next_case  = NULL;
      }
#line 1808 "parser.tab.c"
    break;

  case 50: /* case_item: DEFAULT COLON stmt_list  */
#line 302 "parser.y"
                              {
        (yyval.node) = at(create_node(NODE_CASE));
        (yyval.node)->data.cas.is_default = 1;
        (yyval.node)->data.cas.val        = NULL;
        (yyval.node)->data.cas.body       = (yyvsp[0].node);
        (yyval.node)->data.cas.next_case  = NULL;
      }
#line 1820 "parser.tab.c"
    break;

  case 51: /* array_decl: type_spec ID LBRACKET NUMBER RBRACKET SEMICOLON  */
#line 313 "parser.y"
                                                      {
        if (lookup_current_scope((yyvsp[-4].str))) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Array '%s' already declared in this scope.", (yyvsp[-4].str));
            report_error(yylineno, current_col, msg);
        } else {
            insert_array_symbol((yyvsp[-4].str), (DataType)(yyvsp[-5].dtype), (yyvsp[-2].num));
        }
        (yyval.node) = at(create_array_decl_node((DataType)(yyvsp[-5].dtype), (yyvsp[-4].str), (yyvsp[-2].num)));
      }
#line 1835 "parser.tab.c"
    break;

  case 52: /* array_assign: ID LBRACKET expr RBRACKET ASSIGN expr SEMICOLON  */
#line 327 "parser.y"
                                                      {
        Symbol *sym = lookup_symbol((yyvsp[-6].str));
        if (!sym) {
            char msg[256];
            char *sug = closest_symbol((yyvsp[-6].str));
            if (sug) snprintf(msg, sizeof(msg), "Undeclared array '%s'. Did you mean '%s'?", (yyvsp[-6].str), sug);
            else     snprintf(msg, sizeof(msg), "Undeclared array '%s'.", (yyvsp[-6].str));
            report_error(yylineno, current_col, msg);
        } else if (!sym->is_array) {
            char msg[128];
            snprintf(msg, sizeof(msg), "'%s' is not an array.", (yyvsp[-6].str));
            report_error(yylineno, current_col, msg);
        }
        (yyval.node) = at(create_array_assign_node((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node)));
      }
#line 1855 "parser.tab.c"
    break;

  case 53: /* for_stmt: FOR LPAREN ID ASSIGN expr SEMICOLON expr SEMICOLON ID ASSIGN expr RPAREN stmt  */
#line 346 "parser.y"
                                                                                    {
        if (!lookup_symbol((yyvsp[-10].str))) {
            char msg[128];
            snprintf(msg, sizeof(msg), "Undeclared variable '%s' in for-init.", (yyvsp[-10].str));
            report_error(yylineno, current_col, msg);
        }
        (yyval.node) = at(create_node(NODE_FOR));
        (yyval.node)->data.for_stmt.init_id   = strdup((yyvsp[-10].str));
        (yyval.node)->data.for_stmt.init_expr = (yyvsp[-8].node);
        (yyval.node)->data.for_stmt.cond      = (yyvsp[-6].node);
        (yyval.node)->data.for_stmt.inc_id    = strdup((yyvsp[-4].str));
        (yyval.node)->data.for_stmt.inc_expr  = (yyvsp[-2].node);
        (yyval.node)->data.for_stmt.body      = (yyvsp[0].node);
      }
#line 1874 "parser.tab.c"
    break;

  case 54: /* $@3: %empty  */
#line 364 "parser.y"
                                                 {
        /* Register function in current (outer) scope */
        ParamList *p = (yyvsp[-1].plist);
        DataType ptypes[8]; int pc = 0;
        while (p && pc < 8) { ptypes[pc++] = p->type; p = p->next; }
        insert_func_symbol((yyvsp[-3].str), (DataType)(yyvsp[-4].dtype), ptypes, pc);
        /* Push scope and insert params BEFORE parsing body */
        push_scope();
        p = (yyvsp[-1].plist);
        while (p) { insert_symbol(p->name, p->type); p = p->next; }
      }
#line 1890 "parser.tab.c"
    break;

  case 55: /* func_decl: FUNC type_spec ID LPAREN param_list RPAREN $@3 LBRACE stmt_list RBRACE  */
#line 375 "parser.y"
                              {
        pop_scope();
        (yyval.node) = at(create_node(NODE_FUNC_DECL));
        (yyval.node)->data.func_decl.name     = strdup((yyvsp[-7].str));
        (yyval.node)->data.func_decl.ret_type = (DataType)(yyvsp[-8].dtype);
        (yyval.node)->data.func_decl.params   = (yyvsp[-5].plist);
        (yyval.node)->data.func_decl.body     = (yyvsp[-1].node);
      }
#line 1903 "parser.tab.c"
    break;

  case 56: /* param_list: param_list_ne  */
#line 386 "parser.y"
                     { (yyval.plist) = (yyvsp[0].plist); }
#line 1909 "parser.tab.c"
    break;

  case 57: /* param_list: %empty  */
#line 387 "parser.y"
                     { (yyval.plist) = NULL; }
#line 1915 "parser.tab.c"
    break;

  case 58: /* param_list_ne: type_spec ID  */
#line 391 "parser.y"
                   {
        (yyval.plist) = create_param((yyvsp[0].str), (DataType)(yyvsp[-1].dtype), NULL);
      }
#line 1923 "parser.tab.c"
    break;

  case 59: /* param_list_ne: param_list_ne COMMA type_spec ID  */
#line 394 "parser.y"
                                       {
        (yyval.plist) = create_param((yyvsp[0].str), (DataType)(yyvsp[-1].dtype), (yyvsp[-3].plist));
      }
#line 1931 "parser.tab.c"
    break;

  case 60: /* func_call_stmt: ID LPAREN arg_list RPAREN SEMICOLON  */
#line 401 "parser.y"
                                          {
        (yyval.node) = at(create_node(NODE_FUNC_CALL));
        (yyval.node)->data.func_call.name = strdup((yyvsp[-4].str));
        (yyval.node)->data.func_call.args = (yyvsp[-2].elist);
      }
#line 1941 "parser.tab.c"
    break;

  case 61: /* arg_list: arg_list_ne  */
#line 409 "parser.y"
                   { (yyval.elist) = (yyvsp[0].elist); }
#line 1947 "parser.tab.c"
    break;

  case 62: /* arg_list: %empty  */
#line 410 "parser.y"
                   { (yyval.elist) = NULL; }
#line 1953 "parser.tab.c"
    break;

  case 63: /* arg_list_ne: expr  */
#line 414 "parser.y"
                                 { (yyval.elist) = create_expr_list((yyvsp[0].node), NULL); }
#line 1959 "parser.tab.c"
    break;

  case 64: /* arg_list_ne: arg_list_ne COMMA expr  */
#line 415 "parser.y"
                                 { (yyval.elist) = create_expr_list((yyvsp[0].node), (yyvsp[-2].elist)); }
#line 1965 "parser.tab.c"
    break;

  case 65: /* expr: expr PLUS expr  */
#line 420 "parser.y"
                       { (yyval.node) = at(create_binop_node(PLUS,  (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1971 "parser.tab.c"
    break;

  case 66: /* expr: expr MINUS expr  */
#line 421 "parser.y"
                       { (yyval.node) = at(create_binop_node(MINUS, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1977 "parser.tab.c"
    break;

  case 67: /* expr: expr MULT expr  */
#line 422 "parser.y"
                       { (yyval.node) = at(create_binop_node(MULT,  (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1983 "parser.tab.c"
    break;

  case 68: /* expr: expr DIV expr  */
#line 423 "parser.y"
                       { (yyval.node) = at(create_binop_node(DIV,   (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1989 "parser.tab.c"
    break;

  case 69: /* expr: expr MOD expr  */
#line 424 "parser.y"
                       { (yyval.node) = at(create_binop_node(MOD,   (yyvsp[-2].node), (yyvsp[0].node))); }
#line 1995 "parser.tab.c"
    break;

  case 70: /* expr: expr EQ expr  */
#line 425 "parser.y"
                       { (yyval.node) = at(create_binop_node(EQ,    (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2001 "parser.tab.c"
    break;

  case 71: /* expr: expr NE expr  */
#line 426 "parser.y"
                       { (yyval.node) = at(create_binop_node(NE,    (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2007 "parser.tab.c"
    break;

  case 72: /* expr: expr LT expr  */
#line 427 "parser.y"
                       { (yyval.node) = at(create_binop_node(LT,    (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2013 "parser.tab.c"
    break;

  case 73: /* expr: expr GT expr  */
#line 428 "parser.y"
                       { (yyval.node) = at(create_binop_node(GT,    (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2019 "parser.tab.c"
    break;

  case 74: /* expr: expr LE expr  */
#line 429 "parser.y"
                       { (yyval.node) = at(create_binop_node(LE,    (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2025 "parser.tab.c"
    break;

  case 75: /* expr: expr GE expr  */
#line 430 "parser.y"
                       { (yyval.node) = at(create_binop_node(GE,    (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2031 "parser.tab.c"
    break;

  case 76: /* expr: expr AND expr  */
#line 431 "parser.y"
                       { (yyval.node) = at(create_binop_node(AND,   (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2037 "parser.tab.c"
    break;

  case 77: /* expr: expr OR expr  */
#line 432 "parser.y"
                       { (yyval.node) = at(create_binop_node(OR,    (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2043 "parser.tab.c"
    break;

  case 78: /* expr: NOT expr  */
#line 433 "parser.y"
                       { (yyval.node) = at(create_node(NODE_NOT)); (yyval.node)->data.single_expr.expr = (yyvsp[0].node); }
#line 2049 "parser.tab.c"
    break;

  case 79: /* expr: MINUS expr  */
#line 434 "parser.y"
                              { (yyval.node) = at(create_node(NODE_NEG)); (yyval.node)->data.single_expr.expr = (yyvsp[0].node); }
#line 2055 "parser.tab.c"
    break;

  case 80: /* expr: LPAREN expr RPAREN  */
#line 435 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2061 "parser.tab.c"
    break;

  case 81: /* expr: LPAREN INT RPAREN expr  */
#line 437 "parser.y"
                                     { (yyval.node) = at(create_cast_node(TYPE_INT,    (yyvsp[0].node))); }
#line 2067 "parser.tab.c"
    break;

  case 82: /* expr: LPAREN FLOAT_TYPE RPAREN expr  */
#line 438 "parser.y"
                                     { (yyval.node) = at(create_cast_node(TYPE_FLOAT,  (yyvsp[0].node))); }
#line 2073 "parser.tab.c"
    break;

  case 83: /* expr: LPAREN BOOL RPAREN expr  */
#line 439 "parser.y"
                                     { (yyval.node) = at(create_cast_node(TYPE_BOOL,   (yyvsp[0].node))); }
#line 2079 "parser.tab.c"
    break;

  case 84: /* expr: LPAREN STRING_TYPE RPAREN expr  */
#line 440 "parser.y"
                                     { (yyval.node) = at(create_cast_node(TYPE_STRING, (yyvsp[0].node))); }
#line 2085 "parser.tab.c"
    break;

  case 85: /* expr: ID LPAREN arg_list RPAREN  */
#line 442 "parser.y"
                                {
        (yyval.node) = at(create_node(NODE_FUNC_CALL));
        (yyval.node)->data.func_call.name = strdup((yyvsp[-3].str));
        (yyval.node)->data.func_call.args = (yyvsp[-1].elist);
      }
#line 2095 "parser.tab.c"
    break;

  case 86: /* expr: NUMBER  */
#line 447 "parser.y"
                 { (yyval.node) = at(create_num_node((yyvsp[0].num))); }
#line 2101 "parser.tab.c"
    break;

  case 87: /* expr: FLOAT_NUM  */
#line 448 "parser.y"
                 { (yyval.node) = at(create_float_node((yyvsp[0].fnum))); }
#line 2107 "parser.tab.c"
    break;

  case 88: /* expr: TRUE  */
#line 449 "parser.y"
                 { (yyval.node) = at(create_bool_node(1)); }
#line 2113 "parser.tab.c"
    break;

  case 89: /* expr: FALSE  */
#line 450 "parser.y"
                 { (yyval.node) = at(create_bool_node(0)); }
#line 2119 "parser.tab.c"
    break;

  case 90: /* expr: STRING_LIT  */
#line 451 "parser.y"
                 { (yyval.node) = at(create_str_node((yyvsp[0].str))); }
#line 2125 "parser.tab.c"
    break;

  case 91: /* expr: ID LBRACKET expr RBRACKET  */
#line 452 "parser.y"
                                {
        Symbol *sym = lookup_symbol((yyvsp[-3].str));
        if (!sym) {
            char msg[256];
            char *sug = closest_symbol((yyvsp[-3].str));
            if (sug) snprintf(msg, sizeof(msg), "Undeclared array '%s'. Did you mean '%s'?", (yyvsp[-3].str), sug);
            else     snprintf(msg, sizeof(msg), "Undeclared identifier '%s'.", (yyvsp[-3].str));
            report_error(yylineno, current_col, msg);
        } else if (!sym->is_array) {
            char msg[128];
            snprintf(msg, sizeof(msg), "'%s' is not an array, cannot index it.", (yyvsp[-3].str));
            report_error(yylineno, current_col, msg);
        }
        (yyval.node) = at(create_array_access_node((yyvsp[-3].str), (yyvsp[-1].node)));
      }
#line 2145 "parser.tab.c"
    break;

  case 92: /* expr: ID  */
#line 467 "parser.y"
                 {
        if (!lookup_symbol((yyvsp[0].str))) {
            char msg[256];
            char *sug = closest_symbol((yyvsp[0].str));
            if (sug) snprintf(msg, sizeof(msg), "Undeclared variable '%s'. Did you mean '%s'?", (yyvsp[0].str), sug);
            else     snprintf(msg, sizeof(msg), "Undeclared variable '%s'.", (yyvsp[0].str));
            report_error(yylineno, current_col, msg);
        }
        (yyval.node) = at(create_id_node((yyvsp[0].str)));
      }
#line 2160 "parser.tab.c"
    break;


#line 2164 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 479 "parser.y"


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
