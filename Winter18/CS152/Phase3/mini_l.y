/* Juan's Grammar for CS152 */
/* mini_l.y */

%{
#define YY_NO_UNPUT

#include "headers.h"

extern int currLine;	
extern int currPos;
extern char *yytext;

void yyerror(char const*);
int yylex(void);

/*
struct symbolDetails{
   symbolDetails():value(0){}
   string type;
   int value;
};
*/

struct Symbol{
   Symbol():value(777){}
   Symbol(string n):name(n) {}
   Symbol(string n, string t): name(n), type(t){}
   Symbol(string n, int v):name(n), value(v), type("INTEGER") {}
   string name;
   string type;
   int limit;  // for arrays
   int value;
   bool operator==(const string &rhs) { return !(this->name.compare(rhs));}
};

typedef list<string> lstStr;
//typedef map<string, symbolDetails> Table;
typedef list<Symbol> Table;
typedef stack<string> stackStr;


bool inTable(string);
bool inArrayList(string);
string genQuad(string op, string src1, string src2, string dest);
string newLabel();
string newTemp();
string newPred();
Table symTable;
int currentTemp = 1; 	// the current number of temporary variables
int currentLabel = 1; 	// the current number of labels
int currentPred = 1;    // the current predicate

lstStr milCode;		// holds the code generated
stackStr identStack;   	// holds list of identifiers seen
lstStr labels;		// holds the labels
bool isReading = false;

%}
%union{
   int		iVal;
   string* 	strVal;
typedef struct Attributes{
   string* name;
   string* code;
   string* type;
   int limit; // for arrays
   int value;
}Attributes;
   Attributes attribute;
};


%error-verbose
%token		FUNCTION INTEGER OF ARRAY READ IF THEN ENDIF ELSE WHILE DO 
%token		BEGIN_PARAMS BEGIN_LOCALS BEGIN_BODY IN BEGINLOOP ENDLOOP RETURN
%token		END_PARAMS END_LOCALS END_BODY CONTINUE WRITE TRUE FALSE FOREACH 
%token 		SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET 
%token <iVal> 	NUMBER
%token <strVal>	IDENT

%right		UMINUS
%left		MULT DIV MOD
%left   	ADD SUB 
%left		LT LTE GT GTE EQ NEQ
%right		NOT 
%left		AND
%left		OR
%right  	ASSIGN

%type<iVal> number
%type<strVal> term expression multiplicative_expression expressions
%type<attribute> ident identifiers comp var vars statement statements
%type<attribute> bool_exp relation_exp relation_and_exp 


%%
prog_start:	functions {
//		for (auto symbol : symTable) cout << symbol.name << endl;
		}
                ;
functions:	function functions
                | /*empty*/
                ;
function: 	FUNCTION ident SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY {

                }
                ;
declarations:	declaration SEMICOLON declarations

                | /*empty*/
                ;

declaration:    identifiers COLON INTEGER {
			$1.type = new string("INTEGER");
			cout << "declaration -> identifiers COLON INTEGER\n";
                }
		| identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER {
/*
			$1.type = new string("ARRAY");
			$1.limit = $5;
			cout << "declaration -> identifiers COLON ARRAY\n";
*/
		}
                ;

statements:       statement SEMICOLON statements
                | /*empty*/
                ;

statement:        var ASSIGN expression {
		}
                | IF ifCond ENDIF
                | IF ifCond ELSE statements ENDIF
       		| WHILE bool_exp loop
		| DO loop WHILE bool_exp
  		| FOREACH ident IN ident loop
		| READ M1 vars
                | WRITE M2 vars
                | CONTINUE
                | RETURN expression
                ;

M1:		/*empty*/ {isReading = true;}
M2:		/*empty*/ {isReading = false;}

ifCond:		bool_exp THEN statements
                ;

loop:		BEGINLOOP statements ENDLOOP
                ;

bool_exp:	  relation_and_exp {
		}
                | relation_and_exp OR relation_and_exp {
		}
		
		; 

relation_and_exp: relation_exp {
		}
                | relation_exp AND relation_and_exp {
		}
                ;

relation_exp:	  NOT relation_exp {
			*($$.name) = "TESTING2\n";	

		}
		| expression comp expression
                | TRUE { *($$.name) = "true";}
                | FALSE { *($$.name) = "false";}
                | L_PAREN bool_exp R_PAREN { *($$.name) = *($2.name);}
                ;

comp:	   	  EQ  { $$.name = new string("==");}
		| NEQ { $$.name = new string("<>");}
		| LT  { $$.name = new string("<");}
		| GT  { $$.name = new string(">");}
		| LTE { $$.name = new string("<=");}
		| GTE { $$.name = new string(">=");}
                ;

expression:	  multiplicative_expression {
		}
                | expression ADD multiplicative_expression {
		}
                | expression SUB multiplicative_expression {
		}
		;

multiplicative_expression:	  term {
				}
				| term MULT term {
				}
				| term DIV term {
				}
				| term MOD term {
				}
                		;

term:		  SUB number %prec UMINUS {
                  }
                | number {
                 }
		| var { 
		}
		| SUB var %prec UMINUS {
                  }
                | L_PAREN expression R_PAREN {
		  }
                | SUB L_PAREN expression R_PAREN  %prec UMINUS {
		}
		| ident L_PAREN expressions R_PAREN {
		}
		;

expressions:	  expression {
		 }
		| expression COMMA expressions {
		}
			
		;

vars:		  var {
		}
                | var COMMA vars {
//			cout << "vars -> " << *($1.name) << " COMMA " << *($3.name) << endl;
		}
                ;

var:		ident{
                  }
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
		   } 
		;

identifiers:      ident {
/*
			*($1.type) = *($$.type);
			cout << *($1.name) + " TYPE IS: " << *($$.type) << endl;
*/
		}
                   
		| ident COMMA identifiers{ 
/*
			$1.type = new string(*($$.type));
			$3.type = new string(*($$.type));
			cout << "identifiers -> ident\n";
			cout << *($1.name) + " TYPE IS: " << *($$.type) << endl;
*/
                }
		;

ident:		IDENT {
			string ident = "_"+*($1);	
			Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
			if (iter == symTable.end()) identStack.push(ident);
		        cout << "ident -> " + ident << endl;	
			$$.name = new string(ident);
                }
		
number:		NUMBER {
			$$ = $1;
			cout << "number -> " << $$ << endl;	
		}
                ;
%%

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

string genQuad(string op, string src1, string src2, string dest) {
    return op + " " + dest + ", " + src1 + ", " + src2; 
}
