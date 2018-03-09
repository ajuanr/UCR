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
   Symbol():name("NONAME"),type("NOTYPE"),value(777), size(-1){} // 
   Symbol(string n):name(n) {}
   Symbol(string n, string t): name(n), type(t){}
   Symbol(string n, string t, int l):name(n), type(t),size(l) {}
   string name;
   string type;
   int value;
   int size;  // for arrays
   bool operator==(const string &rhs) { return !(this->name.compare(rhs));}
};

struct BranchLabels {
   string l1;
   string l2;
   string l3;
};

typedef list<string> lstStr;
typedef list<Symbol> Table;
typedef stack<string> stackStr;
typedef stack<BranchLabels> stackBL;
typedef queue<string> strQ;
typedef deque<string> strDq;


bool inTable(string);
bool inArrayList(string);
string genQuad(string op, string src1, string src2, string dest);
string genQuad(string op, string src, string dest);
string newLabel();
string newTemp();
string newPred();
Table symTable;
stackStr paramTable;

int currentTemp = 1; 	// the current number of temporary variables
int currentLabel = 1; 	// the current number of labels
int currentPred = 1;    // the current predicate
bool funcCall = false;	// add to paramater table for function calls


lstStr milCode;		// holds the code generated
stackStr identStack;   	// holds list of identifiers seen
lstStr varList;   	// holds list of identifiers seen
lstStr labels;		// holds the labels
strDq opDeck;		// holds the operands
stackBL ifLabels;
stackBL loopLabels;

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
			$1.size= $5;
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
			milCode.push_back(genQuad("||", *($1.name), *($3.name), newPred()));
			cout << milCode.back() << endl;
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
		| expression comp expression {
			*($$.name) = newPred();
			milCode.push_back(genQuad(*($2.name), *($1.name), *($3.name), *($$.name)));
			cout << milCode.back() << endl;

		}
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
			$$.value = $1.value - $3.value;
			milCode.push_back(genQuad("+",*($1.name), *($3.name), temp));
			cout << milCode.back() << endl;
		}
                | expression SUB multiplicative_expression {
			string temp = newTemp();
			$$.name = new string(temp);
			$$.value = $1.value - $3.value;
			milCode.push_back(genQuad("-",*($1.name), *($3.name), temp));
			cout << milCode.back() << endl;
		}
		;

multiplicative_expression:	  term {
					*($$.name) = *($1.name);
					$$.value = $1.value;
				}
				| multiplicative_expression MULT term {
					string temp = newTemp();
					$$.name = new string(temp);
					$$.value = $1.value * $3.value;
					milCode.push_back(genQuad("*",*($1.name), *($3.name), temp));
					cout << milCode.back() << endl;
				}
				| multiplicative_expression DIV term {
					string temp = newTemp();
					$$.name = new string(temp);
					$$.value = $1.value / $3.value;
					milCode.push_back(genQuad("/",*($1.name), *($3.name), temp));
					cout << milCode.back() << endl;
					
				}
				| multiplicative_expression MOD term {
					string temp = newTemp();
					$$.name = new string(temp);
					$$.value = $1.value % $3.value;
					milCode.push_back(genQuad("%",*($1.name), *($3.name), temp));
					cout << milCode.back() << endl;
				}
                		;

term:		  SUB number %prec UMINUS {
			string temp = newTemp();
			$$.name = new string(temp);
			$$.value = -$2;
			symTable.push_back(Symbol(temp, "INTEGER"));
			milCode.push_back(genQuad("-","0",to_string($2),temp));
			opDeck.pop_back();
			opDeck.push_back(temp);
			cout << milCode.back() << endl;
                  }
                | number {
			$$.name = new string(to_string($$.value));
			$$.value = $1;
			string temp = newTemp();
			symTable.push_back(Symbol(temp, "INTEGER"));
			milCode.push_back(genQuad("=", temp, to_string($1)));
                 }
		| var { 
			string tempVar = newTemp();
			symTable.push_back(Symbol(tempVar, "INTEGER"));
			string oldOp = opDeck.back();
			if (oldOp[0] == '['){
				 string tempOldOp = string(oldOp, 3,oldOp.length()-3);
				 milCode.push_back("=[] " + tempVar + ", " + tempOldOp);
			}
			else milCode.push_back("= " + tempVar + ", " + oldOp);
			cout << milCode.back() << endl;
			opDeck.pop_back();
			opDeck.push_back(tempVar);
			$$.name = $1.name;
			$$.value = $1.value;
		}
		| SUB var %prec UMINUS {
			$$.value = -$2.value;
			milCode.push_back(genQuad("-","0",to_string($2.value),newTemp()));	
			cout << milCode.back() << endl;
                  }
                | L_PAREN expression R_PAREN {
			*($$.name) = *($2.name);
			$$.value = $2.value;
			paramTable.push(opDeck.back());
			opDeck.pop_back();
		  }
                | SUB L_PAREN expression R_PAREN  %prec UMINUS {
			$$.name = new string(newTemp());
			$$.value = -$3.value;
			milCode.push_back(genQuad("-","0", *($3.name), *($$.name)));
		}
		| IDENT L_PAREN expressions R_PAREN {
			$$.name = new string(*($1));
			while (!paramTable.empty()) {
				milCode.push_back("param " + paramTable.top());
				paramTable.pop();
			}
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
		}

                ;

var:		IDENT {
			string ident = "_"+*$1;
			Table::iterator iter = find(symTable.begin(),symTable.end(), ident);
			if (iter == symTable.end()) { // not in symbol table
				cout << "ERROR: var not declared\n";
			}
			else {
				$$.value = iter->value;
				opDeck.push_back(ident);
			}
			*($$.name) = *$1;	
                  }
                | IDENT L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
			string oldOp = opDeck.back();
			opDeck.pop_back();
			string ident = "_" + *($1);
			Table::iterator iter = find(symTable.begin(),symTable.end(), ident);
			if (iter == symTable.end()) { // not in symbol table
				cout << "ERROR: var not declared\n";
			}
			else if (iter->type != "ARRAY") cout << "ERROR: NOT an array\n";
			else {
				opDeck.push_back("[] " + ident + ", " + oldOp);
			}
			
		   } 
		;

identifiers:      ident {}
                   
		| ident COMMA identifiers{}
		;

ident:		IDENT {
			string ident = "_"+*($1);	
			Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
			if (iter == symTable.end()) identStack.push(ident);
			if (funcCall) paramTable.push(ident);
			$$.name = new string(ident);
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

string genQuad(string op, string src1, string src2, string dest) {
    return op + " " + dest + ", " + src1 + ", " + src2; 
}

string genQuad(string op, string dest, string src) {
    return op + " " + dest + ", " + src; 
}

