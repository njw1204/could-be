
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
#line 1 "main.y"

#include <stdio.h>
#include <string.h>
#include "hashtable.h"
int yylex();
int yyerror(char *s);
int _yyerror(char *s, int yylineno);
void prepareParse();
extern int yylineno;

#define L_VALUE 1
#define R_VALUE 2

int errorCount = 0;
FILE *yyin;
HashTable symbolTable;
HashTable tempVarTable;
int debugVal = 0;
char buf[4096] = {0};
const YYNode ZERO_NODE = {0};


/* Line 189 of yacc.c  */
#line 96 "main.tab.c"

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

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 94 "main.y"

	#include "yynode.h"
	#include "linkedlist.h"



/* Line 209 of yacc.c  */
#line 127 "main.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TYPE_INT = 258,
     TYPE_FLOAT = 259,
     MAINPROG = 260,
     FUNCTION = 261,
     PROCEDURE = 262,
     BEGIN_BODY = 263,
     END_BODY = 264,
     IF = 265,
     THEN = 266,
     ELIF = 267,
     ELSE = 268,
     NOP = 269,
     WHILE = 270,
     FOR = 271,
     RETURN = 272,
     PRINT = 273,
     IN = 274,
     ID = 275,
     FLOAT = 276,
     INTEGER = 277,
     OP_EQ = 278,
     OP_NE = 279,
     OP_LE = 280,
     OP_GE = 281,
     OP_LT = 282,
     OP_GT = 283
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 99 "main.y"

	char name[1024];
	int intData;
	float floatData;
	struct YYNode nodeData;
	List nodeList;



/* Line 214 of yacc.c  */
#line 182 "main.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 194 "main.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   136

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  141

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,     2,     2,     2,
      34,    35,    40,    38,    31,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,    30,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    10,    15,    16,    18,    22,    24,    29,
      31,    33,    36,    37,    41,    48,    53,    57,    58,    62,
      68,    72,    74,    78,    82,    84,    86,    88,    90,    92,
      94,    97,    99,   104,   112,   118,   127,   133,   138,   143,
     151,   156,   164,   166,   171,   173,   178,   183,   185,   186,
     188,   192,   194,   196,   200,   204,   206,   210,   212,   216,
     218,   220,   222,   224,   227,   230,   232,   234,   236,   238,
     240,   242,   244,   246,   248,   250,   252
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,     5,    20,    30,    44,    48,    53,    -1,
      46,    45,    30,    44,    -1,    -1,    20,    -1,    20,    31,
      45,    -1,    47,    -1,    47,    32,    22,    33,    -1,     3,
      -1,     4,    -1,    49,    48,    -1,    -1,    50,    44,    53,
      -1,     6,    20,    51,    29,    47,    30,    -1,     7,    20,
      51,    30,    -1,    34,    52,    35,    -1,    -1,    45,    29,
      46,    -1,    45,    29,    46,    30,    52,    -1,     8,    54,
       9,    -1,    55,    -1,    55,    30,    54,    -1,    61,    36,
      65,    -1,    60,    -1,    62,    -1,    53,    -1,    56,    -1,
      58,    -1,    59,    -1,    17,    65,    -1,    14,    -1,    10,
      65,    29,    55,    -1,    10,    65,    29,    55,    13,    29,
      55,    -1,    10,    65,    29,    55,    57,    -1,    10,    65,
      29,    55,    57,    13,    29,    55,    -1,    12,    65,    29,
      55,    57,    -1,    12,    65,    29,    55,    -1,    15,    65,
      29,    55,    -1,    15,    65,    29,    55,    13,    29,    55,
      -1,    16,    66,    29,    55,    -1,    16,    66,    29,    55,
      13,    29,    55,    -1,    18,    -1,    18,    34,    65,    35,
      -1,    20,    -1,    20,    32,    65,    33,    -1,    20,    34,
      63,    35,    -1,    64,    -1,    -1,    65,    -1,    65,    31,
      64,    -1,    67,    -1,    66,    -1,    67,    71,    67,    -1,
      67,    19,    67,    -1,    68,    -1,    68,    72,    67,    -1,
      69,    -1,    69,    73,    68,    -1,    22,    -1,    21,    -1,
      61,    -1,    62,    -1,    37,    69,    -1,    70,    69,    -1,
      38,    -1,    39,    -1,    28,    -1,    26,    -1,    27,    -1,
      25,    -1,    23,    -1,    24,    -1,    38,    -1,    39,    -1,
      40,    -1,    41,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   116,   129,   134,   142,   155,   158,   167,
     167,   172,   177,   180,   201,   210,   221,   222,   225,   237,
     254,   261,   265,   272,   281,   282,   283,   284,   285,   286,
     287,   294,   302,   312,   324,   335,   350,   365,   383,   394,
     410,   420,   436,   441,   453,   458,   467,   494,   495,   498,
     502,   511,   518,   519,   533,   570,   575,   586,   590,   597,
     603,   609,   612,   620,   635,   650,   651,   654,   655,   656,
     657,   658,   659,   662,   663,   666,   667
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"int\"", "\"float\"", "\"mainprog\"",
  "\"function\"", "\"procedure\"", "\"begin\"", "\"end\"", "\"if\"",
  "\"then\"", "\"elif\"", "\"else\"", "\"nop\"", "\"while\"", "\"for\"",
  "\"return\"", "\"print\"", "\"in\"", "\"identifier\"",
  "\"decimal number\"", "\"integer number\"", "\"==\"", "\"!=\"", "\"<=\"",
  "\">=\"", "\"<\"", "\">\"", "':'", "';'", "','", "'['", "']'", "'('",
  "')'", "'='", "'!'", "'+'", "'-'", "'*'", "'/'", "$accept", "program",
  "declarations", "identifier_list", "type", "standard_type",
  "subprogram_declarations", "subprogram_declaration", "subprogram_head",
  "arguments", "parameter_list", "compound_statement", "statement_list",
  "statement", "if_statement", "elif_statement", "while_statement",
  "for_statement", "print_statement", "variable", "procedure_statement",
  "actual_parameter_expression", "expression_list", "expression",
  "in_expression", "simple_expression", "term", "factor", "sign", "relop",
  "addop", "multop", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    58,
      59,    44,    91,    93,    40,    41,    61,    33,    43,    45,
      42,    47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    47,
      47,    48,    48,    49,    50,    50,    51,    51,    52,    52,
      53,    54,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    56,    56,    56,    57,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    63,    63,    64,
      64,    65,    65,    65,    66,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    70,    70,    71,    71,    71,
      71,    71,    71,    72,    72,    73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     4,     0,     1,     3,     1,     4,     1,
       1,     2,     0,     3,     6,     4,     3,     0,     3,     5,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       2,     1,     4,     7,     5,     8,     5,     4,     4,     7,
       4,     7,     1,     4,     1,     4,     4,     1,     0,     1,
       3,     1,     1,     3,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     9,    10,    12,     0,
       7,     0,     0,     0,    12,     4,     5,     0,     0,    17,
      17,     0,     2,    11,     0,     0,     4,     0,     0,     0,
       0,     0,    31,     0,     0,     0,    42,    44,    26,     0,
      21,    27,    28,    29,    24,     0,    25,    13,     6,     3,
       8,     0,     0,     0,    15,    60,    59,     0,    65,    66,
      61,    62,     0,    52,    51,    55,    57,     0,     0,     0,
       0,    30,     0,     0,    48,    20,     0,     0,     0,    16,
       0,    63,     0,     0,    71,    72,    70,    68,    69,    67,
       0,    73,    74,     0,    75,    76,     0,    64,     0,     0,
       0,     0,     0,    47,    49,    22,    23,    18,    14,    32,
      54,    53,    56,    58,    38,    40,    43,    45,    46,     0,
       0,     0,     0,    34,     0,     0,    50,    19,     0,     0,
       0,     0,     0,     0,    33,     0,    39,    41,    37,    35,
      36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     8,    51,     9,    10,    13,    14,    15,    29,
      52,    38,    39,    40,    41,   123,    42,    43,    44,    60,
      61,   102,   103,   104,    63,    64,    65,    66,    67,    90,
      93,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -65
static const yytype_int8 yypact[] =
{
       8,    -1,    32,    19,   -65,    12,   -65,   -65,    31,    30,
      21,    34,    36,    43,    31,    12,    26,    28,    41,    38,
      38,    13,   -65,   -65,    43,    30,    12,    37,    30,    35,
      44,   -13,   -65,   -13,   -13,   -13,    39,   -20,   -65,    66,
      46,   -65,   -65,   -65,   -65,    45,   -65,   -65,   -65,   -65,
     -65,    50,    55,    12,   -65,   -65,   -65,   -13,   -65,   -65,
     -65,   -65,    62,   -65,    61,     1,     5,   -13,    64,    65,
      76,   -65,   -13,   -13,   -13,   -65,    13,   -13,    12,   -65,
      67,   -65,    13,   -13,   -65,   -65,   -65,   -65,   -65,   -65,
     -13,   -65,   -65,   -13,   -65,   -65,   -13,   -65,    13,    13,
      63,    68,    69,   -65,    71,   -65,   -65,    70,   -65,    29,
     -65,   -65,   -65,   -65,    83,    86,   -65,   -65,   -65,   -13,
      30,   -13,    74,    92,    77,    78,   -65,   -65,    80,    13,
      89,    13,    13,    13,   -65,    13,   -65,   -65,   108,   -65,
     -65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,   -65,    -4,    -8,    47,    73,   107,   -65,   -65,   102,
       3,    23,    48,   -64,   -65,   -11,   -65,   -65,   -65,   -21,
     -16,   -65,     9,   -29,    95,   -31,    40,   -47,   -65,   -65,
     -65,   -65
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      45,    17,    62,    70,    68,    46,    71,    37,    55,    56,
      81,    24,    73,     1,    74,     6,     7,    48,   109,     3,
      97,    21,    49,    31,    57,    58,    59,    32,    33,    34,
      35,    36,     4,    37,   114,   115,    22,    11,    12,    91,
      92,   121,   122,   100,   101,    94,    95,    47,   106,     5,
      16,    21,   110,    18,    19,    45,    20,    25,    26,   111,
      46,    45,   112,    27,    53,   134,    46,   136,   137,   138,
      50,   139,    28,    72,    54,    75,    76,    45,    45,    78,
      83,    77,    46,    46,    84,    85,    86,    87,    88,    89,
      79,    82,   128,    98,    99,    83,   124,   108,   116,   125,
     120,   117,   119,   129,   118,   130,   131,   132,    45,   133,
      45,    45,    45,    46,    45,    46,    46,    46,   135,    46,
     121,    23,    30,   127,   105,   107,    80,   140,   126,    69,
       0,     0,     0,     0,     0,     0,   113
};

static const yytype_int16 yycheck[] =
{
      21,     9,    31,    34,    33,    21,    35,    20,    21,    22,
      57,    15,    32,     5,    34,     3,     4,    25,    82,    20,
      67,     8,    26,    10,    37,    38,    39,    14,    15,    16,
      17,    18,     0,    20,    98,    99,    13,     6,     7,    38,
      39,    12,    13,    72,    73,    40,    41,    24,    77,    30,
      20,     8,    83,    32,    20,    76,    20,    31,    30,    90,
      76,    82,    93,    22,    29,   129,    82,   131,   132,   133,
      33,   135,    34,    34,    30,     9,    30,    98,    99,    29,
      19,    36,    98,    99,    23,    24,    25,    26,    27,    28,
      35,    29,   121,    29,    29,    19,    13,    30,    35,    13,
      30,    33,    31,    29,    35,    13,    29,    29,   129,    29,
     131,   132,   133,   129,   135,   131,   132,   133,    29,   135,
      12,    14,    20,   120,    76,    78,    53,   138,   119,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    43,    20,     0,    30,     3,     4,    44,    46,
      47,     6,     7,    48,    49,    50,    20,    45,    32,    20,
      20,     8,    53,    48,    44,    31,    30,    22,    34,    51,
      51,    10,    14,    15,    16,    17,    18,    20,    53,    54,
      55,    56,    58,    59,    60,    61,    62,    53,    45,    44,
      33,    45,    52,    29,    30,    21,    22,    37,    38,    39,
      61,    62,    65,    66,    67,    68,    69,    70,    65,    66,
      67,    65,    34,    32,    34,     9,    30,    36,    29,    35,
      47,    69,    29,    19,    23,    24,    25,    26,    27,    28,
      71,    38,    39,    72,    40,    41,    73,    69,    29,    29,
      65,    65,    63,    64,    65,    54,    65,    46,    30,    55,
      67,    67,    67,    68,    55,    55,    35,    33,    35,    31,
      30,    12,    13,    57,    13,    13,    64,    52,    65,    29,
      13,    29,    29,    29,    55,    29,    55,    55,    55,    55,
      57
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
        case 2:

/* Line 1455 of yacc.c  */
#line 110 "main.y"
    {
	;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 116 "main.y"
    {
		(yyval.nodeList) = (yyvsp[(2) - (4)].nodeList);
		for (ListNode *curr = (yyvsp[(2) - (4)].nodeList); curr; curr = nextNode((yyvsp[(2) - (4)].nodeList), curr)) {
			if ((yyvsp[(1) - (4)].intData) == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = (yyvsp[(1) - (4)].intData); // 배열 길이
			}
		}
		concatList(&((yyval.nodeList)), (yyvsp[(4) - (4)].nodeList));
	;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 129 "main.y"
    {
		(yyval.nodeList) = createList();
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 134 "main.y"
    {
		(yyval.nodeList) = createList();
		YYNode node = {0};
		node.type = T_ID;
		node.iParam[0] = yylineno;
		strcpy(node.sParam[0], (yyvsp[(1) - (1)].name)); // 식별자 이름
		appendToList(&((yyval.nodeList)), node);
	;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 142 "main.y"
    {
		(yyval.nodeList) = createList();
		YYNode node = {0};
		node.type = T_ID;
		node.iParam[0] = yylineno;
		strcpy(node.sParam[0], (yyvsp[(1) - (3)].name)); // 식별자 이름
		appendToList(&((yyval.nodeList)), node);
		concatList(&((yyval.nodeList)), (yyvsp[(3) - (3)].nodeList));
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 155 "main.y"
    {
		(yyval.intData) = T_VAR;
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 158 "main.y"
    {
		(yyval.intData) = (yyvsp[(3) - (4)].intData);  // 배열 길이
		if ((yyvsp[(3) - (4)].intData) < 1) {
			sprintf(buf, "array must have positive size");
			yyerror(buf);
		}
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 172 "main.y"
    {
		(yyval.nodeList) = createList();
		appendToList(&((yyval.nodeList)), (yyvsp[(1) - (2)].nodeData));
		concatList(&((yyval.nodeList)), (yyvsp[(2) - (2)].nodeList));
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 177 "main.y"
    { (yyval.nodeList) = createList(); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 180 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_SUBPROGRAM_DECL;
		(yyval.nodeData).iParam[0] = yylineno;

		if (!findFromHashTable(&symbolTable, (yyvsp[(1) - (3)].nodeData).sParam[0])) {
			insertToHashTable(&symbolTable, (yyvsp[(1) - (3)].nodeData).sParam[0], (yyvsp[(1) - (3)].nodeData));
			(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
			(yyval.nodeData).rParam[2] = malloc(sizeof(YYNode));

			*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(1) - (3)].nodeData); // 함수 시그니처 (nodeData)
			(yyval.nodeData).rParam[1] = (yyvsp[(2) - (3)].nodeList); // 지역변수 목록 (nodeList)
			*((YYNode*)(yyval.nodeData).rParam[2]) = (yyvsp[(3) - (3)].nodeData); // compound_statement (nodeData)
		}
		else {
			sprintf(buf, "identifier \"%s\" is declared duplicately", (yyvsp[(1) - (3)].nodeData).sParam[0]);
			_yyerror(buf, (yyvsp[(1) - (3)].nodeData).iParam[0]);
		}
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 201 "main.y"
    {
		YYNode node;
		node.type = T_FUNCTION;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList((yyvsp[(3) - (6)].nodeList)); // 매개변수 개수
		node.rParam[0] = (yyvsp[(3) - (6)].nodeList); // 매개변수 목록 (nodeList)
		strcpy(node.sParam[0], (yyvsp[(2) - (6)].name)); // 함수 이름
		(yyval.nodeData) = node;
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 210 "main.y"
    {
		YYNode node;
		node.type = T_PROCEDURE;
		node.iParam[0] = yylineno;
		node.iParam[1] = lengthOfList((yyvsp[(3) - (4)].nodeList)); // 매개변수 개수
		node.rParam[0] = (yyvsp[(3) - (4)].nodeList); // 매개변수 목록 (nodeList)
		strcpy(node.sParam[0], (yyvsp[(2) - (4)].name)); // 프로시저 이름
		(yyval.nodeData) = node;
	;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 221 "main.y"
    { (yyval.nodeList) = (yyvsp[(2) - (3)].nodeList); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 222 "main.y"
    { (yyval.nodeList) = createList(); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 225 "main.y"
    {
		(yyval.nodeList) = (yyvsp[(1) - (3)].nodeList);
		for (ListNode *curr = (yyvsp[(1) - (3)].nodeList); curr; curr = nextNode((yyvsp[(1) - (3)].nodeList), curr)) {
			if ((yyvsp[(3) - (3)].intData) == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = (yyvsp[(3) - (3)].intData); // 배열 길이
			}
		}
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 237 "main.y"
    {
		(yyval.nodeList) = (yyvsp[(1) - (5)].nodeList);
		for (ListNode *curr = (yyvsp[(1) - (5)].nodeList); curr; curr = nextNode((yyvsp[(1) - (5)].nodeList), curr)) {
			if ((yyvsp[(3) - (5)].intData) == T_VAR) {
				curr->data.type = T_VAR;
			}
			else {
				curr->data.type = T_ARRAY;
				curr->data.iParam[1] = (yyvsp[(3) - (5)].intData); // 배열 길이
			}
		}
		concatList(&((yyval.nodeList)), (yyvsp[(5) - (5)].nodeList));
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 254 "main.y"
    {
		(yyval.nodeData).type = T_COMPOUND;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = (yyvsp[(2) - (3)].nodeList); // statement_list (nodeList)
	;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 261 "main.y"
    {
		(yyval.nodeList) = createList();
		appendToList(&((yyval.nodeList)), (yyvsp[(1) - (1)].nodeData));
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 265 "main.y"
    {
		(yyval.nodeList) = createList();
		appendToList(&((yyval.nodeList)), (yyvsp[(1) - (3)].nodeData));
		concatList(&((yyval.nodeList)), (yyvsp[(3) - (3)].nodeList));
	;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 272 "main.y"
    {
		(yyval.nodeData).type = T_ASSIGN;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(1) - (3)].nodeData); // variable (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(3) - (3)].nodeData); // expression (nodeData)
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 281 "main.y"
    {(yyval.nodeData) = (yyvsp[(1) - (1)].nodeData);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 282 "main.y"
    {(yyval.nodeData) = (yyvsp[(1) - (1)].nodeData);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 283 "main.y"
    { (yyval.nodeData) = (yyvsp[(1) - (1)].nodeData); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 284 "main.y"
    {(yyval.nodeData) = (yyvsp[(1) - (1)].nodeData);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 285 "main.y"
    {(yyval.nodeData) = (yyvsp[(1) - (1)].nodeData);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 286 "main.y"
    {(yyval.nodeData) = (yyvsp[(1) - (1)].nodeData);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 287 "main.y"
    {
		(yyval.nodeData).type = T_RETURN;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (2)].nodeData); // expression (nodeData)
	;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 294 "main.y"
    {
		(yyval.nodeData).type = T_NONE;
		(yyval.nodeData).iParam[0] = yylineno;
	;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 302 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_IF;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (4)].nodeData); // expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (4)].nodeData); // statement (nodeData)
	;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 312 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_IF_ELSE;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[2] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (7)].nodeData); // expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (7)].nodeData); // statement (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[2]) = (yyvsp[(7) - (7)].nodeData); // else statement (nodeData)
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 324 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_IF_ELIF;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (5)].nodeData); // expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (5)].nodeData); // statement (nodeData)
		(yyval.nodeData).rParam[2] = (yyvsp[(5) - (5)].nodeList); // elif statement list (nodeList)
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 335 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_IF_ELIF_ELSE;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[3] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (8)].nodeData); // expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (8)].nodeData); // statement (nodeData)
		(yyval.nodeData).rParam[2] = (yyvsp[(5) - (8)].nodeList); // elif statement list (nodeList)
		*((YYNode*)(yyval.nodeData).rParam[3]) = (yyvsp[(8) - (8)].nodeData); // else statement (nodeData)
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 350 "main.y"
    {
		(yyval.nodeList) = createList();

		YYNode node = {0};
		node.type = T_ELIF;
		node.iParam[0] = yylineno;
		node.rParam[0] = malloc(sizeof(YYNode));
		node.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)node.rParam[0]) = (yyvsp[(2) - (5)].nodeData);
		*((YYNode*)node.rParam[1]) = (yyvsp[(4) - (5)].nodeData);

		appendToList(&((yyval.nodeList)), node);
		concatList(&((yyval.nodeList)), (yyvsp[(5) - (5)].nodeList));
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 365 "main.y"
    {
		(yyval.nodeList) = createList();

		YYNode node = {0};
		node.type = T_ELIF;
		node.iParam[0] = yylineno;
		node.rParam[0] = malloc(sizeof(YYNode));
		node.rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)node.rParam[0]) = (yyvsp[(2) - (4)].nodeData);
		*((YYNode*)node.rParam[1]) = (yyvsp[(4) - (4)].nodeData);

		appendToList(&((yyval.nodeList)), node);
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 383 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_WHILE_STMT;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (4)].nodeData); // expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (4)].nodeData); // statement (nodeData)

	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 394 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_WHILE_ELSE_STMT;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[2] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (7)].nodeData); // expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (7)].nodeData); // statement (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[2]) = (yyvsp[(7) - (7)].nodeData); // else statement (nodeData)
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 410 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_FOR_STMT;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (4)].nodeData); // in_expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (4)].nodeData); // statement (nodeData)
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 420 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_FOR_ELSE_STMT;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[2] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(2) - (7)].nodeData); // expression (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(4) - (7)].nodeData); // statement (nodeData)
		*((YYNode*)(yyval.nodeData).rParam[2]) = (yyvsp[(7) - (7)].nodeData); // else statement (nodeData)
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 436 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_NONE;
		(yyval.nodeData).iParam[0] = yylineno;
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 441 "main.y"
    {
		(yyval.nodeData) = (yyvsp[(3) - (4)].nodeData);
		(yyval.nodeData).type = T_PRINT_STMT;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(3) - (4)].nodeData); // expression (nodeData)
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 453 "main.y"
    {
		(yyval.nodeData).type = T_VAR_USING;
		(yyval.nodeData).iParam[0] = yylineno;
		strcpy((yyval.nodeData).sParam[0], (yyvsp[(1) - (1)].name)); // 식별자 이름
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 458 "main.y"
    {
		(yyval.nodeData).type = T_ARRAY_USING;
		(yyval.nodeData).iParam[0] = yylineno;
		strcpy((yyval.nodeData).sParam[0], (yyvsp[(1) - (4)].name)); // 식별자 이름
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 467 "main.y"
    {
		YYNode *nodePtr = findFromHashTable(&symbolTable, (yyvsp[(1) - (4)].name));
		int paraLen = lengthOfList((yyvsp[(3) - (4)].nodeList));
		(yyval.nodeData).iParam[0] = yylineno;

		if (nodePtr == NULL) {
			sprintf(buf, "undeclared identifier \"%s\"", (yyvsp[(1) - (4)].name));
			yyerror(buf);
			(yyval.nodeData).type = T_FUNCTION_CALL;
		}
		else if (nodePtr->type != T_FUNCTION && nodePtr->type != T_PROCEDURE) {
			sprintf(buf, "\"%s\" is not function or procedure", (yyvsp[(1) - (4)].name));
			yyerror(buf);
			(yyval.nodeData).type = T_FUNCTION_CALL;
		}
		else if (nodePtr->iParam[1] != paraLen) {
			sprintf(buf, "\"%s\" expect %d parameter, but %d given", (yyvsp[(1) - (4)].name), nodePtr->iParam[1], paraLen);
			yyerror(buf);
			(yyval.nodeData).type = T_FUNCTION_CALL;
		}
		else {
			if (nodePtr->type == T_FUNCTION) (yyval.nodeData).type = T_FUNCTION_CALL;
			else (yyval.nodeData).type = T_PROCEDURE_CALL;
		}
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 494 "main.y"
    { (yyval.nodeList) = (yyvsp[(1) - (1)].nodeList); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 495 "main.y"
    { (yyval.nodeList) = createList(); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 498 "main.y"
    {
		(yyval.nodeList) = createList();
		appendToList(&((yyval.nodeList)), (yyvsp[(1) - (1)].nodeData));
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 502 "main.y"
    {
		(yyval.nodeList) = createList();
		appendToList(&((yyval.nodeList)), (yyvsp[(1) - (3)].nodeData));
		concatList(&((yyval.nodeList)), (yyvsp[(3) - (3)].nodeList));
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 511 "main.y"
    {
		(yyval.nodeData) = (yyvsp[(1) - (1)].nodeData);

		// $$.type = T_SIMPLE_EXPR;
		// $$.iParam[0] = yylineno;
		// $$.rParam[0] = $1;
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 518 "main.y"
    { (yyval.nodeData) = (yyvsp[(1) - (1)].nodeData); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 519 "main.y"
    {
		(yyval.nodeData).type = T_RELOP_EXPR;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));

		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(1) - (3)].nodeData); // left simple_expression
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(3) - (3)].nodeData); // right simple_expression

		// $$.rParam[0] = $1;
		// $$.rParam[1] = $3;
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 533 "main.y"
    {
		int llistLen = lengthOfList((yyvsp[(1) - (3)].nodeData).rParam[0]), rlistLen = lengthOfList((yyvsp[(3) - (3)].nodeData).rParam[0]);
		if (rlistLen > 1) {
			sprintf(buf, "expect l-value on the right side of \"in\", but r-value given");
			yyerror(buf);
		}
		else {
			ListNode rNode = *((ListNode*)(yyvsp[(3) - (3)].nodeData).rParam[0]);
			if (rNode.data.type != T_VAR_USING) {
				sprintf(buf, "expect l-value on the right side of \"in\", but r-value given");
				yyerror(buf);
			}
		}

		(yyval.nodeData).type = T_IN_EXPR;
		(yyval.nodeData).iParam[0] = yylineno;

		if (llistLen > 1) {
			(yyval.nodeData).iParam[1] = R_VALUE; // left r-value
		}
		else {
			ListNode lNode = *((ListNode*)(yyvsp[(1) - (3)].nodeData).rParam[0]);
			if (lNode.data.type == T_VAR || lNode.data.type == T_ARRAY) {
				(yyval.nodeData).iParam[1] = L_VALUE; // left l-value
			}
			else {
				(yyval.nodeData).iParam[1] = R_VALUE; // left r-value
			}
		}

		(yyval.nodeData).rParam[0] = malloc(sizeof(YYNode));
		(yyval.nodeData).rParam[1] = malloc(sizeof(YYNode));
		*((YYNode*)(yyval.nodeData).rParam[0]) = (yyvsp[(1) - (3)].nodeData); // simple_expression, left node
		*((YYNode*)(yyval.nodeData).rParam[1]) = (yyvsp[(3) - (3)].nodeData); // simple_expression, right node
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 570 "main.y"
    {
		(yyval.nodeData).type = T_SIMPLE_EXPR;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = (yyvsp[(1) - (1)].nodeList); // term (nodeList)
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 575 "main.y"
    {
		(yyval.nodeData).type = T_SIMPLE_EXPR;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).rParam[0] = (yyvsp[(1) - (3)].nodeList); // term (only include operands, nodeList)

		List temp = (yyval.nodeData).rParam[0];
		concatList(&temp, (yyvsp[(3) - (3)].nodeData).rParam[0]); // append another term (nodeList)
		(yyval.nodeData).rParam[0] = temp;
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 586 "main.y"
    {
		(yyval.nodeList) = createList();
		appendToList(&((yyval.nodeList)), (yyvsp[(1) - (1)].nodeData));
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 590 "main.y"
    {
		(yyval.nodeList) = createList();
		appendToList(&((yyval.nodeList)), (yyvsp[(1) - (3)].nodeData));
		concatList(&((yyval.nodeList)), (yyvsp[(3) - (3)].nodeList));
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 597 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_CONST_INTEGER;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).iParam[1] = (yyvsp[(1) - (1)].intData); // value
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 603 "main.y"
    {
		(yyval.nodeData) = ZERO_NODE;
		(yyval.nodeData).type = T_CONST_FLOAT;
		(yyval.nodeData).iParam[0] = yylineno;
		(yyval.nodeData).fParam[1] = (yyvsp[(1) - (1)].floatData); // value
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 609 "main.y"
    {
		(yyval.nodeData) = (yyvsp[(1) - (1)].nodeData); // variable (nodeData, type : T_VAR_USING or T_ARRAY_USING)
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 612 "main.y"
    {
		if ((yyvsp[(1) - (1)].nodeData).type == T_PROCEDURE_CALL) {
			sprintf(buf, "\"%s\" is not function so it doesn't have return value", (yyvsp[(1) - (1)].nodeData).sParam[0]);
			yyerror(buf);
		}
		(yyval.nodeData).type = T_DYNAMIC_FACTOR;
		(yyval.nodeData).iParam[0] = yylineno;
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 620 "main.y"
    {
		(yyval.nodeData).iParam[0] = yylineno;
		if ((yyvsp[(2) - (2)].nodeData).type == T_CONST_INTEGER || (yyvsp[(2) - (2)].nodeData).type == T_CONST_FLOAT) {
			(yyval.nodeData).type = (yyvsp[(2) - (2)].nodeData).type;

			if ((yyvsp[(2) - (2)].nodeData).iParam[1]) (yyval.nodeData).iParam[1] = 0;
			else (yyval.nodeData).iParam[1] = 1;

			if ((yyvsp[(2) - (2)].nodeData).fParam[1]) (yyval.nodeData).fParam[1] = 0;
			else (yyval.nodeData).fParam[1] = 1;
		}
		else {
			(yyval.nodeData).type = T_DYNAMIC_FACTOR;
		}
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 635 "main.y"
    {
		(yyval.nodeData).iParam[0] = yylineno;
		if ((yyvsp[(2) - (2)].nodeData).type == T_CONST_INTEGER || (yyvsp[(2) - (2)].nodeData).type == T_CONST_FLOAT) {
			(yyval.nodeData).type = (yyvsp[(2) - (2)].nodeData).type;
			(yyval.nodeData).iParam[1] = -(yyvsp[(2) - (2)].nodeData).iParam[1];
			(yyval.nodeData).fParam[1] = -(yyvsp[(2) - (2)].nodeData).fParam[1];
		}
		else {
			(yyval.nodeData).type = T_DYNAMIC_FACTOR;
		}
	;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 650 "main.y"
    {;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 651 "main.y"
    {;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 654 "main.y"
    {;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 655 "main.y"
    {;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 656 "main.y"
    {;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 657 "main.y"
    {;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 658 "main.y"
    {;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 659 "main.y"
    {;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 662 "main.y"
    {;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 663 "main.y"
    {;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 666 "main.y"
    {;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 667 "main.y"
    {;}
    break;



/* Line 1455 of yacc.c  */
#line 2429 "main.tab.c"
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
#line 670 "main.y"


int yyerror(char *s) {
	_yyerror(s, yylineno);
}

int _yyerror(char *s, int yylineno) {
	printf("Error: %s at line %d\n", s, yylineno);
	errorCount++;
	return 0;
}

void prepareParse() {
	symbolTable = createHashTable();
}

int main(int argc, char *argv[]) {
	if (argc == 2) {
		yyin = fopen(argv[1], "r");
		if (yyin) {
			prepareParse();
			if (yyparse() == 0) {
				if (errorCount == 0) {
					printf("[Compile OK]\n");
				}
				else {
					printf("[Compile Fail]\n");
				}
			}
			else {
				printf("[Compile Fail]\n");
			}
			fclose(yyin);
		}
		else {
			printf("Error: Can't open the file (%s)\n", argv[1]);
		}
	}
	else if (argc > 2) {
		printf("Error: Please enter only one argument\n");
	}
	else {
		printf("Error: Please enter source file name as command line argument\n");
	}
	return 0;
}

