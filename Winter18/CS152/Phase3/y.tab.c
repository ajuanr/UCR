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
   Symbol():value("NO VALUE"){}
   Symbol(string n):name(n) {}
   Symbol(string n, string t): name(n), type(t){}
   Symbol(string n, string t, int l):name(n), type(t),size(l) {}
   string name;
   string type;
   int size;  // for arrays
   string value;
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
DeckStr paramTable; 	// keep track of parameters
DeckStr funcParams;		// keep track of parameters in functions
stackStr indexStack;
lstStr funcTable;	// keep track of functions;
stackStr varStack;	// keep track of vars
stackStr labelStack;	// keep track of labels
stackStr loopStack;	// keep track of which loop you're in
stackStr rwStack;
int currentTemp = 0; 	// the current number of temporary variables
int currentLabel = 0; 	// the current number of labels
int currentPred = 0;    // the current predicate
bool addParams = false;

lstStr milCode;		// holds the code generated
stackStr identStack;   	// holds list of identifiers seen


#line 121 "y.tab.c" /* yacc.c:339  */

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
#line 58 "mini_l.y" /* yacc.c:355  */

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

#line 228 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 245 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

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
       0,    96,    96,   100,   101,   103,   110,   115,   116,   117,
     124,   126,   129,   141,   155,   156,   159,   207,   208,   209,
     215,   222,   225,   242,   259,   264,   269,   275,   278,   286,
     291,   298,   307,   314,   320,   323,   333,   336,   345,   350,
     357,   360,   363,   369,   370,   371,   372,   373,   374,   377,
     383,   392,   403,   408,   417,   425,   435,   441,   449,   460,
     466,   472,   480,   487,   490,   497,   500,   506,   522,   541,
     542,   545,   552
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
  "functions", "function", "funcName", "M", "M1", "M2", "declarations",
  "declaration", "statements", "statement", "ifCond", "loop", "M3", "M4",
  "M6", "M7", "M10", "M11", "bool_exp", "relation_and_exp", "relation_exp",
  "comp", "expression", "multiplicative_expression", "term", "terms",
  "parenExpression", "expressions", "vars", "var", "identifiers", "ident",
  "number", YY_NULLPTR
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

#define YYPACT_NINF -51

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-51)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       4,   -24,    28,   -51,     4,    33,   -51,   -51,   -51,   -51,
      41,    38,   -51,    44,    48,    51,    55,   -51,    38,    54,
      38,    73,   -51,   -51,    74,   -51,    38,    75,   -51,   -51,
      77,    87,   105,    97,   110,    39,   -51,    38,    -5,   -51,
     -51,   -17,   -51,    38,    38,    92,    88,    39,    63,    84,
     -51,    89,   -51,   -51,    -5,    90,   -26,    -5,   112,    67,
      72,    58,     9,   -51,   -51,   -51,   -51,    -5,   106,   -17,
      31,   -51,   108,   -51,    39,   116,   -17,   -17,    38,    94,
      50,   -17,   -51,   -51,   -51,   -51,    -5,    -5,   -17,   -17,
     -51,   -51,   -51,   -51,   -51,   -51,   -17,   -17,   -17,   -17,
     111,    39,    11,    91,   -51,   119,   121,    31,    26,   -51,
     -51,   -51,    -8,    99,   -51,   -51,     9,     9,    31,   -51,
     -51,   -51,    39,   -51,   114,   111,    39,   -51,   -51,   -17,
     -51,   115,   -51,   -51,   -51,   -51,   -51,   -51,   123,   126,
      -5,   -51,   -51
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     2,     4,     0,     6,     1,     3,     8,
       0,    11,    71,     0,     0,     0,    69,     9,    11,     0,
       0,     0,    10,    12,     0,    70,    11,     0,     7,    72,
       0,     0,     0,     0,     0,    15,    13,     0,     0,    30,
      32,     0,    24,     0,     0,     0,     0,    15,     0,    67,
      22,    65,    40,    41,     0,    71,     0,     0,     0,    34,
      36,     0,    49,    52,    56,    60,    59,     0,     0,     0,
      25,    23,     0,     5,    15,    28,     0,     0,     0,     0,
       0,     0,    58,    57,    38,    26,     0,     0,     0,     0,
      45,    47,    46,    48,    43,    44,     0,     0,     0,     0,
       0,    15,     0,     0,    14,     0,     0,    16,     0,    66,
      42,    61,    63,     0,    35,    37,    50,    51,    39,    53,
      54,    55,    15,    31,     0,     0,    15,    17,    68,     0,
      62,     0,    19,    33,    21,    29,    64,    27,     0,     0,
       0,    18,    20
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -51,   -51,   133,   -51,   -51,   -51,   -51,   -51,     7,   -51,
     -44,   -51,   -51,    13,   -51,     5,   -51,   -51,   -51,   -51,
     -50,    -7,    82,   -51,   -40,    -4,   -27,    85,   -51,    14,
     -38,   -35,   122,    -2,   117
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    31,    10,    21,    13,    14,
      45,    46,    47,   123,   105,   106,    67,   132,    68,   138,
      58,    59,    60,    96,    61,    62,    63,    64,    82,   113,
      50,    65,    15,    49,    66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    70,    51,    75,    79,    71,    69,     1,    51,    16,
      29,    12,    48,     6,    80,    69,    16,   100,    16,    29,
      55,    52,    53,   129,    16,    22,    56,    54,     7,   102,
     104,    29,    55,    28,    88,    89,   107,   108,    56,    48,
     109,   112,    72,    51,   111,    57,    37,    38,    97,    98,
      99,    39,    40,    88,    89,    11,   118,   124,    23,    41,
      24,   128,     9,    42,    43,    17,    48,    44,    88,    89,
     119,   120,   121,    88,    89,    12,    12,    18,   131,   114,
     115,    19,   135,   111,   116,   117,    20,    48,    26,   112,
     142,    48,    88,    89,    90,    91,    92,    93,    94,    95,
      88,    89,    90,    91,    92,    93,    94,    95,    27,    33,
      34,    29,    32,    35,    36,    73,    76,    74,    77,    86,
      78,    85,    81,    87,   101,   103,   -29,   110,   125,   122,
     126,   127,   130,   133,   137,   140,   141,     8,   134,    84,
     139,    83,    25,   136,    30
};

static const yytype_uint8 yycheck[] =
{
      35,    41,    37,    47,    54,    43,    32,     3,    43,    11,
      36,    37,    47,    37,    54,    32,    18,    67,    20,    36,
      37,    26,    27,    31,    26,    18,    43,    32,     0,    69,
      74,    36,    37,    26,    42,    43,    76,    77,    43,    74,
      78,    81,    44,    78,    33,    50,     7,     8,    39,    40,
      41,    12,    13,    42,    43,    14,    96,   101,     4,    20,
       6,    35,    29,    24,    25,    21,   101,    28,    42,    43,
      97,    98,    99,    42,    43,    37,    37,    29,   122,    86,
      87,    30,   126,    33,    88,    89,    31,   122,    15,   129,
     140,   126,    42,    43,    44,    45,    46,    47,    48,    49,
      42,    43,    44,    45,    46,    47,    48,    49,    34,    22,
       5,    36,    35,    16,     4,    23,    53,    29,    34,    52,
      31,     9,    32,    51,    18,    17,    10,    33,    37,    18,
      11,    10,    33,    19,    19,    12,    10,     4,   125,    57,
     135,    56,    20,   129,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    55,    56,    57,    58,    37,     0,    56,    29,
      60,    14,    37,    62,    63,    86,    87,    21,    29,    30,
      31,    61,    62,     4,     6,    86,    15,    34,    62,    36,
      88,    59,    35,    22,     5,    16,     4,     7,     8,    12,
      13,    20,    24,    25,    28,    64,    65,    66,    85,    87,
      84,    85,    26,    27,    32,    37,    43,    50,    74,    75,
      76,    78,    79,    80,    81,    85,    88,    70,    72,    32,
      78,    84,    87,    23,    29,    64,    53,    34,    31,    74,
      78,    32,    82,    81,    76,     9,    52,    51,    42,    43,
      44,    45,    46,    47,    48,    49,    77,    39,    40,    41,
      74,    18,    78,    17,    64,    68,    69,    78,    78,    84,
      33,    33,    78,    83,    75,    75,    79,    79,    78,    80,
      80,    80,    18,    67,    64,    37,    11,    10,    35,    31,
      33,    64,    71,    19,    67,    64,    83,    19,    73,    69,
      12,    10,    74
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    58,    59,    60,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    74,    75,    75,    76,    76,
      76,    76,    76,    77,    77,    77,    77,    77,    77,    78,
      78,    78,    79,    79,    79,    79,    80,    80,    80,    81,
      81,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,    14,     2,     0,     0,     0,
       3,     0,     3,     8,     3,     0,     3,     4,     7,     5,
       8,     5,     2,     2,     1,     2,     3,     3,     0,     0,
       0,     0,     0,     0,     1,     3,     1,     3,     2,     3,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     1,
       1,     3,     3,     1,     3,     1,     3,     1,     4,     1,
       3,     1,     1
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
#line 96 "mini_l.y" /* yacc.c:1646  */
    {
//		for (auto symbol : symTable) cout << symbol.name << endl;
		}
#line 1431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 103 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back("endfunc");
			for (auto code : milCode) {
		//		cout << code << endl;
			}
                }
#line 1442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 110 "mini_l.y" /* yacc.c:1646  */
    {
			funcTable.push_back(*((yyvsp[0].strVal)));
			milCode.push_back("func " + *((yyvsp[0].strVal)));
		}
#line 1451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 115 "mini_l.y" /* yacc.c:1646  */
    { milCode.push_back(": " + string("START"));}
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 116 "mini_l.y" /* yacc.c:1646  */
    { addParams = true; }
#line 1463 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 117 "mini_l.y" /* yacc.c:1646  */
    { addParams = false; 
			while (!paramTable.empty()) {
				milCode.push_back(genQuad("=", string(paramTable.front(),1), "$0"));
				paramTable.pop_front();
			}
		}
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 129 "mini_l.y" /* yacc.c:1646  */
    {
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					if(addParams) milCode.push_back("\t. " + string(ident,1));
					else milCode.push_back("\t. " + ident);
					symTable.push_back(Symbol(ident, "INTEGER"));
				}
				identStack.pop();
			}
                }
#line 1491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 141 "mini_l.y" /* yacc.c:1646  */
    {
			if ((yyvsp[-3].iVal) < 0) cout << "ERROR: negative size\n";
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					milCode.push_back(genQuad(".[]", ident, to_string((yyvsp[-3].iVal))));
					symTable.push_back(Symbol(ident, "ARRAY", (yyvsp[-3].iVal)));
				}
				identStack.pop();
			}
		}
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 155 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "mini_l.y" /* yacc.c:1646  */
    {}
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 159 "mini_l.y" /* yacc.c:1646  */
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
							string src = "[]" + expression +", " + rIndex;
							milCode.push_back(genQuad("[]=", var, index, src));
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
							milCode.push_back(genQuad("=[]", var, expression, index));
						}
					}				
					else {// rhs not in table, must be temp or constant
						// INTEGER = temp
						milCode.push_back(genQuad("=", var, expression));
					}
				}
			}
			else cout << "ERROR: assigninging to constant\n";
		}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 209 "mini_l.y" /* yacc.c:1646  */
    {
			string label = newLabel();
			labelStack.push(label);
			milCode.push_back(genQuad("?:=", labelStack.top(), *((yyvsp[-2].attribute).name)));
		}
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 215 "mini_l.y" /* yacc.c:1646  */
    {
			string label =  labelStack.top();
			labelStack.pop();
			milCode.push_back(genQuad("==", newPred(), *((yyvsp[0].attribute).name), "0"));
			milCode.push_back(genQuad("?:=", label, newPred()));
			
		}
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 222 "mini_l.y" /* yacc.c:1646  */
    {
			cout << "ident is: " << *((yyvsp[-3].strVal)) << " " << *((yyvsp[-1].strVal)) << endl;
		}
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 225 "mini_l.y" /* yacc.c:1646  */
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
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 242 "mini_l.y" /* yacc.c:1646  */
    {
		//while (!rwStack.empty()) rwStack.pop();	
			while (!rwStack.empty()) {
				string var = rwStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), var);
				if (iter != symTable.end()) {
					if (iter->type == "INTEGER") {
						milCode.push_back("\t.>" + var);
					}
					else {
						milCode.push_back("\t.[]>" + var +", " + indexStack.top());
						indexStack.pop();
					}
				}
				rwStack.pop();
			}
		}
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 259 "mini_l.y" /* yacc.c:1646  */
    {
			if(!loopStack.empty()) 
				milCode.push_back("\t:= " + loopStack.top());
			else "ERROR. USING continue outside of loop\n";
  		}
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 264 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back("\tret " + *((yyvsp[0].attribute).name));	
		}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 269 "mini_l.y" /* yacc.c:1646  */
    {
			string label = newLabel();
			milCode.push_back(genQuad("?:=", label, *((yyvsp[-1].attribute).name)));
			labelStack.push(label);
		}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 278 "mini_l.y" /* yacc.c:1646  */
    {
			string label = newLabel();
			milCode.push_back("\t:= " + label);
			milCode.push_back(": " + labelStack.top());
			labelStack.pop();				
			labelStack.push(label);
		}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 286 "mini_l.y" /* yacc.c:1646  */
    {
			milCode.push_back(": " + labelStack.top());
			labelStack.pop();	
		}
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 291 "mini_l.y" /* yacc.c:1646  */
    {
			string label = newLabel();
			labelStack.push(label);
			loopStack.push(label);
			milCode.push_back(": " + label);
		}
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 298 "mini_l.y" /* yacc.c:1646  */
    {
			string l1 = labelStack.top(); labelStack.pop();	
			string l2 = labelStack.top(); labelStack.pop();	
			milCode.push_back("\t:= " + l1);
			milCode.push_back("\t:= " + l2);
			loopStack.pop();

		}
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 307 "mini_l.y" /* yacc.c:1646  */
    {
			string label = newLabel();
			milCode.push_back(": " + label);
			labelStack.push(label);
			loopStack.push(newLabel());	
		}
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 314 "mini_l.y" /* yacc.c:1646  */
    {
			string label = loopStack.top();
			milCode.push_back(": " + label);
			loopStack.pop();
		}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 320 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
		}
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 323 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
			(yyval.attribute).name = new string(pred);
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			milCode.push_back(genQuad("||", pred, lhs, rhs));
		}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 333 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
		}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 336 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
			(yyval.attribute).name = new string(pred);
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			milCode.push_back(genQuad("&&", pred, lhs, rhs));
		}
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 345 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
                        (yyval.attribute).name = new string(pred);
                        milCode.push_back(genQuad("!", pred, *((yyvsp[0].attribute).name)));
		}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 350 "mini_l.y" /* yacc.c:1646  */
    {
			string pred = newPred();
                        (yyval.attribute).name = new string(pred);
                        string lhs = *((yyvsp[-2].attribute).name);
                        string rhs = *((yyvsp[0].attribute).name);
                        milCode.push_back(genQuad(*((yyvsp[-1].strVal)), pred, lhs, rhs));
		}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 357 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string("true");
		}
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 360 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string("false");
		}
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 363 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = (yyvsp[-1].attribute).name;
			(yyval.attribute).type = (yyvsp[-1].attribute).type;
		}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 369 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("==");}
#line 1834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 370 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("<>");}
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 371 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("<");}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 372 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string(">");}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 373 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string("<=");}
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 374 "mini_l.y" /* yacc.c:1646  */
    { (yyval.strVal) = new string(">=");}
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 377 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
			(yyval.attribute).type= new string(*((yyvsp[0].attribute).type));
			//$$.value = $1.value;

		}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 383 "mini_l.y" /* yacc.c:1646  */
    {
			string temp = newTemp();
			(yyval.attribute).name = new string(temp);
			(yyval.attribute).type = new string("INTEGER");
			//$$.value = $1.value + $3.value;
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			milCode.push_back(genQuad("+",temp, lhs, rhs));
		}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 392 "mini_l.y" /* yacc.c:1646  */
    {
			string temp = newTemp();
			(yyval.attribute).name = new string(temp);
			(yyval.attribute).type = new string("INTEGER");
			//$$.value = $1.value - $3.value;
			string lhs = *((yyvsp[-2].attribute).name);
			string rhs = *((yyvsp[0].attribute).name);
			milCode.push_back(genQuad("-",temp, lhs, rhs));
		}
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 403 "mini_l.y" /* yacc.c:1646  */
    {
					(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
					(yyval.attribute).type = new string(*((yyvsp[0].attribute).type));
					//$$.value = $1.value;
				}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 408 "mini_l.y" /* yacc.c:1646  */
    {
					string temp = newTemp();
					(yyval.attribute).name = new string(temp);
					(yyval.attribute).type = new string("INTEGER");
					//$$.value = $1.value * $3.value;
					string lhs = *((yyvsp[-2].attribute).name);
					string rhs = *((yyvsp[0].attribute).name);
					milCode.push_back(genQuad("*",temp, lhs, rhs));
				}
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 417 "mini_l.y" /* yacc.c:1646  */
    {
					string temp = newTemp();
					(yyval.attribute).name = new string(temp);
					(yyval.attribute).type = new string("INTEGER");
					string lhs = *((yyvsp[-2].attribute).name);
					string rhs = *((yyvsp[0].attribute).name);
					milCode.push_back(genQuad("/",temp, lhs, rhs));
				}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 425 "mini_l.y" /* yacc.c:1646  */
    {
					string temp = newTemp();
					(yyval.attribute).name = new string(temp);
					(yyval.attribute).type = new string("INTEGER");
					string lhs = *((yyvsp[-2].attribute).name);
					string rhs = *((yyvsp[0].attribute).name);
					milCode.push_back(genQuad("%",temp, lhs, rhs));
				}
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 435 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
			(yyval.attribute).type = new string (*((yyvsp[0].attribute).type));
			//$$.value = $1.value;
		}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 441 "mini_l.y" /* yacc.c:1646  */
    {
			string name = newTemp();
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));
			(yyval.attribute).type = new string(*((yyvsp[0].attribute).type));
			//*($$.type) = *($2.type);
			//$$.value = -($2.value);
			milCode.push_back(genQuad("-", name, "0", *((yyval.attribute).name)));
		}
#line 1976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 449 "mini_l.y" /* yacc.c:1646  */
    {
					// "FIX THIS LATER"
			string temp = *((yyvsp[-1].strVal));
			lstStr::iterator iter = find(funcTable.begin(), funcTable.end(), *((yyvsp[-1].strVal)));
			if (iter == funcTable.end()) cout << "ERROR: " + *((yyvsp[-1].strVal)) + " not a function\n";
			else milCode.push_back(genQuad("call", *((yyvsp[-1].strVal)), newTemp()));
			(yyval.attribute).name = new string(temp);
			(yyval.attribute).type = new string("TEMP TYPE");
		}
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 460 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(to_string((yyvsp[0].iVal)));
			(yyval.attribute).name = new string(to_string((yyvsp[0].iVal))); // FOR TESTING DELETE LATER 
			(yyval.attribute).type = new string("INTEGER");
			//$$.value = $1;
		}
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 466 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.attribute).name = new string(*((yyvsp[0].attribute).name));	
			(yyval.attribute).type = new string(*((yyvsp[0].attribute).type));
			//$$.value = $1.value; // fix this for array assignment stuff
		// NEED TO CHECK ARRAY STUFF	
		}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 472 "mini_l.y" /* yacc.c:1646  */
    {
			// TEMPORARY
			(yyval.attribute).name = new string(*((yyvsp[-1].attribute).name));
			(yyval.attribute).type = new string(*((yyvsp[-1].attribute).type));
			//$$.value = 909;
		}
#line 2023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 480 "mini_l.y" /* yacc.c:1646  */
    {
			while (!funcParams.empty()) {
				milCode.push_back("\tparam " + funcParams.back());
				funcParams.pop_back();
			}
		}
#line 2034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 487 "mini_l.y" /* yacc.c:1646  */
    {
			funcParams.push_back(*((yyvsp[0].attribute).name));
		 }
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 490 "mini_l.y" /* yacc.c:1646  */
    {
			funcParams.push_back(*((yyvsp[-2].attribute).name));

		}
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 497 "mini_l.y" /* yacc.c:1646  */
    {
			rwStack.push(*((yyvsp[0].attribute).name));
		}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 500 "mini_l.y" /* yacc.c:1646  */
    {
			rwStack.push(*((yyvsp[-2].attribute).name));
		}
#line 2067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 506 "mini_l.y" /* yacc.c:1646  */
    {
			string ident = *((yyvsp[0].strVal));
			(yyval.attribute).name = new string(ident);
			(yyval.attribute).type = new string("INTEGER");
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) cout << "ERROR: var " +ident +" not found\n";
				else {
					if (iter->type != "INTEGER") cout << "ERROR: var not an int\n";
					else {
						identStack.push(ident);
						//$$.value = iter->value;
						varStack.push(ident);
					}
				}
			
                  }
#line 2088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 522 "mini_l.y" /* yacc.c:1646  */
    {
			string ident = *((yyvsp[-3].strVal));
			(yyval.attribute).name = new string(ident);
			(yyval.attribute).type = new string("ARRAY");
			indexStack.push(*((yyvsp[-1].attribute).name));
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) cout << "ERROR: var not found\n";
				else {
					if (iter->type != "ARRAY") cout << "ERROR: var not an array\n";
					else {
						//$$.value = iter->value;
						varStack.push(ident);
					}
				}
	
		}
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 541 "mini_l.y" /* yacc.c:1646  */
    {}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 542 "mini_l.y" /* yacc.c:1646  */
    {}
#line 2121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 545 "mini_l.y" /* yacc.c:1646  */
    {
			 string ident = "_" + *((yyvsp[0].strVal));
			(yyval.strVal) = new string(ident);
			identStack.push(ident);
			if (addParams) paramTable.push_back(ident);
		}
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 552 "mini_l.y" /* yacc.c:1646  */
    {
			(yyval.iVal) = (yyvsp[0].iVal);
		}
#line 2140 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2144 "y.tab.c" /* yacc.c:1646  */
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
#line 556 "mini_l.y" /* yacc.c:1906  */


int main() {
   yyparse();

   return 0;
}

void yyerror (char const *s)
{
  fprintf (stderr, "error at line %d:  \"%s\"\n", currLine, s);
}

string newTemp() {
    return "t" + to_string(currentTemp++);
}

string newLabel() {
    return "L" + to_string(currentLabel++);
}

string newPred() {
    return "p" + to_string(currentPred++);
}


string genQuad(string op, string dest, string src1, string src2) {
    return "\t" + op + " " + dest + ", " + src1 + ", " + src2; 
}

string genQuad(string op, string dest , string src) {
    return "\t" + op + " " + dest + ", " + src;
}
	
