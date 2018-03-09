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

struct Symbol{
   Symbol():value(777){}
   Symbol(string n):name(n) {}
   Symbol(string n, string t): name(n), type(t){}
   Symbol(string n, string t, int l):name(n), type(t),limit(l) {}
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
lstStr varList;   	// holds list of identifiers seen
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
%type<attribute> term expression multiplicative_expression expressions
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
function: 	FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY {

                }
                ;
declarations:	declaration SEMICOLON declarations

                | /*empty*/
                ;

declaration:    identifiers COLON INTEGER {
			$1.type = new string("INTEGER");
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					symTable.push_back(Symbol(ident, "INTEGER"));
				}
				identStack.pop();
			}
                }
		| identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER {
			$1.type = new string("ARRAY");
			$1.limit = $5;
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					symTable.push_back(Symbol(ident, "ARRAY", $5));
				}
				identStack.pop();
			}
		}
                ;

statements:       statement SEMICOLON statements
                | /*empty*/
                ;

statement:        var ASSIGN expression {
			cout << "ASSSIGNMEING " << $3.value << endl;
			string var = *($1.name);
			Table::iterator iter = find(symTable.begin(), symTable.end(), var);
			if (iter != symTable.end()) {
				iter->value = $3.value;
			}
			milCode.push_back("= " + var + " " + to_string($3.value));
			cout << milCode.back() << endl;
		}
                | IF ifCond ENDIF
                | IF ifCond ELSE statements ENDIF
       		| WHILE bool_exp loop
		| DO loop WHILE bool_exp
  		| FOREACH IDENT IN IDENT loop
		| READ vars {
		        for (auto var: varList)	{
				milCode.push_back(".< " + var);
				cout << milCode.back() << endl;
			}
			
		}
                | WRITE vars {
		        for (auto var: varList)	{
				milCode.push_back(".< " + var);
				cout << milCode.back() << endl;
			}

		}
                | CONTINUE
                | RETURN expression
                ;

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
			*($$.name) = *($1.name);
			$$.value = $1.value;
		}
                | expression ADD multiplicative_expression {
			string temp = newTemp();
			$$.name = new string(temp);
			cout << "ADD " << *($$.name) << endl;
			$$.value = $1.value - $3.value;
			milCode.push_back(genQuad("+",*($1.name), *($3.name), temp));
			cout << milCode.back() << endl;
		}
                | expression SUB multiplicative_expression {
			string temp = newTemp();
			$$.name = new string(temp);
			cout << "SUB " << *($$.name) << endl;
			$$.value = $1.value - $3.value;
			milCode.push_back(genQuad("-",*($1.name), *($3.name), temp));
			cout << milCode.back() << endl;
		}
		;

multiplicative_expression:	  term {
					cout << "term: " << *($$.name) << endl;
					*($$.name) = *($1.name);
					$$.value = $1.value;
				}
				| multiplicative_expression MULT term {
					string temp = newTemp();
					$$.name = new string(temp);
					cout << "MULT " << *($$.name) << endl;
					$$.value = $1.value * $3.value;
					milCode.push_back(genQuad("*",*($1.name), *($3.name), temp));
					cout << milCode.back() << endl;
				}
				| multiplicative_expression DIV term {
					string temp = newTemp();
					$$.name = new string(temp);
					cout << "DIV" << *($$.name) << endl;
					$$.value = $1.value / $3.value;
					milCode.push_back(genQuad("/",*($1.name), *($3.name), temp));
					cout << milCode.back() << endl;
					
				}
				| multiplicative_expression MOD term {
					string temp = newTemp();
					$$.name = new string(temp);
					cout << "MOD" << *($$.name) << endl;
					$$.value = $1.value % $3.value;
					milCode.push_back(genQuad("%",*($1.name), *($3.name), temp));
					cout << milCode.back() << endl;
				}
                		;

term:		  SUB number %prec UMINUS {
			$$.name = new string(newTemp());
			$$.value = -$2;
			milCode.push_back(genQuad("-","0",to_string($2),*($$.name)));
			cout << milCode.back() << endl;
                  }
                | number {
			$$.name = new string(to_string($$.value));
			$$.value = $1;
                 }
		| var { 
			$$.name = $1.name;
			$$.value = $1.value;
		}
		| SUB var %prec UMINUS {
			$$.value = -$2.value;
			milCode.push_back(genQuad("-","0",to_string($2.value),newTemp()));	
			cout << milCode.back() << endl;
                  }
                | L_PAREN expression R_PAREN {
			$$.value = 777;
		  }
                | SUB L_PAREN expression R_PAREN  %prec UMINUS {
			$$.value = -777;
		}
		| IDENT L_PAREN expressions R_PAREN {
			$$.value = 888;
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
			string ident = *($1.name);
			Table::iterator iter = find(symTable.begin(),symTable.end(), ident);
			if (iter == symTable.end()) {
				cout << "ERROR: var not declared\n";
			}
			else {
				$$.value = iter->value;
			}
			*($$.name) = *($1.name);	
			if (find(varList.begin(), varList.end(), ident) == varList.end())
				varList.push_back(ident);			
                  }
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
			$$.name = new string("TESTING");
		   } 
		;

identifiers:      ident {
		}
                   
		| ident COMMA identifiers{ 
                }
		;

ident:		IDENT {
			string ident = "_"+*($1);	
			Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
			if (iter == symTable.end()) identStack.push(ident);
			else cout << "ident error: Redaclaration\n";
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
