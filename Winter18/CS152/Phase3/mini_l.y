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
DeckStr paramTable; 	// keep track of parameters
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
//			cout << "symbolTAble.size " << symTable.size() << endl;
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
				milCode.push_back(genQuad("=", string(paramTable.front(),1), "$0"));
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
				if (iter == symTable.end()) {
					if(addParams) milCode.push_back("\t. " + string(ident,1));
					symTable.push_back(Symbol(ident, "INTEGER"));
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
					symTable.push_back(Symbol(ident, "ARRAY", $5));
				}
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
							//string src = "[] " + expression +", " + rIndex;
							//milCode.push_back(genQuad("[]=", var, index, src));
							milCode.push_back(genQuad("[]=", var, index, expression));
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
                | ifCond statements M4 ENDIF {}
                | ifCond statements M3 ELSE statements M4 ENDIF { }
       		|  while BEGINLOOP statements M6 ENDLOOP{
			cout << "WHILE BEGINLOOP HAS " << loopStack.front() << endl;
			milCode.push_back("\t:= " + loopStack.front());
			loopStack.pop_front();	
		}
			
		| DO M10 BEGINLOOP statements ENDLOOP WHILE bool_exp {
			milCode.push_back(genQuad("?:=", loopStack.front(), *($7.name)));
			loopStack.pop_back();
		}
  		| FOREACH ident IN IDENT loop {}
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
		//while (!rwStack.empty()) rwStack.pop();	
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
			if(!loopStack.empty()) 
				milCode.push_back("\t:= " + loopStack.front());
			else "ERROR. USING continue outside of loop\n";
  		}	
                | RETURN expression {
			milCode.push_back("\tret " + *($2.name));	
		}
                ;

while:		WHILE bool_exp {
			string l0 = newLabel();
			cout << "WHILE GENERATED: " << l0 << endl;
			string l1 = newLabel();
			cout << "WHILE GENERATED: " << l1 << endl;
			string l2 = newLabel();
			cout << "WHILE GENERATED: " << l2 << endl;
			milCode.push_back(": " + l0);
			milCode.push_back(genQuad("?:=", l1, *($2.name)));
			milCode.push_back("\t:= " + l2);
			milCode.push_back(": " + l1);
			loopStack.push_back(l0);
			loopStack.push_back(l2);
		}

ifCond:		IF bool_exp THEN  {
			string ifTrue = newLabel();
			cout << "IFCOND GENERATED: " << ifTrue << endl;
			string ifFalse = newLabel();
			cout << "IFCOND GENERATED: " << ifFalse<< endl;
			milCode.push_back(genQuad("?:= ", ifTrue, *($2.name)));
			milCode.push_back("\t:= " + ifFalse);
			milCode.push_back(": " + ifTrue);
			labelStack.push_back(ifFalse);
			
		}

loop:		BEGINLOOP statements ENDLOOP
                ;

M3:		/*empty*/ {
			string label = newLabel();
			cout << "M3 GENERATED: " << label << endl;
			milCode.push_back("\t:= " + label);
			milCode.push_back(": " + labelStack.front());
			labelStack.pop_front();
			labelStack.push_back(label);
		}

M4:		/*empty*/ {
			milCode.push_back(": " + labelStack.back());
			labelStack.pop_front();	
		}

M6:		/*empty*/ {
			cout << "M6 HAS: " << loopStack.front() << endl;
			milCode.push_back("\t:= " + loopStack.front());
			loopStack.pop_front();
		}

M10:		/*empty*/ {
			string label = newLabel();
			cout << "DO GENERATED: " << label << endl;
			milCode.push_back(": " + label);
			//labelStack.push(label);
			loopStack.push_back(newLabel());	
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
			else milCode.push_back(genQuad("call", *($1), newTemp()));
			$$.name = new string(temp);
			$$.type = new string("INTEGER");
		}
		;

terms:		number {
			$$.name = new string(to_string($1));
			$$.name = new string(to_string($1)); // FOR TESTING DELETE LATER 
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
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
			string ident = *($1);
			$$.name = new string(ident);
			$$.type = new string("ARRAY");
			indexStack.push(*($3.name));
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
	
