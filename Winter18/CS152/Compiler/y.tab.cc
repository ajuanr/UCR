// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 7 "mini_l.y" // lalr1.cc:404

#define YY_NO_UNPUT

#include "headers.h"

extern int currLine;	
extern int currPos;
extern char *yytext;

void yyerror(char const*);
int yylex(void);


struct symbolDetails{
   symbolDetails():value(0){}
   string type;
   int value;
};

typedef struct Attributes{
   string name;
   string code;
   string type;
   int value;
}Attributes;

typedef vector<string> vecStr;
typedef map<string, symbolDetails> Table;


bool inTable(string);
bool inArrayList(string);
string genQuad(string op, string src1, string src2, string dest);
string newLabel();
string newTemp();
Table symTable;
int currentTemp=0; 	// the current number of temporary variables
int currentLabel=1; 	// the current number of labels

vecStr milCode;		// holds the code generated
vecStr identList;    	// holds list of identifiers seen
vecStr labels;		// holds the labels
bool isReading = false;

#line 81 "y.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "y.tab.hh"

// User implementation prologue.

#line 95 "y.tab.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 162 "y.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
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
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
     :yydebug_ (false),
      yycdebug_ (&std::cerr)
#endif
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
      switch (other.type_get ())
    {
      case 70: // expression
      case 71: // multiplicative_expression
      case 72: // term
      case 73: // expressions
      case 74: // vars
      case 75: // var
        value.copy< Attributes > (other.value);
        break;

      case 36: // NUMBER
      case 78: // number
        value.copy< int > (other.value);
        break;

      case 37: // IDENT
      case 76: // identifiers
      case 77: // ident
        value.copy< string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value ()
  {
    (void) v;
      switch (this->type_get ())
    {
      case 70: // expression
      case 71: // multiplicative_expression
      case 72: // term
      case 73: // expressions
      case 74: // vars
      case 75: // var
        value.copy< Attributes > (v);
        break;

      case 36: // NUMBER
      case 78: // number
        value.copy< int > (v);
        break;

      case 37: // IDENT
      case 76: // identifiers
      case 77: // ident
        value.copy< string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Attributes v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const string v)
    : Base (t)
    , value (v)
  {}


  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 70: // expression
      case 71: // multiplicative_expression
      case 72: // term
      case 73: // expressions
      case 74: // vars
      case 75: // var
        value.template destroy< Attributes > ();
        break;

      case 36: // NUMBER
      case 78: // number
        value.template destroy< int > ();
        break;

      case 37: // IDENT
      case 76: // identifiers
      case 77: // ident
        value.template destroy< string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 70: // expression
      case 71: // multiplicative_expression
      case 72: // term
      case 73: // expressions
      case 74: // vars
      case 75: // var
        value.move< Attributes > (s.value);
        break;

      case 36: // NUMBER
      case 78: // number
        value.move< int > (s.value);
        break;

      case 37: // IDENT
      case 76: // identifiers
      case 77: // ident
        value.move< string > (s.value);
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }
  // Implementation of make_symbol for each symbol type.
  parser::symbol_type
  parser::make_FUNCTION ()
  {
    return symbol_type (token::FUNCTION);
  }

  parser::symbol_type
  parser::make_INTEGER ()
  {
    return symbol_type (token::INTEGER);
  }

  parser::symbol_type
  parser::make_OF ()
  {
    return symbol_type (token::OF);
  }

  parser::symbol_type
  parser::make_ARRAY ()
  {
    return symbol_type (token::ARRAY);
  }

  parser::symbol_type
  parser::make_READ ()
  {
    return symbol_type (token::READ);
  }

  parser::symbol_type
  parser::make_IF ()
  {
    return symbol_type (token::IF);
  }

  parser::symbol_type
  parser::make_THEN ()
  {
    return symbol_type (token::THEN);
  }

  parser::symbol_type
  parser::make_ENDIF ()
  {
    return symbol_type (token::ENDIF);
  }

  parser::symbol_type
  parser::make_ELSE ()
  {
    return symbol_type (token::ELSE);
  }

  parser::symbol_type
  parser::make_WHILE ()
  {
    return symbol_type (token::WHILE);
  }

  parser::symbol_type
  parser::make_DO ()
  {
    return symbol_type (token::DO);
  }

  parser::symbol_type
  parser::make_BEGIN_PARAMS ()
  {
    return symbol_type (token::BEGIN_PARAMS);
  }

  parser::symbol_type
  parser::make_BEGIN_LOCALS ()
  {
    return symbol_type (token::BEGIN_LOCALS);
  }

  parser::symbol_type
  parser::make_BEGIN_BODY ()
  {
    return symbol_type (token::BEGIN_BODY);
  }

  parser::symbol_type
  parser::make_IN ()
  {
    return symbol_type (token::IN);
  }

  parser::symbol_type
  parser::make_BEGINLOOP ()
  {
    return symbol_type (token::BEGINLOOP);
  }

  parser::symbol_type
  parser::make_ENDLOOP ()
  {
    return symbol_type (token::ENDLOOP);
  }

  parser::symbol_type
  parser::make_RETURN ()
  {
    return symbol_type (token::RETURN);
  }

  parser::symbol_type
  parser::make_END_PARAMS ()
  {
    return symbol_type (token::END_PARAMS);
  }

  parser::symbol_type
  parser::make_END_LOCALS ()
  {
    return symbol_type (token::END_LOCALS);
  }

  parser::symbol_type
  parser::make_END_BODY ()
  {
    return symbol_type (token::END_BODY);
  }

  parser::symbol_type
  parser::make_CONTINUE ()
  {
    return symbol_type (token::CONTINUE);
  }

  parser::symbol_type
  parser::make_WRITE ()
  {
    return symbol_type (token::WRITE);
  }

  parser::symbol_type
  parser::make_TRUE ()
  {
    return symbol_type (token::TRUE);
  }

  parser::symbol_type
  parser::make_FALSE ()
  {
    return symbol_type (token::FALSE);
  }

  parser::symbol_type
  parser::make_FOREACH ()
  {
    return symbol_type (token::FOREACH);
  }

  parser::symbol_type
  parser::make_SEMICOLON ()
  {
    return symbol_type (token::SEMICOLON);
  }

  parser::symbol_type
  parser::make_COLON ()
  {
    return symbol_type (token::COLON);
  }

  parser::symbol_type
  parser::make_COMMA ()
  {
    return symbol_type (token::COMMA);
  }

  parser::symbol_type
  parser::make_L_PAREN ()
  {
    return symbol_type (token::L_PAREN);
  }

  parser::symbol_type
  parser::make_R_PAREN ()
  {
    return symbol_type (token::R_PAREN);
  }

  parser::symbol_type
  parser::make_L_SQUARE_BRACKET ()
  {
    return symbol_type (token::L_SQUARE_BRACKET);
  }

  parser::symbol_type
  parser::make_R_SQUARE_BRACKET ()
  {
    return symbol_type (token::R_SQUARE_BRACKET);
  }

  parser::symbol_type
  parser::make_NUMBER (const int& v)
  {
    return symbol_type (token::NUMBER, v);
  }

  parser::symbol_type
  parser::make_IDENT (const string& v)
  {
    return symbol_type (token::IDENT, v);
  }

  parser::symbol_type
  parser::make_UMINUS ()
  {
    return symbol_type (token::UMINUS);
  }

  parser::symbol_type
  parser::make_MULT ()
  {
    return symbol_type (token::MULT);
  }

  parser::symbol_type
  parser::make_DIV ()
  {
    return symbol_type (token::DIV);
  }

  parser::symbol_type
  parser::make_MOD ()
  {
    return symbol_type (token::MOD);
  }

  parser::symbol_type
  parser::make_ADD ()
  {
    return symbol_type (token::ADD);
  }

  parser::symbol_type
  parser::make_SUB ()
  {
    return symbol_type (token::SUB);
  }

  parser::symbol_type
  parser::make_LT ()
  {
    return symbol_type (token::LT);
  }

  parser::symbol_type
  parser::make_LTE ()
  {
    return symbol_type (token::LTE);
  }

  parser::symbol_type
  parser::make_GT ()
  {
    return symbol_type (token::GT);
  }

  parser::symbol_type
  parser::make_GTE ()
  {
    return symbol_type (token::GTE);
  }

  parser::symbol_type
  parser::make_EQ ()
  {
    return symbol_type (token::EQ);
  }

  parser::symbol_type
  parser::make_NEQ ()
  {
    return symbol_type (token::NEQ);
  }

  parser::symbol_type
  parser::make_NOT ()
  {
    return symbol_type (token::NOT);
  }

  parser::symbol_type
  parser::make_AND ()
  {
    return symbol_type (token::AND);
  }

  parser::symbol_type
  parser::make_OR ()
  {
    return symbol_type (token::OR);
  }

  parser::symbol_type
  parser::make_ASSIGN ()
  {
    return symbol_type (token::ASSIGN);
  }



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
      switch (that.type_get ())
    {
      case 70: // expression
      case 71: // multiplicative_expression
      case 72: // term
      case 73: // expressions
      case 74: // vars
      case 75: // var
        value.move< Attributes > (that.value);
        break;

      case 36: // NUMBER
      case 78: // number
        value.move< int > (that.value);
        break;

      case 37: // IDENT
      case 76: // identifiers
      case 77: // ident
        value.move< string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 70: // expression
      case 71: // multiplicative_expression
      case 72: // term
      case 73: // expressions
      case 74: // vars
      case 75: // var
        value.copy< Attributes > (that.value);
        break;

      case 36: // NUMBER
      case 78: // number
        value.copy< int > (that.value);
        break;

      case 37: // IDENT
      case 76: // identifiers
      case 77: // ident
        value.copy< string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 70: // expression
      case 71: // multiplicative_expression
      case 72: // term
      case 73: // expressions
      case 74: // vars
      case 75: // var
        yylhs.value.build< Attributes > ();
        break;

      case 36: // NUMBER
      case 78: // number
        yylhs.value.build< int > ();
        break;

      case 37: // IDENT
      case 76: // identifiers
      case 77: // ident
        yylhs.value.build< string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 5:
#line 96 "mini_l.y" // lalr1.cc:859
    {

                }
#line 1133 "y.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 104 "mini_l.y" // lalr1.cc:859
    {
//		cout << "declaration sees: " << *($1) << endl;
	        //*($1.type) = "INTEGER";	
		
                }
#line 1143 "y.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 116 "mini_l.y" // lalr1.cc:859
    {
//			string var = *($1.name);
//			string expr = *($3.name);
		}
#line 1152 "y.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 131 "mini_l.y" // lalr1.cc:859
    {isReading = true;}
#line 1158 "y.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 132 "mini_l.y" // lalr1.cc:859
    {isReading = false;}
#line 1164 "y.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 163 "mini_l.y" // lalr1.cc:859
    {
//			*($$.name) = *($1.name);
//			*($$.code) = *($1.code);
		}
#line 1173 "y.tab.cc" // lalr1.cc:859
    break;

  case 42:
#line 167 "mini_l.y" // lalr1.cc:859
    {
//			string temp = newTemp();
//			*($$.name) = temp;
//			*($$.code) = genQuad("+",*($1.name),*($3.name),temp) + "\n" + *($$.code);
		}
#line 1183 "y.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 172 "mini_l.y" // lalr1.cc:859
    {
//			string temp = newTemp();
//			*($$.name) = temp;
//			*($$.code) = genQuad("-",*($1.name),*($3.name),temp) + "\n" + *($$.code);
		}
#line 1193 "y.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 179 "mini_l.y" // lalr1.cc:859
    {
//					*($$.name) = *($1.name);
//					*($$.code) = *($1.code);	
				}
#line 1202 "y.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 183 "mini_l.y" // lalr1.cc:859
    {
//					string temp = newTemp();
//					*($$.name) = temp;
//					*($$.code) = genQuad("*",*($1.name),*($3.name),temp) + "\n" + *($$.code);
				}
#line 1212 "y.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 188 "mini_l.y" // lalr1.cc:859
    {
//					string temp = newTemp();
//					*($$.name) = temp;
//					*($$.code) = genQuad("/",*($1.name),*($3.name),temp) + "\n" + *($$.code);
				}
#line 1222 "y.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 193 "mini_l.y" // lalr1.cc:859
    {
//					string temp = newTemp();
//					*($$.name) = temp;
//					*($$.code) = genQuad("%",*($1.name),*($3.name),temp) + "\n" + *($$.code);
				}
#line 1232 "y.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 200 "mini_l.y" // lalr1.cc:859
    {
//			string temp = newTemp();
//			*($$.name) = temp;
//			$$.value = -($2);
//			*($$.code) = genQuad("-", "h",to_string($2),temp);
                  }
#line 1243 "y.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 206 "mini_l.y" // lalr1.cc:859
    {
//		    *($$.name) = to_string($1);
//		    $$.value = $1;
                 }
#line 1252 "y.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 210 "mini_l.y" // lalr1.cc:859
    {
//		     *($$.name) = *($1.name);
		}
#line 1260 "y.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 213 "mini_l.y" // lalr1.cc:859
    {
//		      string temp = newTemp();
//		      *($$.name) = *($2.name);
//		      *($$.code) = genQuad("-", "0", *($2.name), temp);
                  }
#line 1270 "y.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 218 "mini_l.y" // lalr1.cc:859
    {
//			*($$.name) = *($2.name);
//			*($$.code) = *($2.code);
		  }
#line 1279 "y.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 222 "mini_l.y" // lalr1.cc:859
    {
//			string temp = newTemp();
//			*($$.name) = temp;
//			*($$.code) = genQuad("-", "0",*($3.name),temp);
}
#line 1289 "y.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 227 "mini_l.y" // lalr1.cc:859
    {
//		 	$$.name = $3.name;
//			$$.code = $3.code;
}
#line 1298 "y.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 234 "mini_l.y" // lalr1.cc:859
    {
			
		 }
#line 1306 "y.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 240 "mini_l.y" // lalr1.cc:859
    {
//`			cout << "vars seeing: " << (*$1.code) << endl;
//		        string temp= *($1.name);
//			*($$.name) = temp;
//		 	*($$.code) = *($1.code);
//		        if (isReading) milCode.push_back(".< " + temp);
//		        else milCode.push_back(".> " + temp);
		}
#line 1319 "y.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 251 "mini_l.y" // lalr1.cc:859
    {
			yylhs.value.as< Attributes > ().name = yystack_[0].value.as< string > ();
//			$$.code = "HELLO";

/*
		    string ident = *($1);
		    Table::iterator iter = symTable.find(ident);
		    // ident not in symbol table
		    if (iter == symTable.end()) {
			cout << "Error: " << ident << " was not declared. "
			     << "Line " << currLine << ", position " << currPos << endl;
		    }
                    else {
			if (iter->second.type != "INTEGER") cout << "ERROR, invalid type (var)\n";
		        else {
				$$.value = iter->second.value;
			}
		   } 
                    *($$.name) = *($1);
*/
                  }
#line 1345 "y.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 272 "mini_l.y" // lalr1.cc:859
    {
/*
		    string ident = *($1);
		    Table::iterator iter = symTable.find(ident);
		    // ident not in symbol table
		    if (iter == symTable.end()) {
			cout << "Error: " << ident << " was not declared. "
			     << "Line " << currLine << ", position " << currPos << endl;
		    }
                    else {
			if (iter->second.type == "INTEGER") cout << "ERROR, invalid type (var)\n";
		        else $$.value = iter->second.value;
		   } 
                    *($$.name) = *($1);
		    *($$.code) = *($3.code);
*/
                }
#line 1367 "y.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 291 "mini_l.y" // lalr1.cc:859
    {
			yylhs.value.as< string > () = yystack_[0].value.as< string > ();
		}
#line 1375 "y.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 298 "mini_l.y" // lalr1.cc:859
    {
			yylhs.value.as< string > () = "\t. " + yystack_[0].value.as< string > ();
/*
                    Table::iterator ident = symTable.find(*($1));
		    // new symbol
		    if (ident == symTable.end()) identList.push_back(*($1));
		    else {
		        cout << "Error at line " << currLine << ", pos " << currPos
			     << ": redeclaration of " << *($1);
		    }
		    $$ = $1;
*/
                }
#line 1393 "y.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 312 "mini_l.y" // lalr1.cc:859
    {
		    yylhs.value.as< int > () = yystack_[0].value.as< int > ();
		}
#line 1401 "y.tab.cc" // lalr1.cc:859
    break;


#line 1405 "y.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -64;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
       3,    -4,    41,   -64,     3,   -64,    17,   -64,   -64,    34,
      -4,    30,    27,    35,    46,    55,    -4,     8,    -4,    -4,
     -64,   -64,    61,   -64,    75,    63,    84,   -64,    69,    66,
      96,   -64,   -16,   -16,    87,    18,   -64,   -64,    -4,    98,
      78,    70,    88,   120,    -4,   -64,   -64,   -16,    39,   -16,
      12,   116,    74,    76,    71,    42,   -15,   -64,     6,   -64,
      87,    66,   117,    18,   -64,    -4,   111,   -64,    66,    18,
      18,   -64,   -64,    99,   100,    65,    18,   -64,   -64,   -64,
     -64,    66,    66,   -16,   -16,   -64,   -64,   -64,   -64,   -64,
     -64,    18,    18,    18,    18,    18,    18,    18,   -64,   112,
     -16,   101,   -64,    -4,   -64,   -64,    97,    -4,   -64,   -64,
     102,   126,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   106,   105,   -64,   -64,    87,   -64,   -64,   -64,   -64,
      18,   -64,   -64,   -64
  };

  const unsigned char
  parser::yydefact_[] =
  {
       4,     0,     0,     2,     4,    63,     0,     1,     3,     0,
       7,     0,     0,     0,    61,     0,     7,     0,     0,     7,
       6,     8,     0,    62,     0,     0,     0,    64,     0,    11,
       0,    22,     0,     0,     0,     0,    20,    23,     0,     0,
       0,     0,    59,     0,     0,    32,    33,     0,     0,     0,
       0,     0,    26,    28,     0,    41,    44,    50,    59,    49,
       0,    11,     0,     0,    21,     0,     0,     5,    11,     0,
       0,     9,    18,    57,     0,     0,     0,    51,    48,    30,
      13,    11,    11,     0,     0,    37,    39,    38,    40,    35,
      36,     0,     0,     0,     0,     0,     0,     0,    15,     0,
       0,     0,    19,     0,    10,    12,     0,     0,    34,    52,
       0,     0,    24,    27,    29,    31,    42,    43,    45,    46,
      47,    55,     0,    25,    16,     0,    60,    58,    53,    14,
       0,    54,    17,    56
  };

  const short int
  parser::yypgoto_[] =
  {
     -64,   -64,   135,   -64,   -12,   -64,   -29,   -64,   -64,   -64,
     -64,   -57,   -28,     9,    91,   -64,   -34,   -64,    -7,    11,
     -63,     1,   124,    -1,   -17
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,    11,    12,    39,    40,    44,    65,
      50,    62,    51,    52,    53,    91,    54,    55,    56,   122,
      72,    57,    13,    58,    59
  };

  const unsigned char
  parser::yytable_[] =
  {
       6,    64,   102,    98,    20,    60,     1,    24,    28,    14,
      45,    46,    21,    75,    22,    14,    47,    14,    14,    74,
      27,     5,    80,    81,    94,    95,    96,    48,    42,   101,
      41,    78,    99,     5,    49,   105,   106,    66,    97,   104,
      70,     7,   110,    42,   127,    73,     9,    42,    10,    77,
      63,    15,   111,   112,    27,     5,    16,   115,   116,   117,
      42,    48,    41,   121,    42,    17,    73,    42,   132,    41,
      19,    76,   124,    31,    32,    27,     5,    18,    33,    34,
      42,    42,    41,    41,    92,    93,    35,   118,   119,   120,
      36,    37,   113,   114,    38,    25,   121,    26,   109,    27,
      29,    43,   125,     5,    30,    61,    42,    68,    73,    85,
      86,    87,    88,    89,    90,    85,    86,    87,    88,    89,
      90,    67,    70,    69,    71,    82,    83,    84,   103,   100,
     107,   123,   126,   108,   109,   128,   129,   130,   131,     8,
      79,   133,    23
  };

  const unsigned char
  parser::yycheck_[] =
  {
       1,    35,    65,    60,    16,    33,     3,    19,    25,    10,
      26,    27,     4,    47,     6,    16,    32,    18,    19,    47,
      36,    37,    10,    11,    39,    40,    41,    43,    29,    63,
      29,    48,    61,    37,    50,    69,    70,    38,    32,    68,
      34,     0,    76,    44,   107,    44,    29,    48,    14,    48,
      32,    21,    81,    82,    36,    37,    29,    91,    92,    93,
      61,    43,    61,    97,    65,    30,    65,    68,   125,    68,
      15,    32,   100,     7,     8,    36,    37,    31,    12,    13,
      81,    82,    81,    82,    42,    43,    20,    94,    95,    96,
      24,    25,    83,    84,    28,    34,   130,    22,    33,    36,
      16,     5,   103,    37,    35,    18,   107,    29,   107,    44,
      45,    46,    47,    48,    49,    44,    45,    46,    47,    48,
      49,    23,    34,    53,     4,     9,    52,    51,    17,    12,
      31,    19,    35,    33,    33,    33,    10,    31,    33,     4,
      49,   130,    18
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,    55,    56,    57,    37,    77,     0,    56,    29,
      14,    58,    59,    76,    77,    21,    29,    30,    31,    15,
      58,     4,     6,    76,    58,    34,    22,    36,    78,    16,
      35,     7,     8,    12,    13,    20,    24,    25,    28,    60,
      61,    75,    77,     5,    62,    26,    27,    32,    43,    50,
      64,    66,    67,    68,    70,    71,    72,    75,    77,    78,
      66,    18,    65,    32,    70,    63,    77,    23,    29,    53,
      34,     4,    74,    75,    66,    70,    32,    75,    78,    68,
      10,    11,     9,    52,    51,    44,    45,    46,    47,    48,
      49,    69,    42,    43,    39,    40,    41,    32,    65,    60,
      12,    70,    74,    17,    60,    70,    70,    31,    33,    33,
      70,    60,    60,    67,    67,    70,    70,    70,    72,    72,
      72,    70,    73,    19,    66,    77,    35,    74,    33,    10,
      31,    33,    65,    73
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    54,    55,    56,    56,    57,    58,    58,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    63,    64,    65,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    69,    69,    69,    69,    69,
      69,    70,    70,    70,    71,    71,    71,    71,    72,    72,
      72,    72,    72,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    78
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,    12,     3,     0,     3,     8,
       3,     0,     3,     3,     5,     3,     4,     5,     3,     3,
       1,     2,     0,     0,     3,     3,     1,     3,     1,     3,
       2,     3,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1,     3,     3,     3,     2,     1,
       1,     2,     3,     4,     4,     1,     3,     1,     3,     1,
       4,     1,     3,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "FUNCTION", "INTEGER", "OF", "ARRAY",
  "READ", "IF", "THEN", "ENDIF", "ELSE", "WHILE", "DO", "BEGIN_PARAMS",
  "BEGIN_LOCALS", "BEGIN_BODY", "IN", "BEGINLOOP", "ENDLOOP", "RETURN",
  "END_PARAMS", "END_LOCALS", "END_BODY", "CONTINUE", "WRITE", "TRUE",
  "FALSE", "FOREACH", "SEMICOLON", "COLON", "COMMA", "L_PAREN", "R_PAREN",
  "L_SQUARE_BRACKET", "R_SQUARE_BRACKET", "NUMBER", "IDENT", "UMINUS",
  "MULT", "DIV", "MOD", "ADD", "SUB", "LT", "LTE", "GT", "GTE", "EQ",
  "NEQ", "NOT", "AND", "OR", "ASSIGN", "$accept", "prog_start",
  "functions", "function", "declarations", "declaration", "statements",
  "statement", "M1", "M2", "ifCond", "loop", "bool_exp",
  "relation_and_exp", "relation_exp", "comp", "expression",
  "multiplicative_expression", "term", "expressions", "vars", "var",
  "identifiers", "ident", "number", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  parser::yyrline_[] =
  {
       0,    91,    91,    93,    94,    96,   100,   101,   104,   109,
     112,   113,   116,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   131,   132,   134,   137,   140,   141,   144,   145,
     148,   149,   150,   151,   152,   155,   156,   157,   158,   159,
     160,   163,   167,   172,   179,   183,   188,   193,   200,   206,
     210,   213,   218,   222,   227,   233,   237,   240,   248,   251,
     272,   291,   295,   298,   312
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
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
    const unsigned int user_token_number_max_ = 308;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1914 "y.tab.cc" // lalr1.cc:1167
#line 317 "mini_l.y" // lalr1.cc:1168


int main() {
   yyparse();

   return 0;
}

void yyerror (char const *s)
{
  fprintf (stderr, "error at line %d:  \"%s\"\n", currLine, s);
}

string newTemp() {
    return "__temp__" + to_string(currentTemp++);
}

string newLabel() {
    return "__label__" + to_string(currentLabel++);
}

string genQuad(string op, string src1, string src2, string dest) {
    return ". " + op + " " + dest + ", " + src1 + ", " + src2; 
}
