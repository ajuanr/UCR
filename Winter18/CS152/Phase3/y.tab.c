/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 4 "mini_l.y" /* yacc.c:339  */

#define YY_NO_UNPUT

#include "headers.h"

extern int currLine;	
extern int currPos;
extern char *yytext;

void yyerror(char const*);
int yylex(void);

struct Symbol{
   Symbol():value(0){}
   Symbol(string n):name(n) {}
   Symbol(string n, string t): name(n), type(t){}
   Symbol(string n, string t, int l):name(n), type(t),size(l) {}
   string name;
   string type;
   bool param=false;
   int size;  // for arrays
   int value;
   bool operator==(const string &rhs) { return !(this->name.compare(rhs));}
};

typedef list<string> lstStr;
typedef vector<string> vecStr;
typedef list<Symbol> Table;
typedef stack<string> stackStr;
typedef deque<string> DeckStr;

string genQuad(string op, string dest, string srcl, string src2);
string genQuad(string op, string dest , string src2);
string newLabel();
string newTemp();
string newPred();
Table symTable;
DeckStr funcParams;		// keep track of parameters in functions
stackStr indexStack;
lstStr funcTable;	// keep track of functions;
stackStr varStack;	// keep track of vars
DeckStr labelStack;	// keep track of labels
DeckStr loopStack;	// keep track of which loop you're in
stackStr rwStack;
int currentTemp = 0; 	// the current number of temporary variables
int currentLabel = 0; 	// the current number of labels
int currentPred = 0;    // the current predicate
bool addParams = false;
bool errorFound = false;
lstStr milCode;		// holds the code generated
stackStr identStack;   	// holds list of identifiers seen


#line 120 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FUNCTION = 258,
    INTEGER = 259,
    OF = 260,
    ARRAY = 261,
    READ = 262,
    IF = 263,
    THEN = 264,
    ENDIF = 265,
    ELSE = 266,
    WHILE = 267,
    DO = 268,
    BEGIN_PARAMS = 269,
    BEGIN_LOCALS = 270,
    BEGIN_BODY = 271,
    IN = 272,
    BEGINLOOP = 273,
    ENDLOOP = 274,
    RETURN = 275,
    END_PARAMS = 276,
    END_LOCALS = 277,
    END_BODY = 278,
    CONTINUE = 279,
    WRITE = 280,
    TRUE = 281,
    FALSE = 282,
    FOREACH = 283,
    SEMICOLON = 284,
    COLON = 285,
    COMMA = 286,
    L_PAREN = 287,
    R_PAREN = 288,
    L_SQUARE_BRACKET = 289,
    R_SQUARE_BRACKET = 290,
    NUMBER = 291,
    IDENT = 292,
    UMINUS = 293,
    MULT = 294,
    DIV = 295,
    MOD = 296,
    ADD = 297,
    SUB = 298,
    LT = 299,
    LTE = 300,
    GT = 301,
    GTE = 302,
    EQ = 303,
    NEQ = 304,
    NOT = 305,
    AND = 306,
    OR = 307,
    ASSIGN = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 57 "mini_l.y" /* yacc.c:355  */

   int		iVal;
   string* 	strVal;
typedef struct Attributes{
   string* name;
   string* code;
   string* type;
   int size; // for arrays
   int value;
}Attributes;
   Attributes attribute;

#line 227 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 244 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  154

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,    99,   100,   102,   127,   131,   132,   135,
     136,   139,   157,   173,   174,   177,   178,   181,   235,   236,
     237,   243,   247,   248,   264,   280,   289,   290,   295,   299,
     311,   320,   328,   332,   335,   343,   348,   354,   365,   368,
     377,   382,   389,   394,   399,   406,   407,   408,   409,   410,
     411,   414,   419,   427,   437,   441,   449,   457,   467,   472,
     478,   490,   493,   498,   502,   508,   515,   518,   523,   526,
     532,   554,   576,   577,   580,   581,   584,   590
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNCTION", "INTEGER", "OF", "ARRAY",
  "READ", "IF", "THEN", "ENDIF", "ELSE", "WHILE", "DO", "BEGIN_PARAMS",
  "BEGIN_LOCALS", "BEGIN_BODY", "IN", "BEGINLOOP", "ENDLOOP", "RETURN",
  "END_PARAMS", "END_LOCALS", "END_BODY", "CONTINUE", "WRITE", "TRUE",
  "FALSE", "FOREACH", "SEMICOLON", "COLON", "COMMA", "L_PAREN", "R_PAREN",
  "L_SQUARE_BRACKET", "R_SQUARE_BRACKET", "NUMBER", "IDENT", "UMINUS",
  "MULT", "DIV", "MOD", "ADD", "SUB", "LT", "LTE", "GT", "GTE", "EQ",
  "NEQ", "NOT", "AND", "OR", "ASSIGN", "$accept", "prog_start",
  "functions", "function", "funcName", "begin_params", "end_params",
  "declarations", "declaration", "statements", "statement", "foreach",
  "while", "ifCond", "else", "endif", "M5", "do", "M8", "bool_exp",
  "relation_and_exp", "relation_exp", "comp", "expression",
  "multiplicative_expression", "term", "terms", "parenExpression",
  "expressions", "vars", "var", "identifiers", "ident", "number", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -100

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-100)))

#define YYTABLE_NINF -77

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      30,    13,    59,  -100,    30,    37,  -100,  -100,  -100,    65,
    -100,    44,  -100,    62,    67,    68,    66,  -100,    85,    44,
      81,    44,    44,  -100,  -100,  -100,    71,  -100,    79,    17,
      86,    76,  -100,    93,   174,   125,   128,   -27,     7,     5,
       5,  -100,    24,  -100,     7,    44,   106,   109,   122,   123,
     152,   127,    87,   108,   142,   146,    24,   117,  -100,   126,
    -100,  -100,     5,    75,    26,     5,   145,   103,   105,   226,
      49,  -100,  -100,  -100,  -100,  -100,    24,   -14,  -100,  -100,
    -100,   124,    44,   200,    64,   200,    24,    24,  -100,  -100,
      29,     7,   133,   218,  -100,    24,  -100,  -100,  -100,  -100,
       5,     5,    24,    24,  -100,  -100,  -100,  -100,  -100,  -100,
      24,    24,    24,    24,    -3,  -100,  -100,   139,  -100,  -100,
     222,  -100,   148,   -14,    35,  -100,  -100,  -100,  -100,   -20,
     135,  -100,  -100,    49,    49,   -14,  -100,  -100,  -100,   151,
    -100,   160,  -100,  -100,    24,  -100,   200,  -100,   159,  -100,
     154,     5,  -100,  -100
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     2,     4,     0,     6,     1,     3,     0,
       7,    10,    76,     0,     0,     0,    74,     8,     0,    10,
       0,     0,    10,     9,    14,    11,     0,    75,     0,     0,
       0,     0,    77,     0,     0,     0,     0,    26,     0,     0,
       0,    34,     0,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,     0,     0,     0,    72,    23,    68,
      42,    43,     0,     0,     0,     0,     0,    36,    38,     0,
      51,    54,    58,    63,    62,    29,     0,    27,    24,    28,
       5,     0,     0,     0,     0,     0,     0,     0,    13,    12,
       0,     0,     0,     0,    61,     0,    60,    59,    40,    30,
       0,     0,     0,     0,    47,    49,    48,    50,    45,    46,
       0,     0,     0,     0,     0,    15,    33,     0,    32,    31,
       0,    18,     0,    17,     0,    73,    69,    44,    64,    66,
       0,    37,    39,    52,    53,    41,    55,    56,    57,     0,
      20,     0,    35,    71,     0,    65,     0,    19,     0,    67,
       0,     0,    22,    21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -100,  -100,   170,  -100,  -100,  -100,  -100,    46,  -100,   -47,
    -100,  -100,  -100,  -100,  -100,    38,  -100,  -100,  -100,   -38,
      -9,   113,  -100,   -41,    -8,   -99,   119,  -100,    40,   -39,
     -34,   164,    -2,   161
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    11,    18,    13,    14,    46,
      47,    48,    49,    50,   120,   121,   139,    51,   148,    66,
      67,    68,   110,    69,    70,    71,    72,    96,   130,    58,
      73,    15,    53,    74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    77,    75,    84,    59,    78,    57,    56,    57,    16,
      59,   144,   136,   137,   138,    90,    52,    16,    31,    16,
      16,    93,   102,   103,    92,    57,   -72,    57,   102,   103,
     128,    60,    61,     1,   115,   114,   117,    62,   122,   102,
     103,    32,    63,    79,    12,   123,   124,    52,    64,    52,
       6,    52,   126,    32,   129,    65,    76,    59,    76,     7,
      32,    63,    32,    12,   125,    23,     9,    64,    28,   135,
     143,   102,   103,   141,   118,   119,    94,   102,   103,    10,
     116,    12,    24,    17,   -76,    25,    52,    26,   111,   112,
     113,   131,   132,   -76,   133,   134,    19,    21,    20,   150,
      22,    30,    34,   129,   -76,    29,   -76,    95,   -76,   -76,
     -76,    35,    52,   153,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,    37,   -76,   -76,    36,    80,
      54,    38,    39,    55,   -16,   -16,    40,    41,    81,    82,
      86,    83,    87,   -16,    42,    85,    88,   -16,    43,    44,
      89,    56,    45,    37,    99,   100,   101,    91,   140,    38,
      39,    12,   -16,   -16,    40,    41,   127,   142,   145,   146,
     118,   151,    42,   152,     8,    37,    43,    44,    98,   147,
      45,    38,    39,    97,   149,    27,    40,    41,     0,    12,
      33,     0,     0,     0,    42,     0,     0,   -16,    43,    44,
       0,    37,    45,     0,     0,     0,     0,    38,    39,     0,
       0,    12,    40,    41,     0,     0,     0,     0,     0,   -16,
      42,     0,     0,    37,    43,    44,     0,     0,    45,    38,
      39,     0,   -16,     0,    40,    41,     0,    12,     0,     0,
       0,     0,    42,     0,     0,     0,    43,    44,     0,     0,
      45,   128,     0,     0,     0,     0,     0,     0,     0,    12,
     102,   103,   104,   105,   106,   107,   108,   109,   102,   103,
     104,   105,   106,   107,   108,   109
};

static const yytype_int16 yycheck[] =
{
      34,    42,    40,    50,    38,    44,     1,    34,     1,    11,
      44,    31,   111,   112,   113,    56,    50,    19,     1,    21,
      22,    62,    42,    43,    62,     1,    53,     1,    42,    43,
      33,    26,    27,     3,    81,    76,    83,    32,    85,    42,
      43,    36,    37,    45,    37,    86,    87,    81,    43,    83,
      37,    85,    91,    36,    95,    50,    32,    91,    32,     0,
      36,    37,    36,    37,    35,    19,    29,    43,    22,   110,
      35,    42,    43,   120,    10,    11,     1,    42,    43,    14,
      82,    37,     1,    21,     9,     4,   120,     6,    39,    40,
      41,   100,   101,    18,   102,   103,    29,    31,    30,   146,
      15,    22,    16,   144,    29,    34,    31,    32,    33,    34,
      35,    35,   146,   151,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,     1,    51,    52,    35,    23,
       5,     7,     8,     5,    10,    11,    12,    13,    29,    17,
      53,    18,    34,    19,    20,    18,     4,    23,    24,    25,
       4,    34,    28,     1,     9,    52,    51,    31,    19,     7,
       8,    37,    10,    11,    12,    13,    33,    19,    33,    18,
      10,    12,    20,    19,     4,     1,    24,    25,    65,   141,
      28,     7,     8,    64,   144,    21,    12,    13,    -1,    37,
      29,    -1,    -1,    -1,    20,    -1,    -1,    23,    24,    25,
      -1,     1,    28,    -1,    -1,    -1,    -1,     7,     8,    -1,
      -1,    37,    12,    13,    -1,    -1,    -1,    -1,    -1,    19,
      20,    -1,    -1,     1,    24,    25,    -1,    -1,    28,     7,
       8,    -1,    10,    -1,    12,    13,    -1,    37,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    24,    25,    -1,    -1,
      28,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      42,    43,    44,    45,    46,    47,    48,    49,    42,    43,
      44,    45,    46,    47,    48,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    55,    56,    57,    58,    37,     0,    56,    29,
      14,    59,    37,    61,    62,    85,    86,    21,    60,    29,
      30,    31,    15,    61,     1,     4,     6,    85,    61,    34,
      22,     1,    36,    87,    16,    35,    35,     1,     7,     8,
      12,    13,    20,    24,    25,    28,    63,    64,    65,    66,
      67,    71,    84,    86,     5,     5,    34,     1,    83,    84,
      26,    27,    32,    37,    43,    50,    73,    74,    75,    77,
      78,    79,    80,    84,    87,    73,    32,    77,    83,    86,
      23,    29,    17,    18,    63,    18,    53,    34,     4,     4,
      77,    31,    73,    77,     1,    32,    81,    80,    75,     9,
      52,    51,    42,    43,    44,    45,    46,    47,    48,    49,
      76,    39,    40,    41,    77,    63,    86,    63,    10,    11,
      68,    69,    63,    77,    77,    35,    83,    33,    33,    77,
      82,    74,    74,    78,    78,    77,    79,    79,    79,    70,
      19,    63,    19,    35,    31,    33,    18,    69,    72,    82,
      63,    12,    19,    73
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    58,    59,    60,    61,
      61,    62,    62,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    78,    78,    78,    78,    79,    79,
      79,    79,    80,    80,    80,    81,    82,    82,    83,    83,
      84,    84,    84,    84,    85,    85,    86,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,    11,     2,     1,     1,     3,
       0,     3,     8,     8,     3,     3,     0,     3,     3,     5,
       4,     7,     7,     2,     2,     1,     1,     2,     2,     2,
       3,     1,     1,     0,     1,     0,     1,     3,     1,     3,
       2,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     3,     3,     1,     3,     1,     3,
       1,     4,     1,     4,     1,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 95 "mini_l.y" /* yacc.c:1646  */
    {
//		for (auto symbol : symTable) cout << symbol.name << endl;
		}
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 102 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back("endfunc");
			if (!errorFound) {
				cout << "func " << *(funcTable.begin()) << endl;

				for (auto symbol : symTable) {
					if (symbol.type == "INTEGER" || symbol.type == "BOOLEAN") 
						if (symbol.param) {
							cout << "\t. " + string(symbol.name, 1) << endl;
							cout << "\t= " + string(symbol.name, 1) + ", $0" << endl;
						}
				 		else cout << "\t. " << symbol.name << endl;
					else cout << "\t.[] " << symbol.name << ", " << symbol.size << endl;	

				}
				for (auto code : milCode) {
					cout << code << endl;
				}
			}
			currentTemp = 0;
			currentPred = 0;
			currentLabel = 0;
			symTable.clear();
                }
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 127 "mini_l.y" /* yacc.c:1646  */
    {
			funcTable.push_back(*((yyvsp[0].strVal)));
		}
#line 1496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 131 "mini_l.y" /* yacc.c:1646  */
    { addParams = true; }
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 132 "mini_l.y" /* yacc.c:1646  */
    { addParams = false; 
		}
#line 1509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 135 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 136 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 139 "mini_l.y" /* yacc.c:1646  */
    {
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					Symbol s(ident, "INTEGER");
					if (addParams) {s.param = true;
					}
					symTable.push_back(s);
				}
				else {
					errorFound = true;
					string errorString = string(ident,1) + " has already been declared\n";
					yyerror(errorString.c_str());
				}
				identStack.pop();
			}
                }
#line 1544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 157 "mini_l.y" /* yacc.c:1646  */
    {
			if ((yyvsp[-3].iVal) <= 0) yyerror("negative size for array\n");
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					symTable.push_back(Symbol(ident, "ARRAY", (yyvsp[-3].iVal)));
				}
				else {
					errorFound = true;
					string errorString = string(ident,1) + " has already been declared\n";
					yyerror(errorString.c_str());
				}
				identStack.pop();
			}
		}
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 173 "mini_l.y" /* yacc.c:1646  */
    {yyerrok;}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 174 "mini_l.y" /* yacc.c:1646  */
    {yyerrok;}
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 177 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 178 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 181 "mini_l.y" /* yacc.c:1646  */
    {
			string var = *((yyvsp[-2].attribute).name);
			string expression = *((yyvsp[0].attribute).name);
	
			Table::iterator lhs = find(symTable.begin(), symTable.end(), var);
			Table::iterator rhs= find(symTable.begin(), symTable.end(), expression);
			if ( lhs != symTable.end() ) {
				if (lhs->type == "ARRAY") {
					string index = indexStack.top();
					indexStack.pop();
					// check rhs type
					if (rhs != symTable.end()) { // rhs in table
						if (rhs->type == "INTEGER") {
							// ARRAY = INTEGER
							milCode.push_back(genQuad("[]=", var, index, expression));
						}
						else { // ARRAY = ARRAY
							string rIndex = indexStack.top();
							indexStack.pop();
							string temp = newTemp();
							milCode.push_back(genQuad("=", temp, expression, index));
							milCode.push_back(genQuad("[]=", var, index, temp));
						}
					}				
					else {// rhs not in table, must be temp or constant
						// ARRAY[] = temp
						milCode.push_back(genQuad("[]=", var, index, expression));
					}
				}
				else { // lhs is INTEGER
					// check rhs type
					if (rhs != symTable.end()) { // rhs in table
						if (rhs->type == "INTEGER") { // INTEGER = INTEGER
							milCode.push_back(genQuad("=", var, expression));
						}
						else { // int = array[]
							string index = indexStack.top();
							indexStack.pop();
							string temp = newTemp();
							milCode.push_back(genQuad("=[]", temp, expression, index));
							milCode.push_back(genQuad("=",var, temp)); 
						}
					}				
					else {// rhs not in table, must be temp or constant
						// INTEGER = temp
						milCode.push_back(genQuad("=", var, expression));
					}
				}
			}
			else {
				errorFound = true;
				cout << "assigning to constant\n";
			}
		}
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 235 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 236 "mini_l.y" /* yacc.c:1646  */
    { }
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 237 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back("\t:= " + loopStack.front());
			loopStack.pop_front();
			milCode.push_back(": " + loopStack.front());
			loopStack.pop_front();	
		}
#line 1671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 243 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back(genQuad("?:=", loopStack.front(), *((yyvsp[0].attribute).name)));
			loopStack.pop_front();
		}
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 247 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 248 "mini_l.y" /* yacc.c:1646  */
    {
			while (!rwStack.empty()) {
				string var = rwStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), var);
				if (iter != symTable.end()) {
					if (iter->type == "INTEGER") {
						milCode.push_back("\t.< " + var);
					}
					else {
						milCode.push_back("\t.[]<" + var +", " + indexStack.top() );
						indexStack.pop();
					}
				}
				rwStack.pop();
			}
		}
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 264 "mini_l.y" /* yacc.c:1646  */
    {
			while (!rwStack.empty()) {
				string var = rwStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), var);
				if (iter != symTable.end()) {
					if (iter->type == "INTEGER") {
						milCode.push_back("\t.> " + var);
					}
					else {
						milCode.push_back("\t.[]> " + var +", " + indexStack.top());
						indexStack.pop();
					}
				}
				rwStack.pop();
			}
		}
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 280 "mini_l.y" /* yacc.c:1646  */
    {
			if(!loopStack.empty()) {
				milCode.push_back("\t:= " + loopStack.front());
			}
			else {
				errorFound = true;
				 yyerror("Using continue outside of loop\n");
			}
  		}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 289 "mini_l.y" /* yacc.c:1646  */
    { yyerrok;}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 290 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back("\tret " + *((yyvsp[0].attribute).name));	
		}
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 295 "mini_l.y" /* yacc.c:1646  */
    {
			Symbol ident = Symbol(*((yyvsp[0].strVal)), "INTEGER");
		}
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 299 "mini_l.y" /* yacc.c:1646  */
    {
			string l0 = newLabel();
			string l1 = newLabel();
			string l2 = newLabel();
			milCode.push_back(": " + l0);
			milCode.push_back(genQuad("?:=", l1, *((yyvsp[0].attribute).name)));
			milCode.push_back("\t:= " + l2);
			milCode.push_back(": " + l1);
			loopStack.push_back(l0);
			loopStack.push_back(l2);
		}
#line 1780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 311 "mini_l.y" /* yacc.c:1646  */
    {
			string l0 = newLabel();
			string l1 = newLabel();
			milCode.push_back(genQuad("?:= ", l0, *((yyvsp[-1].attribute).name)));
			milCode.push_back("\t:= " + l1);
			milCode.push_back(": " + l0);
			labelStack.push_back(l1);
		}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 320 "mini_l.y" /* yacc.c:1646  */
    {
			string l2 = newLabel();
			milCode.push_back("\t:= " + l2); 
			milCode.push_back(": " + labelStack.front());
			labelStack.pop_front();
			labelStack.push_back(l2);
		}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 328 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back(": " + labelStack.front());
			labelStack.pop_front();	
		}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 332 "mini_l.y" /* yacc.c:1646  */
    {
		}
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 335 "mini_l.y" /* yacc.c:1646  */
    {
			string l0 = newLabel();
			string l1 = newLabel();
			milCode.push_back(": " + l0);
			loopStack.push_back(l1);
			loopStack.push_back(l0);	
		}
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 343 "mini_l.y" /* yacc.c:1646  */
    { /* for continue */
			milCode.push_back(": " + loopStack.front());
			loopStack.pop_front();
		}
#line 1842 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 348 "mini_l.y" /* yacc.c:1646  */
    {
			//string pred = newPred();
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
			//milCode.push_back(genQuad("=", pred, *($1.name)));
			//milCode.push_back(genQuad("==", pred, *($1.name), "0"));
		}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 354 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			(yyval.attribute).name = new string(pred);
			milCode.push_back(genQuad("||", pred, lhs, rhs));
			//string pred2 = newPred();
			//milCode.push_back(genQuad("==", pred2, pred, "0"));
		}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 365 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
		}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 368 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
			(yyval.attribute).name = new string(pred);
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			milCode.push_back(genQuad("&&", pred, lhs, rhs));
		}
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 377 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
                        (yyval.attribute).name = new string(pred);
                        milCode.push_back(genQuad("!", pred, *((yyvsp[0].attribute).name)));
		}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 382 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
                        (yyval.attribute).name = new string(pred);
                        string lhs = *((yyvsp[-2].attribute).name);
                        string rhs = *((yyvsp[0].attribute).name);
                        milCode.push_back(genQuad(*((yyvsp[-1].strVal)), pred, lhs, rhs));
		}
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 389 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
			(yyval.attribute).name = new string(pred);
			milCode.push_back(genQuad("=", pred, "1"));
		}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 394 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
			(yyval.attribute).name = new string(pred);
			milCode.push_back(genQuad("=", pred, "0"));
		}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 399 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
			(yyval.attribute).name = new string(pred);
			milCode.push_back(genQuad("=", pred, *((yyvsp[-1].attribute).name)));
		}
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 406 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("==");}
#line 1945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 407 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("<>");}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 408 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("<");}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 409 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string(">");}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 410 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("<=");}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 411 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string(">=");}
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 414 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
			(yyval.attribute).type= new string(*((yyvsp[0].attribute).type));

		}
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 419 "mini_l.y" /* yacc.c:1646  */
    {
			string temp = newTemp();
			(yyval.attribute).name = new string(temp);
			(yyval.attribute).type = new string("INTEGER");
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			milCode.push_back(genQuad("+",temp, lhs, rhs));
		}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 427 "mini_l.y" /* yacc.c:1646  */
    {
			string temp = newTemp();
			(yyval.attribute).name = new string(temp);
			(yyval.attribute).type = new string("INTEGER");
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			milCode.push_back(genQuad("-",temp, lhs, rhs));
		}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 437 "mini_l.y" /* yacc.c:1646  */
    {
					(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
					(yyval.attribute).type = new string(*((yyvsp[0].attribute).type));
				}
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 441 "mini_l.y" /* yacc.c:1646  */
    {
					string temp = newTemp();
					(yyval.attribute).name = new string(temp);
					(yyval.attribute).type = new string("INTEGER");
					string lhs = *((yyvsp[-2].attribute).name);
					string rhs = *((yyvsp[0].attribute).name);
					milCode.push_back(genQuad("*",temp, lhs, rhs));
				}
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 449 "mini_l.y" /* yacc.c:1646  */
    {
					string temp = newTemp();
					(yyval.attribute).name = new string(temp);
					(yyval.attribute).type = new string("INTEGER");
					string lhs = *((yyvsp[-2].attribute).name);
					string rhs = *((yyvsp[0].attribute).name);
					milCode.push_back(genQuad("/",temp, lhs, rhs));
				}
#line 2046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 457 "mini_l.y" /* yacc.c:1646  */
    {
					string temp = newTemp();
					(yyval.attribute).name = new string(temp);
					(yyval.attribute).type = new string("INTEGER");
					string lhs = *((yyvsp[-2].attribute).name);
					string rhs = *((yyvsp[0].attribute).name);
					milCode.push_back(genQuad("%",temp, lhs, rhs));
				}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 467 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
			(yyval.attribute).type = new string (*((yyvsp[0].attribute).type));
		}
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 472 "mini_l.y" /* yacc.c:1646  */
    {
			string name = newTemp();
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
			(yyval.attribute).type = new string(*((yyvsp[0].attribute).type));
			milCode.push_back(genQuad("-", name, "0", *((yyval.attribute).name)));
		}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 478 "mini_l.y" /* yacc.c:1646  */
    {
			string temp = *((yyvsp[-1].strVal));
			lstStr::iterator iter = find(funcTable.begin(), funcTable.end(), *((yyvsp[-1].strVal)));
			if (iter == funcTable.end()) { 
				string errorString = *((yyvsp[-1].strVal)) + " not a function\n";
				errorFound = true;
				yyerror(errorString.c_str());
			}
			else milCode.push_back(genQuad("call", *((yyvsp[-1].strVal)), newTemp()));
			(yyval.attribute).name = new string(temp);
			(yyval.attribute).type = new string("INTEGER");
		}
#line 2096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 490 "mini_l.y" /* yacc.c:1646  */
    {yyerrok;}
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 493 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(to_string((yyvsp[0].iVal)));
			(yyval.attribute).type = new string("INTEGER");
			//$$.value = $1;
		}
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 498 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));	
			(yyval.attribute).type = new string(*((yyvsp[0].attribute).type));
		}
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 502 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[-1].attribute).name));
			(yyval.attribute).type = new string(*((yyvsp[-1].attribute).type));
		}
#line 2130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 508 "mini_l.y" /* yacc.c:1646  */
    {
			while (!funcParams.empty()) {
				milCode.push_back("\tparam " + funcParams.back());
				funcParams.pop_back();
			}
		}
#line 2141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 515 "mini_l.y" /* yacc.c:1646  */
    {
			funcParams.push_back(*((yyvsp[0].attribute).name));
		 }
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 518 "mini_l.y" /* yacc.c:1646  */
    {
			funcParams.push_back(*((yyvsp[-2].attribute).name));
		}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 523 "mini_l.y" /* yacc.c:1646  */
    {
			rwStack.push(*((yyvsp[0].attribute).name));
		}
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 526 "mini_l.y" /* yacc.c:1646  */
    {
			rwStack.push(*((yyvsp[-2].attribute).name));
		}
#line 2173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 532 "mini_l.y" /* yacc.c:1646  */
    {
			string ident = *((yyvsp[0].strVal));
			(yyval.attribute).name = new string(ident);
			(yyval.attribute).type = new string("INTEGER");
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					errorFound = true;
					string errorString = string(ident,1) +" not previously declared\n";
					yyerror(errorString.c_str());
				}
				else {
					if (iter->type != "INTEGER") {
						errorFound = true;
						string errorString = string(ident,1) +" is an integer, not an array\n"; 
						yyerror(errorString.c_str());
					}
					else {
						identStack.push(ident);
						varStack.push(ident);
					}
				}
                  }
#line 2200 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 554 "mini_l.y" /* yacc.c:1646  */
    {
			string ident = *((yyvsp[-3].strVal));
			(yyval.attribute).name = new string(ident);
			(yyval.attribute).type = new string("ARRAY");
			indexStack.push(*((yyvsp[-1].attribute).name));
			string errorString = string(ident,1) +" not previously declared\n";
			Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
			if (iter == symTable.end()) {
				errorFound = true;
				 yyerror(errorString.c_str());
			}
			else {
				if (iter->type != "ARRAY") {
					 errorFound = true;
				 	 string errorString = string(ident,1) +" is an integer, not an array\n"; 
					 yyerror(errorString.c_str());
					}
				else {
					varStack.push(ident);
				}
			}
		}
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 576 "mini_l.y" /* yacc.c:1646  */
    {yyerrok;}
#line 2233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 577 "mini_l.y" /* yacc.c:1646  */
    {yyerrok;}
#line 2239 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 580 "mini_l.y" /* yacc.c:1646  */
    {}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 581 "mini_l.y" /* yacc.c:1646  */
    {}
#line 2251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 584 "mini_l.y" /* yacc.c:1646  */
    {
			 string ident = "_" + *((yyvsp[0].strVal));
			(yyval.strVal) = new string(ident);
			identStack.push(ident);
		}
#line 2261 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 590 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.iVal) = (yyvsp[0].iVal);
		}
#line 2269 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2273 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  return yyresult;
}
#line 594 "mini_l.y" /* yacc.c:1906  */


int main() {
   yyparse();

   return 0;
}

void yyerror (char const *s)
{
  fprintf (stderr, "error at line %d:  \"%s\"\n", currLine, s);
}

string newTemp() {
    string temp = "t" + to_string(currentTemp++);
    symTable.push_back(Symbol(temp, "INTEGER"));
    return temp;
}

string newLabel() {
    return "L" + to_string(currentLabel++);
}

string newPred() {
    string pred = "p" + to_string(currentPred++);
    symTable.push_back(Symbol(pred, "BOOLEAN"));
    return pred;
}


string genQuad(string op, string dest, string src1, string src2) {
    return "\t" + op + " " + dest + ", " + src1 + ", " + src2; 
}

string genQuad(string op, string dest , string src) {
    return "\t" + op + " " + dest + ", " + src;
}
	
