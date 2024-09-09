
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
#line 1 "E:/CompilerLabs/Compilerlab3/parser.y"

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
int functionIndex = 0;
int call_args = 0;
int localVariableCount = 0;
int inputVariableCount = 0;
int zerocnt = 0;
int onecnt = 0;
int notcnt = 0;
int opCountOutSideCall = 0;
bool singleExpression = true;
bool isNumCall = false;

unordered_map<string, int> inputVariables;
unordered_map<string, int> localVariables;

stack <int> operators;
stack <int> oprands;

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
#line 140 "E:/CompilerLabs/Compilerlab3/cmake-build-debug/parser.cpp"

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
     INT = 260,
     RETURN = 261,
     MAIN = 262,
     VOID = 263,
     PREDEFINED_FUNCTION = 264,
     ASSIGN = 265,
     ADD = 266,
     SUB = 267,
     MUL = 268,
     DIV = 269,
     MOD = 270,
     LESS = 271,
     LESS_EQUAL = 272,
     GREATER = 273,
     GREATER_EQUAL = 274,
     EQUAL = 275,
     NOTEQUAL = 276,
     BITWISE_AND = 277,
     BITWISE_OR = 278,
     BITWISE_XOR = 279,
     LOGICAL_AND = 280,
     LOGICAL_OR = 281,
     NOT = 282,
     BITWISE_NOT = 283,
     SEMICOLON = 284,
     LEFT_BRACE = 285,
     RIGHT_BRACE = 286,
     LEFT_PAREN = 287,
     RIGHT_PAREN = 288,
     COMMA = 289,
     UNKNOWN = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 69 "E:/CompilerLabs/Compilerlab3/parser.y"

    int index;



/* Line 214 of yacc.c  */
#line 217 "E:/CompilerLabs/Compilerlab3/cmake-build-debug/parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 229 "E:/CompilerLabs/Compilerlab3/cmake-build-debug/parser.cpp"

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
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

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
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    15,    18,
      23,    24,    25,    36,    37,    38,    49,    50,    51,    62,
      64,    65,    69,    70,    74,    79,    83,    89,    90,    97,
      99,   103,   107,   113,   114,   116,   117,   122,   124,   126,
     127,   133,   134,   139,   140,   145,   146,   151,   152,   157,
     158,   163,   164,   169,   170,   175,   176,   181,   182,   187,
     188,   193,   194,   199,   200,   205,   206,   211,   212,   217,
     218,   223,   224,   229,   232,   235,   238,   239
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    -1,    39,    -1,    39,    38,    -1,
      41,    -1,    44,    -1,    -1,     5,     4,    -1,    40,    34,
       5,     4,    -1,    -1,    -1,     5,     7,    32,    40,    33,
      42,    30,    43,    49,    31,    -1,    -1,    -1,     5,     4,
      32,    40,    33,    45,    30,    46,    49,    31,    -1,    -1,
      -1,     8,     4,    32,    40,    33,    47,    30,    48,    49,
      31,    -1,    51,    -1,    -1,    51,    50,    49,    -1,    -1,
       5,    53,    29,    -1,     4,    10,    56,    29,    -1,     6,
      56,    29,    -1,     9,    32,    56,    33,    29,    -1,    -1,
       4,    52,    32,    54,    33,    29,    -1,     4,    -1,     4,
      10,    56,    -1,    53,    34,     4,    -1,    53,    34,     4,
      10,    56,    -1,    -1,    56,    -1,    -1,    54,    34,    55,
      56,    -1,     3,    -1,     4,    -1,    -1,     4,    57,    32,
      54,    33,    -1,    -1,    56,    11,    58,    56,    -1,    -1,
      56,    12,    59,    56,    -1,    -1,    56,    13,    60,    56,
      -1,    -1,    56,    14,    61,    56,    -1,    -1,    56,    15,
      62,    56,    -1,    -1,    56,    16,    63,    56,    -1,    -1,
      56,    17,    64,    56,    -1,    -1,    56,    18,    65,    56,
      -1,    -1,    56,    19,    66,    56,    -1,    -1,    56,    20,
      67,    56,    -1,    -1,    56,    21,    68,    56,    -1,    -1,
      56,    22,    69,    56,    -1,    -1,    56,    23,    70,    56,
      -1,    -1,    56,    24,    71,    56,    -1,    -1,    56,    25,
      72,    56,    -1,    -1,    56,    26,    73,    56,    -1,    27,
      56,    -1,    12,    56,    -1,    28,    56,    -1,    -1,    32,
      74,    56,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   108,   109,   113,   118,   124,   126,   129,
     135,   138,   135,   152,   158,   152,   169,   175,   169,   189,
     192,   192,   197,   199,   201,   214,   218,   224,   224,   235,
     238,   245,   248,   257,   259,   262,   262,   268,   273,   287,
     287,   293,   293,   301,   301,   309,   309,   317,   317,   325,
     325,   334,   334,   342,   342,   350,   350,   358,   358,   366,
     366,   374,   374,   382,   382,   390,   390,   398,   398,   406,
     406,   414,   414,   423,   437,   444,   451,   451
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "IDENTIFIER", "INT", "RETURN",
  "MAIN", "VOID", "PREDEFINED_FUNCTION", "ASSIGN", "ADD", "SUB", "MUL",
  "DIV", "MOD", "LESS", "LESS_EQUAL", "GREATER", "GREATER_EQUAL", "EQUAL",
  "NOTEQUAL", "BITWISE_AND", "BITWISE_OR", "BITWISE_XOR", "LOGICAL_AND",
  "LOGICAL_OR", "NOT", "BITWISE_NOT", "SEMICOLON", "LEFT_BRACE",
  "RIGHT_BRACE", "LEFT_PAREN", "RIGHT_PAREN", "COMMA", "UNKNOWN",
  "$accept", "program", "function_list", "function", "args",
  "main_function", "$@1", "$@2", "other_function", "$@3", "$@4", "$@5",
  "$@6", "statement_list", "$@7", "statement", "$@8", "declaration_list",
  "arg_list", "$@9", "expression", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "$@16", "$@17", "$@18", "$@19", "$@20", "$@21", "$@22", "$@23",
  "$@24", "$@25", "$@26", "$@27", 0
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
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    40,
      42,    43,    41,    45,    46,    44,    47,    48,    44,    49,
      50,    49,    51,    51,    51,    51,    51,    52,    51,    53,
      53,    53,    53,    54,    54,    55,    54,    56,    56,    57,
      56,    58,    56,    59,    56,    60,    56,    61,    56,    62,
      56,    63,    56,    64,    56,    65,    56,    66,    56,    67,
      56,    68,    56,    69,    56,    70,    56,    71,    56,    72,
      56,    73,    56,    56,    56,    56,    74,    56
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     0,     2,     4,
       0,     0,    10,     0,     0,    10,     0,     0,    10,     1,
       0,     3,     0,     3,     4,     3,     5,     0,     6,     1,
       3,     3,     5,     0,     1,     0,     4,     1,     1,     0,
       5,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     2,     2,     2,     0,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     6,     0,     0,
       0,     1,     4,     7,     7,     7,     0,     0,     0,     0,
       8,    13,     0,    10,    16,     0,     0,     0,     0,    14,
       9,    11,    17,    22,    22,    22,    27,     0,     0,     0,
       0,    20,     0,     0,     0,     0,    29,     0,    37,    38,
       0,     0,     0,    76,     0,     0,    15,    22,    12,    18,
       0,    33,     0,    23,     0,     0,    74,    73,    75,     0,
      41,    43,    45,    47,    49,    51,    53,    55,    57,    59,
      61,    63,    65,    67,    69,    71,    25,     0,    21,    24,
       0,    34,    30,    31,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,     0,     0,    77,    42,    44,
      46,    48,    50,    52,    54,    56,    58,    60,    62,    64,
      66,    68,    70,    72,    26,    28,     0,    32,    40,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    17,     6,    27,    34,     7,    25,
      33,    28,    35,    40,    57,    41,    45,    47,    90,   136,
      91,    65,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,    69
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -39
static const yytype_int16 yypact[] =
{
      48,    92,     3,     9,   -39,    48,   -39,   -39,   -21,    23,
      25,   -39,   -39,   191,   191,   191,    93,   -18,   -12,    -5,
     -39,   -39,   225,   -39,   -39,   201,   228,   203,   204,   -39,
     -39,   -39,   -39,    14,    14,    14,   226,   231,    -2,   205,
     207,   208,   209,   211,    -2,   212,   233,   -26,   -39,   213,
      -2,    -2,    -2,   -39,    90,    -2,   -39,    14,   -39,   -39,
     109,    -2,    -2,   -39,   237,   214,   -39,   -39,   -39,    -2,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,    21,   -39,   -39,
      84,   128,   128,   238,    -2,    67,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,   218,   220,   -39,    -2,   103,   -39,    61,    61,
     -39,   -39,   -39,    37,    37,    37,    37,   210,   210,   199,
     173,   187,   159,   144,   -39,   -39,    -2,   128,   -39,   128
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -39,   -39,   245,   -39,    80,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -30,   -39,   -39,   -39,   -39,   157,   -39,
     -38,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -40
static const yytype_int16 yytable[] =
{
      54,    48,    49,    63,    42,    43,    60,    10,    64,    11,
      50,    13,    66,    67,    68,    21,    22,    87,    36,    37,
      38,    23,    22,    39,    92,    51,    52,    88,    24,    22,
      53,    95,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    70,    71,
      72,    73,    74,     1,   112,    14,     2,    15,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,    72,    73,    74,   137,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    18,    19,     8,    20,   139,     9,
     117,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,   113,   114,    86,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,   138,   114,    89,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    16,    83,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      26,    29,    30,    31,    32,    46,    44,    55,    56,   -19,
      58,    93,    59,    62,    61,   -39,    94,   134,   115,   135,
      12,   116
};

static const yytype_uint8 yycheck[] =
{
      38,     3,     4,    29,    34,    35,    44,     4,    34,     0,
      12,    32,    50,    51,    52,    33,    34,    55,     4,     5,
       6,    33,    34,     9,    62,    27,    28,    57,    33,    34,
      32,    69,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    11,    12,
      13,    14,    15,     5,    33,    32,     8,    32,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,    13,    14,    15,   115,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    14,    15,     4,     4,   136,     7,
      33,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    33,    34,    29,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    33,    34,    29,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     5,    24,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       5,    30,     4,    30,    30,     4,    10,    32,    31,    31,
      31,     4,    31,    10,    32,    32,    32,    29,    10,    29,
       5,    94
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     8,    37,    38,    39,    41,    44,     4,     7,
       4,     0,    38,    32,    32,    32,     5,    40,    40,    40,
       4,    33,    34,    33,    33,    45,     5,    42,    47,    30,
       4,    30,    30,    46,    43,    48,     4,     5,     6,     9,
      49,    51,    49,    49,    10,    52,     4,    53,     3,     4,
      12,    27,    28,    32,    56,    32,    31,    50,    31,    31,
      56,    32,    10,    29,    34,    57,    56,    56,    56,    74,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    29,    56,    49,    29,
      54,    56,    56,     4,    32,    56,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    33,    33,    34,    10,    54,    33,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    29,    29,    55,    56,    33,    56
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
#line 113 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        printf("pop eax\n");
        printf("leave\n");
        printf("ret\n");
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 118 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        printf("leave\n");
        printf("ret\n");
    ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 126 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        inputVariables[tokens[(yyvsp[(2) - (2)].index)].value] = ++inputVariableCount;
    ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 129 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        inputVariables[tokens[(yyvsp[(4) - (4)].index)].value] = ++inputVariableCount;
    ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 135 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
            inputVariableCount = 0;
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 138 "E:/CompilerLabs/Compilerlab3/parser.y"
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
#line 145 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        inputVariables.clear();
        localVariables.clear();
    ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 152 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
            for(auto it = inputVariables.begin(); it != inputVariables.end(); it++){
                inputVariables[it->first] = inputVariableCount + 1 - inputVariables[it->first];
            }
            inputVariableCount = 0;
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 158 "E:/CompilerLabs/Compilerlab3/parser.y"
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
#line 165 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        inputVariables.clear();
        localVariables.clear();
    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 169 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
            for(auto it = inputVariables.begin(); it != inputVariables.end(); it++){
                inputVariables[it->first] = inputVariableCount + 1 - inputVariables[it->first];
            }
            inputVariableCount = 0;
        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 175 "E:/CompilerLabs/Compilerlab3/parser.y"
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
#line 182 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        inputVariables.clear();
        localVariables.clear();
    ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 189 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        singleExpression = true;
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 192 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        singleExpression = true;
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 199 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 201 "E:/CompilerLabs/Compilerlab3/parser.y"
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
#line 214 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        clearStack();
        printf("pop eax\n");
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 218 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        clearStack();
        printf("push offset format_str\n");
        printf("call printf\n");
        printf("add esp, 8\n");
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 224 "E:/CompilerLabs/Compilerlab3/parser.y"
    {isNumCall = true;;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 224 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        printf("call %s\n", tokens[(yyvsp[(1) - (6)].index)].value.c_str());
        printf("add esp, %d\n", 4 * (call_args + 1));
        printf("push eax\n");
        call_args = 0;
        isNumCall = false;
        opCountOutSideCall = 0;
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 235 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        localVariables[tokens[(yyvsp[(1) - (1)].index)].value] = ++localVariableCount;
    ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 238 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        localVariables[tokens[(yyvsp[(1) - (3)].index)].value] = ++localVariableCount;
        clearStack();
        singleExpression = true;
        printf("pop eax\n");
        printf("mov DWORD PTR [ebp - %d], eax\n", 4 * localVariableCount);
        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 245 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        localVariables[tokens[(yyvsp[(3) - (3)].index)].value] = ++localVariableCount;
        ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 248 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        localVariables[tokens[(yyvsp[(3) - (5)].index)].value] = ++localVariableCount;
        clearStack();
        singleExpression = true;
        printf("pop eax\n");
        printf("mov DWORD PTR [ebp - %d], eax\n", 4 * localVariableCount);
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 259 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        clearStackInFunc(opCountOutSideCall);
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 262 "E:/CompilerLabs/Compilerlab3/parser.y"
    {call_args++; isNumCall = false;;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 262 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        clearStackInFunc(opCountOutSideCall);
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 268 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        (yyval.index) = (yyvsp[(1) - (1)].index);
        cout << "push " << tokens[(yyvsp[(1) - (1)].index)].value << endl;
        oprands.push((yyvsp[(1) - (1)].index));
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 273 "E:/CompilerLabs/Compilerlab3/parser.y"
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

  case 39:

/* Line 1455 of yacc.c  */
#line 287 "E:/CompilerLabs/Compilerlab3/parser.y"
    {isNumCall = true; opCountOutSideCall = operators.size();;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 287 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
            printf("call %s\n", tokens[(yyvsp[(1) - (5)].index)].value.c_str());
            printf("add esp, %d\n", 4 * (call_args + 1));
            printf("push eax\n");
            call_args = 0;
        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 293 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[ADD]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 301 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[SUB]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 309 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[MUL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 317 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[DIV]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 325 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[MOD]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));

    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 334 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LESS]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 342 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LESS_EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 350 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[GREATER]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 358 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[GREATER_EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 366 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[EQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 374 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[NOTEQUAL]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 382 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_AND]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 390 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_OR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 398 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[BITWISE_XOR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 406 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LOGICAL_AND]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 414 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        while(operators.size() > opCountOutSideCall && priority[tokens[operators.top()].type] <= priority[LOGICAL_OR]){
            yytokentype op = tokens[operators.top()].type;
            operators.pop();
            opreate(op);
        }
        operators.push((yyvsp[(2) - (2)].index));

    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 423 "E:/CompilerLabs/Compilerlab3/parser.y"
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

  case 74:

/* Line 1455 of yacc.c  */
#line 437 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        singleExpression = false;

        printf("pop eax\n");
        printf("neg eax\n");
        printf("push eax\n");
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 444 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        singleExpression = false;

        printf("pop eax\n");
        printf("not eax\n");
        printf("push eax\n");
    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 451 "E:/CompilerLabs/Compilerlab3/parser.y"
    {
        operators.push((yyvsp[(1) - (1)].index));
    ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 453 "E:/CompilerLabs/Compilerlab3/parser.y"
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
#line 2213 "E:/CompilerLabs/Compilerlab3/cmake-build-debug/parser.cpp"
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
#line 463 "E:/CompilerLabs/Compilerlab3/parser.y"


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
    int vars = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        Token& token = tokens[i];
        if(token.type == LEFT_BRACE){
            inFunction = true;
        }
        if(token.type == RIGHT_BRACE){
            inFunction = false;
            functionVars.push_back(vars);
            vars = 0;
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

int main(int argc, char *argv[]){

    //ifstream file(argv[1]);
    ifstream file(R"(E:\CompilerLabs\Compilerlab3_copy\2.txt)");

    if (!file) {
        cerr << "Unable to open file!";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    yy_scan_string(content.c_str());
    lexing();
    // print();

    getFunctions();
    init();

    yy_scan_string(content.c_str());
    yyparse();

    return 0;
}
