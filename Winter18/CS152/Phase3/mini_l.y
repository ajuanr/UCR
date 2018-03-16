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
   Symbol():value(0){}
   Symbol(string n):name(n) {}
   Symbol(string n, string t): name(n), type(t){}
   Symbol(string n, string t, int l):name(n), type(t),size(l) {}
   string name;
   string type;
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
DeckStr paramTable; 	// keep track of parameters
DeckStr funcParams;		// keep track of parameters in functions
stackStr indexStack;
lstStr funcTable;	// keep track of functions;
stackStr varStack;	// keep track of vars
DeckStr labelStack;	// keep track of labels
DeckStr loopStack;	// keep track of which loop you're in
DeckStr foreachStack;	
stackStr rwStack;
int currentTemp = 0; 	// the current number of temporary variables
int currentLabel = 0; 	// the current number of labels
int currentPred = 0;    // the current predicate
int foreachCount=0;
bool addParams = false;

lstStr milCode;		// holds the code generated
stackStr identStack;   	// holds list of identifiers seen

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
function: 	funcName SEMICOLON M1 BEGIN_PARAMS declarations END_PARAMS M2 BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY {
			milCode.push_back("endfunc");
			for (auto symbol : symTable) {
				if (symbol.type == "INTEGER" || symbol.type == "BOOLEAN")
				 	cout << "\t. " << symbol.name << endl;
				else cout << "\t.[] " << symbol.name << ", " << symbol.size << endl;	

			}
			for (auto code : milCode) {
				cout << code << endl;
			}
                }

funcName:	FUNCTION IDENT {
			funcTable.push_back(*($2));
			cout << "func " << *($2) << endl;
			//milCode.push_back("func " + *($2));
		}

M1:		/*empty*/ { addParams = true; }
M2:		/*empty*/ { addParams = false; 
			while (!paramTable.empty()) {
				cout << "\t. " +string(paramTable.front(), 1) << endl;
				cout << genQuad("=", string(paramTable.front(),1), "$0") << endl;
				//milCode.push_back(genQuad("=", string(paramTable.front(),1), "$0"));
				paramTable.pop_front();
			}
		}
                ;
declarations:	declaration SEMICOLON declarations {}
                | /*empty*/ {}
                ;

declaration:    identifiers COLON INTEGER {
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				string errorString = string(ident,1) + " has already been declared\n";
				if (iter == symTable.end()) {
//					if(addParams) milCode.push_back("\t. " + string(ident,1));
					symTable.push_back(Symbol(ident, "INTEGER"));
				}
				else yyerror(errorString.c_str());
				identStack.pop();
			}
                }
		| identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER {
			if ($5 <= 0) yyerror("negative size for array\n");
			while (!identStack.empty()) {
				string ident = identStack.top();
				string errorString = string(ident,1) + " has already been declared\n";
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					symTable.push_back(Symbol(ident, "ARRAY", $5));
				}
				else yyerror(errorString.c_str());
				identStack.pop();
			}
		}
                ;

statements:       statement SEMICOLON statements {}
                | /*empty*/ {}
                ;

statement:        var ASSIGN expression {
			string var = *($1.name);
			string expression = *($3.name);
	
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
			else cout << "assigning to constant\n";
		}
                | ifCond statements endif {}
                | ifCond statements else statements endif{ }
       		|  M9 while BEGINLOOP statements ENDLOOP{
			milCode.push_back("\t:= " + loopStack.front());
			loopStack.pop_front();
			milCode.push_back(": " + loopStack.front());
			loopStack.pop_front();	
		}
			
		| do BEGINLOOP statements ENDLOOP M8 WHILE bool_exp {
			milCode.push_back(genQuad("?:=", loopStack.front(), *($7.name)));
			loopStack.pop_front();
		}
  		| foreach IN ident M5 BEGINLOOP statements ENDLOOP{}
		| READ vars {
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
                | WRITE vars {
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
                | CONTINUE  {
			if(!loopStack.empty()) {
				milCode.push_back("\t:= " + loopStack.front());
			}
			else yyerror("Using continue outside of loop\n");
  		}	
                | RETURN expression {
			milCode.push_back("\tret " + *($2.name));	
		}
                ;

foreach:	FOREACH ident {
			Symbol ident = Symbol(*($2), "INTEGER");
			symTable.push_back(ident);
		}

M9:		{	
			string l0 = newLabel();
			milCode.push_back(": " + l0);
			loopStack.push_back(l0);
		}

while:		WHILE bool_exp {
			string l1 = newLabel();
			string l2 = newLabel();
			milCode.push_back(genQuad("?:=", l1, *($2.name)));
			milCode.push_back("\t:= " + l2);
			milCode.push_back(": " + l1);
			loopStack.push_back(l2);
		}

ifCond:		IF bool_exp THEN  {
			string l0 = newLabel();
			string l1 = newLabel();
			milCode.push_back(genQuad("?:= ", l0, *($2.name)));
			milCode.push_back("\t:= " + l1);
			milCode.push_back(": " + l0);
			labelStack.push_back(l1);
		}

else:		ELSE {
			milCode.push_back(": " + labelStack.front());
			string l2 = newLabel();
			labelStack.pop_front();
			labelStack.push_back(l2);
		}

endif:		ENDIF {
			milCode.push_back(": " + labelStack.front());
			labelStack.pop_front();	
		}
M5:		/*empty*/ {
		}

do:		DO {
			string l0 = newLabel();
			string l1 = newLabel();
			milCode.push_back(": " + l0);
			loopStack.push_back(l1);
			loopStack.push_back(l0);	
		}

M8:		/*empty*/{ /* for continue */
			milCode.push_back(": " + loopStack.front());
			loopStack.pop_front();
		}

bool_exp:	  relation_and_exp {
			string pred = newPred();
			$$.name = new string(pred);
			milCode.push_back(genQuad("==", pred, *($1.name), "0"));
		}
                | relation_and_exp OR relation_and_exp {
			string pred = newPred();
			string lhs = *($1.name);
			string rhs = *($3.name);
			milCode.push_back(genQuad("||", pred, lhs, rhs));
			string pred2 = newPred();
			milCode.push_back(genQuad("==", pred2, pred, "0"));
			$$.name = new string(pred2);
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
			string pred = newPred();
			$$.name = new string(pred);
			milCode.push_back(genQuad("=", pred, "1"));
		}
                | FALSE {
			string pred = newPred();
			$$.name = new string(pred);
			milCode.push_back(genQuad("=", pred, "0"));
		}
                | L_PAREN bool_exp R_PAREN {
			string pred = newPred();
			$$.name = new string(pred);
			milCode.push_back(genQuad("=", pred, *($2.name)));
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

		}
                | expression ADD multiplicative_expression {
			string temp = newTemp();
			$$.name = new string(temp);
			$$.type = new string("INTEGER");
			string lhs = *($1.name);
			string rhs = *($3.name);
			milCode.push_back(genQuad("+",temp, lhs, rhs));
		}
                | expression SUB multiplicative_expression {
			string temp = newTemp();
			$$.name = new string(temp);
			$$.type = new string("INTEGER");
			string lhs = *($1.name);
			string rhs = *($3.name);
			milCode.push_back(genQuad("-",temp, lhs, rhs));
		}
		;

multiplicative_expression:	term {
					$$.name = new string(*($1.name));
					$$.type = new string(*($1.type));
				}
				|multiplicative_expression MULT term {
					string temp = newTemp();
					$$.name = new string(temp);
					$$.type = new string("INTEGER");
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
		}
		|	
		SUB terms %prec UMINUS {
			string name = newTemp();
			$$.name = new string(*($2.name));
			$$.type = new string(*($2.type));
			milCode.push_back(genQuad("-", name, "0", *($$.name)));
		}	
		| IDENT parenExpression  {
			string temp = *($1);
			lstStr::iterator iter = find(funcTable.begin(), funcTable.end(), *($1));
			string errorString = *($1) + " not a function\n";
			if (iter == funcTable.end()) yyerror(errorString.c_str());
			else milCode.push_back(genQuad("call", *($1), newTemp()));
			$$.name = new string(temp);
			$$.type = new string("INTEGER");
		}
		;

terms:		number {
			$$.name = new string(to_string($1));
			$$.type = new string("INTEGER");
			//$$.value = $1;
		}		 
		| var {
			$$.name = new string(*($1.name));	
			$$.type = new string(*($1.type));
		}
		| L_PAREN expression R_PAREN {
			$$.name = new string(*($2.name));
			$$.type = new string(*($2.type));
		} 
		; 
		  
parenExpression: L_PAREN expressions R_PAREN {
			while (!funcParams.empty()) {
				milCode.push_back("\tparam " + funcParams.back());
				funcParams.pop_back();
			}
		}

expressions:	  expression {
			funcParams.push_back(*($1.name));
		 }
		| expression COMMA expressions {
			funcParams.push_back(*($1.name));
		}
		;

vars:		  var {
			rwStack.push(*($1.name));
		}
                | var COMMA vars {
			rwStack.push(*($1.name));
		}

                ;

var:		ident {
			string ident = *($1);
			$$.name = new string(ident);
			$$.type = new string("INTEGER");
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				string errorString = string(ident,1) +" not previously declared\n";
				if (iter == symTable.end()) {
					yyerror(errorString.c_str());
				}
				else {
					if (iter->type != "INTEGER") yyerror(errorString.c_str());
					else {
						identStack.push(ident);
						varStack.push(ident);
					}
				}
                  }
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
			string ident = *($1);
			$$.name = new string(ident);
			$$.type = new string("ARRAY");
			indexStack.push(*($3.name));
			string errorString = string(ident,1) +" not previously declared\n";
			Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
			if (iter == symTable.end()) yyerror(errorString.c_str());
			else {
				if (iter->type != "ARRAY") yyerror(errorString.c_str());
				else {
					varStack.push(ident);
				}
			}
		}
			
		;

identifiers:      ident {}
		| ident COMMA identifiers{}
		;

ident:		IDENT {
			 string ident = "_" + *($1);
			$$ = new string(ident);
			identStack.push(ident);
			if (addParams) paramTable.push_back(ident);
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
	
