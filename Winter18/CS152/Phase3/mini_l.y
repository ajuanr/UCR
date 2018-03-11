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
DeckStr paramTable;
lstStr funcTable;
stackStr varStack;
stackStr labelStack;
int currentTemp = 1; 	// the current number of temporary variables
int currentLabel = 1; 	// the current number of labels
int currentPred = 1;    // the current predicate
bool addParams = false;

lstStr milCode;		// holds the code generated
stackStr identStack;   	// holds list of identifiers seen
bool isReading = false;

%}
%union{
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
%type<strVal> ident comp
%type<attribute> identifiers var vars statement statements term terms expression multiplicative_expression expressions
%type<attribute> bool_exp relation_exp relation_and_exp 


%%
prog_start:	functions {
//		for (auto symbol : symTable) cout << symbol.name << endl;
		}
                ;
functions:	function functions
                | /*empty*/
                ;
function: 	funcName SEMICOLON M1 BEGIN_PARAMS declarations END_PARAMS M2 BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY M {

                }

funcName:	FUNCTION IDENT {
			funcTable.push_back(*($2));
			milCode.push_back("func " + *($2));
		}

M:		/*empty*/ { // print out everything
			milCode.push_back("endfunc");
			for (auto code : milCode) {
				cout << code << endl;
			}
		}

M1:		/*empty*/ { addParams = true; }
M2:		/*empty*/ { addParams = false; }
                ;
declarations:	declaration SEMICOLON declarations

                | /*empty*/
                ;

declaration:    identifiers COLON INTEGER {
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					symTable.push_back(Symbol(ident, "INTEGER"));
					milCode.push_back("\t. " + ident);
					if (addParams) {
						milCode.pop_back();  // param not declaration
						milCode.push_back("\t. " + string(ident,1));
						paramTable.push_back(ident);
						milCode.push_back(genQuad("\t=", string(ident,1), "$0"));
					}
				}
				identStack.pop();
			}
                }
		| identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER {
			if ($5 < 0) cout << "ERROR: negative size\n";
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					milCode.push_back(genQuad("\t.[]", ident, to_string($5)));
					symTable.push_back(Symbol(ident, "ARRAY", $5));
					if (addParams) paramTable.push_back(ident);
				}
				identStack.pop();
			}
		}
                ;

statements:       statement SEMICOLON statements
                | /*empty*/
                ;

statement:        var ASSIGN expression {
			//TEMP CODE//////////
			
			string var = *($1.name);
			Table::iterator iter = find(symTable.begin(), symTable.end(), var);
			if (iter != symTable.end()) {
				iter->value = *($3.name);
				milCode.push_back(genQuad("=", var, *($3.name)));
			}
			else cout << "ERROR: var not in table, cannot assign\n";
		}
                | ifCond statements ENDIF
                | ifCond statements ELSE statements ENDIF
       		| WHILE bool_exp loop
		| DO loop WHILE bool_exp
  		| FOREACH ident IN IDENT loop {
			cout << "ident is: " << *($2) << " " << *($4) << endl;
		}
		| READ M8 vars {
			while (!varStack.empty()) {
				string var = varStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), var);
				if (iter != symTable.end()) {
					if (iter->type == "INTEGER") {
						milCode.push_back(".<" + var);
					}
					else {
						milCode.push_back(".[]<" + var +", INDEX");
					}
					
				}
				varStack.pop();
			}
		}
                | WRITE M9 vars {
//			cout << "stack size: " << varStack.size() << endl;
			while (!varStack.empty()) {
				string var = varStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), var);
				if (iter != symTable.end()) {
					if (iter->type == "INTEGER") {
						//cout << ".>" + var << endl;
						milCode.push_back(".>" + var);
					}
					else {
						//cout << ".[]>" + var +", INDEX" << endl;
						milCode.push_back(".[]>" + var +", INDEX");
					}
					
				}
				varStack.pop();
			}
		}
                | CONTINUE
                | RETURN expression
                ;

M8:		/*empty*/ {isReading = true;}
M9:		/*empty*/ {isReading = false;}

ifCond:		IF bool_exp THEN M3 {
			milCode.push_back(genQuad("?:=", labelStack.top(), *($2.name)));
			cout << milCode.back();
			labelStack.pop();
		}

loop:		BEGINLOOP statements ENDLOOP
                ;

M3:		/*empty*/ {
			string label = newLabel();
			labelStack.push(label);
			milCode.push_back(": " + label);
			cout << milCode.back() << endl;
		}

bool_exp:	  relation_and_exp {
			$$.name = new string(*($1.name));
		}
                | relation_and_exp OR relation_and_exp {
			string pred = newPred();
			$$.name = new string(pred);
			string lhs = *($1.name);
			string rhs = *($3.name);
			milCode.push_back(genQuad("||", pred, lhs, rhs));
		}
		
		; 

relation_and_exp: relation_exp {
			$$.name = new string(*($1.name));
		}
                | relation_exp AND relation_and_exp {
			string pred = newPred();
			$$.name = new string(pred);
			string lhs = *($1.name);
			string rhs = *($3.name);
			milCode.push_back(genQuad("&&", pred, lhs, rhs));
		}
                ;

relation_exp:	  NOT relation_exp {
			string pred = newPred();
                        $$.name = new string(pred);
                        milCode.push_back(genQuad("!", pred, *($2.name)));
		}
		| expression comp expression {
			string pred = newPred();
                        $$.name = new string(pred);
                        string lhs = *($1.name);
                        string rhs = *($3.name);
                        milCode.push_back(genQuad(*($2), pred, lhs, rhs));
		}
                | TRUE {
			$$.name = new string("true");
		}
                | FALSE {
			$$.name = new string("false");
		}
                | L_PAREN bool_exp R_PAREN {
			$$.name = $2.name;
			$$.type = $2.type;
		} 
                ;

comp:	   	  EQ  { $$ = new string("==");}
		| NEQ { $$ = new string("<>");}
		| LT  { $$ = new string("<");}
		| GT  { $$ = new string(">");}
		| LTE { $$ = new string("<=");}
		| GTE { $$ = new string(">=");}
                ;

expression:	  multiplicative_expression {
			$$.name = new string(*($1.name));
			$$.type= new string(*($1.type));
			//$$.value = $1.value;

		}
                | expression ADD multiplicative_expression {
			string temp = newTemp();
			$$.name = new string(temp);
			$$.type = new string("INTEGER");
			//$$.value = $1.value + $3.value;
			string lhs = *($1.name);
			string rhs = *($3.name);
			milCode.push_back(genQuad("+",temp, lhs, rhs));
		}
                | expression SUB multiplicative_expression {
			string temp = newTemp();
			$$.name = new string(temp);
			$$.type = new string("INTEGER");
			//$$.value = $1.value - $3.value;
			string lhs = *($1.name);
			string rhs = *($3.name);
			milCode.push_back(genQuad("-",temp, lhs, rhs));
		}
		;

multiplicative_expression:	term {
					$$.name = new string(*($1.name));
					$$.type = new string(*($1.type));
					//$$.value = $1.value;
				}
				|multiplicative_expression MULT term {
					string temp = newTemp();
					$$.name = new string(temp);
					$$.type = new string("INTEGER");
					//$$.value = $1.value * $3.value;
					string lhs = *($1.name);
					string rhs = *($3.name);
					milCode.push_back(genQuad("*",temp, lhs, rhs));
				}
				|multiplicative_expression DIV term {
					string temp = newTemp();
					$$.name = new string(temp);
					$$.type = new string("INTEGER");
					string lhs = *($1.name);
					string rhs = *($3.name);
					milCode.push_back(genQuad("/",temp, lhs, rhs));
				}
				|multiplicative_expression MOD term {
					string temp = newTemp();
					$$.name = new string(temp);
					$$.type = new string("INTEGER");
					string lhs = *($1.name);
					string rhs = *($3.name);
					milCode.push_back(genQuad("%",temp, lhs, rhs));
				}
                		;

term:		terms {
			$$.name = new string(*($1.name));
			$$.type = new string (*($1.type));
			//$$.value = $1.value;
		}
		|	
		SUB terms %prec UMINUS {
			string name = newTemp();
			$$.name = new string(*($2.name));
			$$.type = new string(*($2.type));
			//*($$.type) = *($2.type);
			//$$.value = -($2.value);
			milCode.push_back(genQuad("-", name, "0", *($$.name)));
		}	
		| IDENT parenExpression  {
					// "FIX THIS LATER"
			string temp = *($1);
			lstStr::iterator iter = find(funcTable.begin(), funcTable.end(), *($1));
			if (iter == funcTable.end()) cout << "ERROR: " + *($1) + " not a function\n";
			else milCode.push_back(genQuad("call", *($1), temp));
			$$.name = new string(temp);
			$$.type = new string("TEMP TYPE");
		}
		;

terms:		number {
			$$.name = new string(to_string($1));
			$$.name = new string("NUMBER " +to_string($1)); // FOR TESTING DELETE LATER 
			$$.type = new string("INTEGER");
			//$$.value = $1;
		}		 
		| var {
			$$.name = new string(*($1.name));	
			$$.type = new string(*($1.type));
			//$$.value = $1.value; // fix this for array assignment stuff
		// NEED TO CHECK ARRAY STUFF	
		}
		| L_PAREN expression R_PAREN {
			// TEMPORARY
			$$.name = new string(*($2.name));
			$$.type = new string(*($2.type));
			//$$.value = 909;
		} 
		; 
		  
parenExpression: L_PAREN expressions R_PAREN {
			while (!paramTable.empty()) {
				milCode.push_back("param " + paramTable.back());
				paramTable.pop_back();
			}
		}

expressions:	  expression {
//			paramTable.push_back(*($1.name));
		 }
		| expression COMMA expressions {
//			paramTable.push_back(*($1.name));

		}
			
		;

vars:		  var {}
                | var COMMA vars {}
                ;

var:		ident {
			string ident = *($1);
			$$.name = new string(ident);
			$$.type = new string("INTEGER");
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) cout << "ERROR: var " +ident +" not found\n";
				else {
					if (iter->type != "INTEGER") cout << "ERROR: var not an int\n";
					else {
						identStack.push(ident);
						//$$.value = iter->value;
					}
				}
			varStack.push(ident);
			
                  }
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
			string ident = *($1);
			$$.name = new string(ident);
			$$.type = new string("ARRAY");
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) cout << "ERROR: var not found\n";
				else {
					if (iter->type != "ARRAY") cout << "ERROR: var not an array\n";
					else {
						//$$.value = iter->value;
					}
				}
			varStack.push(ident);
	
		}
			
		;

identifiers:      ident {}
		| ident COMMA identifiers{}
		;

ident:		IDENT {
			 string ident = "_" + *($1);
			$$ = new string(ident);
			identStack.push(ident); // for declarations
		}
		
number:		NUMBER {
			$$ = $1;
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


string genQuad(string op, string dest, string src1, string src2) {
    return op + " " + dest + ", " + src1 + ", " + src2; 
}

string genQuad(string op, string dest , string src) {
    return op + " " + dest + ", " + src;
}
	
