
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "E:/CompilerLabs/Compilerlab4/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "tokens.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

void yyerror(const char *s);
int yylex();
void clearStack();
void opreate(yytokentype opType);
string tokenTypeToString(int type);
void clearStackInFunc(int num);
extern void yy_scan_string(const char *str);
extern vector<Token> tokens;

vector<string> functions;
vector<int> functionVars;
vector<int> callArgs;
vector<bool> hasElse;
int functionIndex = 0;
int call_args = 0;
int localVariableCount = 0;
int inputVariableCount = 0;
int zerocnt = 0;
int onecnt = 0;
int notcnt = 0;
int opCountOutSideCall = 0;
int offset = 0;
bool singleExpression = true;
bool isNumCall = false;

unordered_map<int, int> ifEnds;
unordered_map<int, int> whileEnds;
unordered_map<string, int> inputVariables;
unordered_map<string, int> localVariables;

stack <int> operators;
stack <int> oprands;
stack <int> while_labels;

unordered_map <yytokentype, int> priority = {
    {MUL, 1},
    {DIV, 1},
    {MOD, 1},
    {ADD, 2},
    {SUB, 2},
    {LESS, 3},
    {LESS_EQUAL, 3},
    {GREATER, 3},
    {GREATER_EQUAL, 3},
    {EQUAL, 4},
    {NOTEQUAL, 4},
    {BITWISE_AND, 5},
    {BITWISE_XOR, 6},
    {BITWISE_OR, 7},
    {LOGICAL_AND, 8},
    {LOGICAL_OR, 9},
    {ASSIGN, 10},
    {LEFT_PAREN, 11},
    {RIGHT_PAREN, 11},
};



/* Line 189 of yacc.c  */
#line 145 "E:/CompilerLabs/Compilerlab4/cmake-build-debug/parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     IDENTIFIER = 259,
     IF = 260,
     ELSE = 261,
     WHILE = 262,
     CONTINUE = 263,
     BREAK = 264,
     INT = 265,
     RETURN = 266,
     MAIN = 267,
     VOID = 268,
     PREDEFINED_FUNCTION = 269,
     ASSIGN = 270,
     ADD = 271,
     SUB = 272,
     MUL = 273,
     DIV = 274,
     MOD = 275,
     LESS = 276,
     LESS_EQUAL = 277,
     GREATER = 278,
     GREATER_EQUAL = 279,
     EQUAL = 280,
     NOTEQUAL = 281,
     BITWISE_AND = 282,
     BITWISE_OR = 283,
     BITWISE_XOR = 284,
     LOGICAL_AND = 285,
     LOGICAL_OR = 286,
     NOT = 287,
     BITWISE_NOT = 288,
     SEMICOLON = 289,
     LEFT_BRACE = 290,
     RIGHT_BRACE = 291,
     LEFT_PAREN = 292,
     RIGHT_PAREN = 293,
     COMMA = 294,
     UNKNOWN = 295
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 74 "E:/CompilerLabs/Compilerlab4/parser.y"

    int index;



/* Line 214 of yacc.c  */
#line 227 "E:/CompilerLabs/Compilerlab4/cmake-build-debug/parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 239 "E:/CompilerLabs/Compilerlab4/cmake-build-debug/parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   273

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNRULES -- Number of states.  */
#define YYNSTATES  169

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    15,    18,
      23,    24,    25,    36,    37,    38,    49,    50,    51,    62,
      64,    65,    69,    70,    74,    79,    83,    89,    90,    97,
      99,   100,   101,   111,   114,   117,   118,   119,   130,   131,
     132,   138,   140,   144,   148,   154,   155,   157,   158,   163,
     165,   167,   168,   174,   175,   180,   181,   186,   187,   192,
     193,   198,   199,   204,   205,   210,   211,   216,   217,   222,
     223,   228,   229,   234,   235,   240,   241,   246,   247,   252,
     253,   258,   259,   264,   265,   270,   273,   276,   279,   280
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    43,    -1,    44,    -1,    44,    43,    -1,
      46,    -1,    49,    -1,    -1,    10,     4,    -1,    45,    39,
      10,     4,    -1,    -1,    -1,    10,    12,    37,    45,    38,
      47,    35,    48,    54,    36,    -1,    -1,    -1,    10,     4,
      37,    45,    38,    50,    35,    51,    54,    36,    -1,    -1,
      -1,    13,     4,    37,    45,    38,    52,    35,    53,    54,
      36,    -1,    56,    -1,    -1,    56,    55,    54,    -1,    -1,
      10,    65,    34,    -1,     4,    15,    68,    34,    -1,    11,
      68,    34,    -1,    14,    37,    68,    38,    34,    -1,    -1,
       4,    57,    37,    66,    38,    34,    -1,    60,    -1,    -1,
      -1,     7,    58,    37,    68,    59,    38,    35,    54,    36,
      -1,     8,    34,    -1,     9,    34,    -1,    -1,    -1,     5,
      37,    68,    61,    38,    35,    54,    36,    62,    63,    -1,
      -1,    -1,     6,    64,    35,    54,    36,    -1,     4,    -1,
       4,    15,    68,    -1,    65,    39,     4,    -1,    65,    39,
       4,    15,    68,    -1,    -1,    68,    -1,    -1,    66,    39,
      67,    68,    -1,     3,    -1,     4,    -1,    -1,     4,    69,
      37,    66,    38,    -1,    -1,    68,    16,    70,    68,    -1,
      -1,    68,    17,    71,    68,    -1,    -1,    68,    18,    72,
      68,    -1,    -1,    68,    19,    73,    68,    -1,    -1,    68,
      20,    74,    68,    -1,    -1,    68,    21,    75,    68,    -1,
      -1,    68,    22,    76,    68,    -1,    -1,    68,    23,    77,
      68,    -1,    -1,    68,    24,    78,    68,    -1,    -1,    68,
      25,    79,    68,    -1,    -1,    68,    26,    80,    68,    -1,
      -1,    68,    27,    81,    68,    -1,    -1,    68,    28,    82,
      68,    -1,    -1,    68,    29,    83,    68,    -1,    -1,    68,
      30,    84,    68,    -1,    -1,    68,    31,    85,    68,    -1,
      32,    68,    -1,    17,    68,    -1,    33,    68,    -1,    -1,
      37,    86,    68,    38,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   114,   115,   119,   122,   126,   128,   131,
     137,   140,   137,   154,   160,   154,   171,   177,   171,   191,
     194,   194,   199,   201,   203,   216,   223,   229,   229,   237,
     238,   241,   238,   250,   253,   260,   269,   260,   276,   277,
     277,   285,   288,   295,   298,   307,   309,   312,   312,   318,
     323,   337,   337,   346,   346,   354,   354,   362,   362,   370,
     370,   378,   378,   386,   386,   394,   394,   402,   402,   410,
     410,   418,   418,   426,   426,   434,   434,   442,   442,   450,
     450,   458,   458,   466,   466,   475,   489,   496,   503,   503
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "IDENTIFIER", "IF", "ELSE",
  "WHILE", "CONTINUE", "BREAK", "INT", "RETURN", "MAIN", "VOID",
  "PREDEFINED_FUNCTION", "ASSIGN", "ADD", "SUB", "MUL", "DIV", "MOD",
  "LESS", "LESS_EQUAL", "GREATER", "GREATER_EQUAL", "EQUAL", "NOTEQUAL",
  "BITWISE_AND", "BITWISE_OR", "BITWISE_XOR", "LOGICAL_AND", "LOGICAL_OR",
  "NOT", "BITWISE_NOT", "SEMICOLON", "LEFT_BRACE", "RIGHT_BRACE",
  "LEFT_PAREN", "RIGHT_PAREN", "COMMA", "UNKNOWN", "$accept", "program",
  "function_list", "function", "args", "main_function", "$@1", "$@2",
  "other_function", "$@3", "$@4", "$@5", "$@6", "statement_list", "$@7",
  "statement", "$@8", "$@9", "$@10", "if_statement", "$@11", "$@12",
  "else_statement", "$@13", "declaration_list", "arg_list", "$@14",
  "expression", "$@15", "$@16", "$@17", "$@18", "$@19", "$@20", "$@21",
  "$@22", "$@23", "$@24", "$@25", "$@26", "$@27", "$@28", "$@29", "$@30",
  "$@31", "$@32", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    45,    45,    45,
      47,    48,    46,    50,    51,    49,    52,    53,    49,    54,
      55,    54,    56,    56,    56,    56,    56,    57,    56,    56,
      58,    59,    56,    56,    56,    61,    62,    60,    63,    64,
      63,    65,    65,    65,    65,    66,    66,    67,    66,    68,
      68,    69,    68,    70,    68,    71,    68,    72,    68,    73,
      68,    74,    68,    75,    68,    76,    68,    77,    68,    78,
      68,    79,    68,    80,    68,    81,    68,    82,    68,    83,
      68,    84,    68,    85,    68,    68,    68,    68,    86,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     0,     2,     4,
       0,     0,    10,     0,     0,    10,     0,     0,    10,     1,
       0,     3,     0,     3,     4,     3,     5,     0,     6,     1,
       0,     0,     9,     2,     2,     0,     0,    10,     0,     0,
       5,     1,     3,     3,     5,     0,     1,     0,     4,     1,
       1,     0,     5,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     2,     2,     2,     0,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,     0,     0,
       0,     1,     4,     7,     7,     7,     0,     0,     0,     0,
       8,    13,     0,    10,    16,     0,     0,     0,     0,    14,
       9,    11,    17,    22,    22,    22,    27,     0,    30,     0,
       0,     0,     0,     0,     0,    20,    29,     0,     0,     0,
       0,     0,     0,    33,    34,    41,     0,    49,    50,     0,
       0,     0,    88,     0,     0,    15,    22,    12,    18,     0,
      45,    35,     0,     0,    23,     0,     0,    86,    85,    87,
       0,    53,    55,    57,    59,    61,    63,    65,    67,    69,
      71,    73,    75,    77,    79,    81,    83,    25,     0,    21,
      24,     0,    46,     0,    31,    42,    43,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,     0,     0,
       0,     0,    89,    54,    56,    58,    60,    62,    64,    66,
      68,    70,    72,    74,    76,    78,    80,    82,    84,    26,
      28,     0,    22,     0,    44,    52,    48,     0,    22,    36,
       0,    38,    32,    39,    37,     0,    22,     0,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    17,     6,    27,    34,     7,    25,
      33,    28,    35,    44,    66,    45,    50,    52,   129,    46,
     103,   161,   164,   165,    56,   101,   151,   102,    76,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,    80
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yytype_int16 yypact[] =
{
      -8,     3,     2,     8,   -40,    -8,   -40,   -40,   -26,   -18,
     -11,   -40,   -40,    30,    30,    30,    42,   -15,   -10,     6,
     -40,   -40,    59,   -40,   -40,    51,    83,    53,    54,   -40,
     -40,   -40,   -40,   112,   112,   112,    75,    71,   -40,    77,
      79,   105,    10,    73,    89,    91,   -40,    92,    93,    10,
      78,    10,    94,   -40,   -40,   115,   -30,   -40,   113,    10,
      10,    10,   -40,    32,    10,   -40,   112,   -40,   -40,   140,
      10,   159,    10,    10,   -40,   145,   114,   -40,   -40,   -40,
      10,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,    76,   -40,
     -40,    26,   159,   116,   159,   159,   137,    10,   117,    10,
      10,    10,    10,    10,    10,    10,    10,    10,    10,    10,
      10,    10,    10,    10,    10,   119,   138,   -40,   197,   135,
      10,    29,   -40,    -2,    -2,   -40,   -40,   -40,    19,    19,
      19,    19,   241,   241,   230,   204,   218,   190,   175,   -40,
     -40,    10,   112,   231,   159,   -40,   159,   232,   112,   -40,
     233,   261,   -40,   -40,   -40,   235,   112,   236,   -40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -40,   -40,   266,   -40,    16,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -34,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   166,   -40,   -39,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -52
static const yytype_int16 yytable[] =
{
      47,    48,     1,    63,    74,     2,    10,     8,    11,    75,
      69,    13,    71,    57,    58,     9,    83,    84,    85,    14,
      77,    78,    79,    21,    22,    98,    15,    59,    23,    22,
      18,    19,    99,   104,   105,    81,    82,    83,    84,    85,
      16,   108,    60,    61,    24,    22,    20,    62,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,   126,   127,    97,   155,   127,    26,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,    29,    30,    31,    32,
      49,   154,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    51,    55,
      64,    53,   156,    54,   125,    70,    36,    37,   157,    38,
      39,    40,    41,    42,   160,    65,    43,   -19,    67,    68,
      73,    72,   167,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,   106,
     -51,   107,   130,   149,   128,   132,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   150,   153,   100,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   152,    94,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   158,   163,   159,   162,
     166,    12,   168,   131
};

static const yytype_uint8 yycheck[] =
{
      34,    35,    10,    42,    34,    13,     4,     4,     0,    39,
      49,    37,    51,     3,     4,    12,    18,    19,    20,    37,
      59,    60,    61,    38,    39,    64,    37,    17,    38,    39,
      14,    15,    66,    72,    73,    16,    17,    18,    19,    20,
      10,    80,    32,    33,    38,    39,     4,    37,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    38,    39,    34,    38,    39,    10,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,    35,     4,    35,    35,
      15,   130,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    37,     4,
      37,    34,   151,    34,    38,    37,     4,     5,   152,     7,
       8,     9,    10,    11,   158,    36,    14,    36,    36,    36,
      15,    37,   166,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,     4,
      37,    37,    15,    34,    38,    38,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    34,    38,    34,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    35,    29,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    35,     6,    36,    36,
      35,     5,    36,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    13,    42,    43,    44,    46,    49,     4,    12,
       4,     0,    43,    37,    37,    37,    10,    45,    45,    45,
       4,    38,    39,    38,    38,    50,    10,    47,    52,    35,
       4,    35,    35,    51,    48,    53,     4,     5,     7,     8,
       9,    10,    11,    14,    54,    56,    60,    54,    54,    15,
      57,    37,    58,    34,    34,     4,    65,     3,     4,    17,
      32,    33,    37,    68,    37,    36,    55,    36,    36,    68,
      37,    68,    37,    15,    34,    39,    69,    68,    68,    68,
      86,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    34,    68,    54,
      34,    66,    68,    61,    68,    68,     4,    37,    68,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    38,    38,    39,    38,    59,
      15,    66,    38,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    34,
      34,    67,    35,    38,    68,    38,    68,    54,    35,    36,
      54,    62,    36,     6,    63,    64,    35,    54,    36
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:

/* Line 1455 of yacc.c  */
#line 119 "E:/CompilerLabs/Compilerlab4/parser.y"
    {

    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 122 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 128 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        inputVariables[tokens[(yyvsp[(2) - (2)].index)].value] = ++inputVariableCount;
    ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 131 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        inputVariables[tokens[(yyvsp[(4) - (4)].index)].value] = ++inputVariableCount;
    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 137 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
            inputVariableCount = 0;
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 140 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
            cout << endl << "main:" << endl;
            cout << "push ebp" << endl;
            cout << "mov ebp, esp" << endl;
            cout << "sub esp, " << 4 * functionVars[functionIndex++] << endl;
            localVariableCount = 0;
        ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 147 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        inputVariables.clear();
        localVariables.clear();
    ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 154 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
            for(auto it = inputVariables.begin(); it != inputVariables.end(); it++){
                inputVariables[it->first] = inputVariableCount + 1 - inputVariables[it->first];
            }
            inputVariableCount = 0;
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 160 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
            cout << endl << tokens[(yyvsp[(2) - (7)].index)].value << ":" << endl;
            printf("push ebp\n");
            printf("mov ebp, esp\n");
            printf("sub esp, %d\n", 4 * functionVars[functionIndex++] + 4);
            localVariableCount = 0;
    ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 167 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        inputVariables.clear();
        localVariables.clear();
    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 171 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
            for(auto it = inputVariables.begin(); it != inputVariables.end(); it++){
                inputVariables[it->first] = inputVariableCount + 1 - inputVariables[it->first];
            }
            inputVariableCount = 0;
        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 177 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
            cout << endl << tokens[(yyvsp[(2) - (7)].index)].value << ":" << endl;
            printf("push ebp\n");
            printf("mov ebp, esp\n");
            printf("sub esp, %d\n", 4 * functionVars[functionIndex++] + 4);
            localVariableCount = 0;
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 184 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        inputVariables.clear();
        localVariables.clear();
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 191 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        singleExpression = true;
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 194 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        singleExpression = true;
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 201 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 203 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        int offset;
        clearStack();
        if(inputVariables.find(tokens[(yyvsp[(1) - (4)].index)].value) != inputVariables.end()){
            offset = 4 * (inputVariables[tokens[(yyvsp[(1) - (4)].index)].value] + 1);
            printf("pop eax\n");
            printf("mov DWORD PTR [ebp + %d], eax\n", offset);
        } else if(localVariables.find(tokens[(yyvsp[(1) - (4)].index)].value) != localVariables.end()){
            offset = 4 * localVariables[tokens[(yyvsp[(1) - (4)].index)].value];
            printf("pop eax\n");
            printf("mov DWORD PTR [ebp - %d], eax\n", offset);
        }
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 216 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        clearStack();
        opCountOutSideCall = 0;
        printf("pop eax\n");
        printf("leave\n");
        printf("ret\n");
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 223 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        clearStack();
        printf("push offset format_str\n");
        printf("call printf\n");
        printf("add esp, 8\n");
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 229 "E:/CompilerLabs/Compilerlab4/parser.y"
    {isNumCall = true;;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 229 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        printf("call %s\n", tokens[(yyvsp[(1) - (6)].index)].value.c_str());
        printf("add esp, %d\n", 4 * (call_args + 1));
        printf("push eax\n");
        call_args = 0;
        isNumCall = false;
        opCountOutSideCall = 0;
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 238 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << ".while_condition_" << whileEnds[(yyvsp[(1) - (1)].index)] << ":" << endl;
        while_labels.push(whileEnds[(yyvsp[(1) - (1)].index)]);
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 241 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        clearStack();
        cout << "pop eax" << endl;
        cout << "cmp eax, 0" << endl;
        cout << "je .while_end_" << whileEnds[(yyvsp[(1) - (4)].index)] << endl;
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 246 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << "jmp .while_condition_" << whileEnds[(yyvsp[(1) - (9)].index)] << endl;
        cout << ".while_end_" << whileEnds[(yyvsp[(1) - (9)].index)] << ":" << endl;
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 250 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << "jmp .while_condition_" << while_labels.top() << endl;
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 253 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << "jmp .while_end_" << while_labels.top() << endl;
        while_labels.pop();
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 260 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        clearStack();
        cout << "pop eax" << endl;
        cout << "cmp eax, 0" << endl;
        if(hasElse[ifEnds[(yyvsp[(1) - (3)].index)] - 1]){
            cout << "je .else_" << ifEnds[(yyvsp[(1) - (3)].index)] << endl;
        } else {
            cout << "je .if_end_" << ifEnds[(yyvsp[(1) - (3)].index)] << endl;
        }
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 269 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << "jmp .if_end_" << ifEnds[(yyvsp[(1) - (8)].index)] << endl;
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 271 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << ".if_end_" << ifEnds[(yyvsp[(1) - (10)].index)] << ":" << endl;
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 277 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << ".else_" << ifEnds[(yyvsp[(1) - (1)].index)] << ":" << endl;
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 279 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        cout << "jmp .if_end_" << ifEnds[(yyvsp[(1) - (5)].index)] << endl;
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 285 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        localVariables[tokens[(yyvsp[(1) - (1)].index)].value] = ++localVariableCount;
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 288 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        localVariables[tokens[(yyvsp[(1) - (3)].index)].value] = ++localVariableCount;
        clearStack();
        singleExpression = true;
        printf("pop eax\n");
        printf("mov DWORD PTR [ebp - %d], eax\n", 4 * localVariableCount);
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 295 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        localVariables[tokens[(yyvsp[(3) - (3)].index)].value] = ++localVariableCount;
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 298 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        localVariables[tokens[(yyvsp[(3) - (5)].index)].value] = ++localVariableCount;
        clearStack();
        singleExpression = true;
        printf("pop eax\n");
        printf("mov DWORD PTR [ebp - %d], eax\n", 4 * localVariableCount);
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 309 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        clearStackInFunc(opCountOutSideCall);
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 312 "E:/CompilerLabs/Compilerlab4/parser.y"
    {call_args++; isNumCall = false;;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 312 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        clearStackInFunc(opCountOutSideCall);
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 318 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        (yyval.index) = (yyvsp[(1) - (1)].index);
        cout << "push " << tokens[(yyvsp[(1) - (1)].index)].value << endl;
        oprands.push((yyvsp[(1) - (1)].index));
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 323 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        (yyval.index) = (yyvsp[(1) - (1)].index);
        int offset;
        if(inputVariables.find(tokens[(yyvsp[(1) - (1)].index)].value) != inputVariables.end()){
            offset = 4 * (inputVariables[tokens[(yyvsp[(1) - (1)].index)].value] + 1);
            printf("mov eax, DWORD PTR [ebp + %d]\n", offset);
            printf("push eax\n");
        } else if(localVariables.find(tokens[(yyvsp[(1) - (1)].index)].value) != localVariables.end()){
            offset = 4 * localVariables[tokens[(yyvsp[(1) - (1)].index)].value];
            printf("mov eax, DWORD PTR [ebp - %d]\n", offset);
            printf("push eax\n");
        }
        oprands.push((yyvsp[(1) - (1)].index));
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 337 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        isNumCall = true;
        opCountOutSideCall = operators.size();
        ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 340 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
            printf("call %s\n", tokens[(yyvsp[(1) - (5)].index)].value.c_str());
            printf("add esp, %d\n", 4 * (call_args + 1));
            printf("push eax\n");
            call_args = 0;
        ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 346 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[ADD]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 354 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[SUB]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 362 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[MUL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 370 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[DIV]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 378 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[MOD]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 386 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LESS]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 394 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LESS_EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 402 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[GREATER]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 410 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[GREATER_EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 418 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 426 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[NOTEQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 434 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_AND]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 442 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_OR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 450 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_XOR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 458 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LOGICAL_AND]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 466 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LOGICAL_OR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));

    ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 475 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        singleExpression = false;

        printf("pop eax\n");
        printf("cmp eax, 0\n");
        cout << "jnz notZero" << notcnt << endl;
        printf("setz al\n");
        cout << "jmp notEnd" << notcnt << endl;
        cout << "notZero" << notcnt << ":" << endl;
        cout << "mov eax, 0" << endl;
        cout << "notEnd" << notcnt << ":" << endl;
        printf("push eax\n");
        notcnt++;
    ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 489 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        singleExpression = false;

        printf("pop eax\n");
        printf("neg eax\n");
        printf("push eax\n");
    ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 496 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        singleExpression = false;

        printf("pop eax\n");
        printf("not eax\n");
        printf("push eax\n");
    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 503 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        operators.push((yyvsp[(1) - (1)].index));
    ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 505 "E:/CompilerLabs/Compilerlab4/parser.y"
    {
        while(tokens[operators.top()].type != LEFT_PAREN){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.pop();
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2353 "E:/CompilerLabs/Compilerlab4/cmake-build-debug/parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 515 "E:/CompilerLabs/Compilerlab4/parser.y"


void init() {
    cout << ".intel_syntax noprefix" << endl;
    cout << ".extern printf" << endl;
    for(auto &function : functions) {
        cout << ".global " << function << endl;
    }
    cout << ".data\nformat_str:\n.asciz \"%d\\n\"\n.text\n" << endl;
}

string tokenTypeToString(int type) {
    switch (type) {
        case NUMBER: return "NUMBER";
        case IDENTIFIER: return "IDENTIFIER";
        case INT: return "INT";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case WHILE: return "WHILE";
        case CONTINUE: return "CONTINUE";
        case BREAK: return "BREAK";
        case RETURN: return "RETURN";
        case MAIN: return "MAIN";
        case VOID: return "VOID";
        case PREDEFINED_FUNCTION: return "PREDEFINED_FUNCTION";
        case ASSIGN: return "ASSIGN";
        case ADD: return "ADD";
        case SUB: return "SUB";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case EQUAL: return "EQUAL";
        case NOTEQUAL: return "NOTEQUAL";
        case BITWISE_AND: return "BITWISE_AND";
        case BITWISE_OR: return "BITWISE_OR";
        case BITWISE_XOR: return "BITWISE_XOR";
        case LOGICAL_AND: return "LOGICAL_AND";
        case LOGICAL_OR: return "LOGICAL_OR";
        case NOT: return "NOT";
        case BITWISE_NOT: return "BITWISE_NOT";
        case SEMICOLON: return "SEMICOLON";
        case LEFT_BRACE: return "LEFT_BRACE";
        case RIGHT_BRACE: return "RIGHT_BRACE";
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case COMMA: return "COMMA";
        case UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}

void print() {
    for (auto &token : tokens) {
        cout << tokenTypeToString(token.type) << "\t" << token.value << endl;
    }
}

void getFunctions(){
    bool inFunction = false;
    bool isFunction = false;
    stack <int> braces;
    int vars = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token& token = tokens[i];
        if(token.type == LEFT_BRACE){
            braces.push(i);
            if(isFunction){
                inFunction = true;
            }
        }
        if(token.type == RIGHT_BRACE){
            if(braces.size() == 1){
                inFunction = false;
                isFunction = false;
                functionVars.push_back(vars);
                vars = 0;
            }
            braces.pop();
        }
        if(token.type == INT && inFunction){
            int comma = 0;
            for (size_t j = i; j < tokens.size(); ++j) {
                if(tokens[j].type == COMMA){
                    comma++;
                }
                if(tokens[j].type == SEMICOLON){
                    vars += comma + 1;
                    break;
                }
            }
        }
        if((token.type == IDENTIFIER || token.type == MAIN) && tokens[i + 1].type == LEFT_PAREN && (tokens[i - 1].type == INT || tokens[i - 1].type == VOID)){
            functions.push_back(token.value);
            isFunction = true;
        }
    }
}

void zero(){
    cout << "zero:" << endl;
    cout << "push 0" << endl;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

void lexing() {
    while(yylex() != 0) {

    }
}

void clearStack(){
    while(!operators.empty()){
        yytokentype op = tokens[operators.top()].type;
        operators.pop();
        opreate(op);
    }
}

void clearStackInFunc(int num){
    while(operators.size() > num){
        yytokentype op = tokens[operators.top()].type;
        operators.pop();
        opreate(op);
    }
}

void opreate(yytokentype opType){ 
    switch(opType){
        case ADD:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "add eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case SUB:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "sub eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case MUL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "imul eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case DIV:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cdq" << endl;
            cout << "idiv ebx" << endl;
            cout << "push eax" << endl;
            break;
        case MOD:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cdq" << endl;
            cout << "idiv ebx" << endl;
            cout << "push edx" << endl;
            break;
        case LESS:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setl al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case LESS_EQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setle al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case GREATER:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setg al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case GREATER_EQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setge al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case EQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "sete al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case NOTEQUAL:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "cmp eax, ebx" << endl;
            cout << "setne al" << endl;
            cout << "movzx eax, al" << endl;
            cout << "push eax" << endl;
            break;
        case BITWISE_AND:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "and eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case BITWISE_OR:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "or eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case BITWISE_XOR:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "xor eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
        case LOGICAL_AND:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "test eax, eax" << endl;
            cout << "jz zero" << zerocnt << endl;
            cout << "test ebx, ebx" << endl;
            cout << "jz zero" << zerocnt << endl;
            cout << "push 1" << endl;
            cout << "jmp logicalAndEnd" << zerocnt << endl;
            cout << "zero" << zerocnt << ":" << endl;
            cout << "push 0" << endl;
            cout << "logicalAndEnd" << zerocnt << ":" << endl;
            zerocnt++;
            break;
        case LOGICAL_OR:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "test eax, eax" << endl;
            cout << "jnz one" << onecnt << endl;
            cout << "test ebx, ebx" << endl;
            cout << "jnz one" << onecnt << endl;
            cout << "push 0" << endl;
            cout << "jmp logicalOrEnd" << onecnt << endl;
            cout << "one" << onecnt << ":" << endl;
            cout << "push 1" << endl;
            cout << "logicalOrEnd" << onecnt << ":" << endl;
            onecnt++;
            break;
        case ASSIGN:
            cout << "pop ebx" << endl;
            cout << "pop eax" << endl;
            cout << "mov eax, ebx" << endl;
            cout << "push eax" << endl;
            break;
    }
}

void findIfAndWhile(){
    int if_cnt = 0;
    int while_cnt = 0;
    for (int i = 0; i < tokens.size(); ++i) {
        if(tokens[i].type == IF){
            ifEnds[i + offset] = ++if_cnt;
        }
        if(tokens[i].type == ELSE){
            ifEnds[i + offset] = if_cnt;
        }
        if(tokens[i].type == WHILE){
            whileEnds[i + offset] = ++while_cnt;
        }
    }
}

void findElse(){
    int if_cnt = 0;
    for (auto &token : tokens) {
        if(token.type == IF){
            hasElse.push_back(false);
            if_cnt++;
        }
        if(token.type == ELSE){
            hasElse[if_cnt - 1] = true;
        }
    }
}

int main(int argc, char *argv[]){

    //ifstream file(argv[1]);
    ifstream file(R"(E:\CompilerLabs\Compilerlab4\Test_cases\10.txt)");

    if (!file) {
        cerr << "Unable to open file!";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    yy_scan_string(content.c_str());
    lexing();
    //print();

    offset = tokens.size();

    getFunctions();
    findIfAndWhile();
    findElse();
    init();

    yy_scan_string(content.c_str());
    yyparse();

    return 0;
}
