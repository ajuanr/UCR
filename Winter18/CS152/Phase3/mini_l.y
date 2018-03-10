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
   Symbol(string n, string t, int l):name(n), type(t),size(l) {}
   string name;
   string type;
   int size;  // for arrays
   int value;
   bool operator==(const string &rhs) { return !(this->name.compare(rhs));}
};

typedef list<string> lstStr;
//typedef map<string, symbolDetails> Table;
typedef list<Symbol> Table;
typedef stack<string> stackStr;
typedef deque<string> DeckStr;


bool inTable(string);
bool inArrayList(string);
string genQuad(string op, string dest, string srcl, string src2);
string genQuad(string op, string dest , string src2);
string newLabel();
string newTemp();
string newPred();
Table symTable;
DeckStr paramTable;
lstStr funcTable;
DeckStr opList;
stackStr varStack;
int currentTemp = 1; 	// the current number of temporary variables
int currentLabel = 1; 	// the current number of labels
int currentPred = 1;    // the current predicate
bool addParams = false;

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
%type<strVal> ident 
%type<attribute> identifiers comp var vars statement statements term terms expression multiplicative_expression expressions
%type<attribute> bool_exp relation_exp relation_and_exp 


%%
prog_start:	functions {
//		for (auto symbol : symTable) cout << symbol.name << endl;
		}
                ;
functions:	function functions
                | /*empty*/
                ;
function: 	funcName SEMICOLON BEGIN_PARAMS M1 declarations END_PARAMS M2 BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY M {

                }

funcName:	FUNCTION IDENT {
			milCode.push_back("func " + *($2));
			cout << milCode.back() << endl;
			
		}

M:		/*empty*/ {
			milCode.push_back("endfunc");
			cout << milCode.back() << endl;
		}

M1:		/*empty*/ {addParams = true;}
M2:		/*empty*/ {addParams = false;}


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
					cout << milCode.back() << endl;
					if (addParams) paramTable.push_back(ident);
					
				}
				identStack.pop();
			}
                }
		| identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER {
			while (!identStack.empty()) {
				string ident = identStack.top();
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) {
					milCode.push_back("\t.[] " + ident + to_string($5));
					cout << milCode.back() << endl;
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
			cout << "VAR IS: " << *($1.name) << endl;
			//TEMP CODE//////////
			string var = *($1.name);
			Table::iterator iter = find(symTable.begin(), symTable.end(), var);
			if (iter != symTable.end()) iter->value = 7654321;
			else cout << "ERROR: var not in table, cannot assign\n";
		}
                | IF ifCond ENDIF
                | IF ifCond ELSE statements ENDIF
       		| WHILE bool_exp loop
		| DO loop WHILE bool_exp
  		| FOREACH IDENT IN IDENT loop
		| READ M8 vars
                | WRITE M9 vars
                | CONTINUE
                | RETURN expression
                ;

M8:		/*empty*/ {isReading = true;}
M9:		/*empty*/ {isReading = false;}

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
		| expression comp expression {
			string temp = newTemp();
			
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

expression:	  multiplicative_expression {}
                | expression ADD multiplicative_expression {
			string temp = newTemp();
			string lhs = opList.back(); opList.pop_back();
			string rhs = opList.back(); opList.pop_back();
			milCode.push_back(genQuad("+",temp, lhs, rhs));
		}
                | expression SUB multiplicative_expression {
			string temp = newTemp();
			string lhs = opList.back(); opList.pop_back();
			string rhs = opList.back(); opList.pop_back();
			milCode.push_back(genQuad("-",temp, lhs, rhs));
		}
		;

multiplicative_expression:	term {}
				|multiplicative_expression  MULT  term {
					string temp = newTemp();
					string lhs = opList.back(); opList.pop_back();
					string rhs = opList.back(); opList.pop_back();
					milCode.push_back(genQuad("*",temp, lhs, rhs));

				}
				|multiplicative_expression  DIV  term {
					string temp = newTemp();
					string lhs = opList.back(); opList.pop_back();
					string rhs = opList.back(); opList.pop_back();
					milCode.push_back(genQuad("/",temp, lhs, rhs));
				}
				|multiplicative_expression  MOD term {
					string temp = newTemp();
					string lhs = opList.back(); opList.pop_back();
					string rhs = opList.back(); opList.pop_back();
					milCode.push_back(genQuad("%",temp, lhs, rhs));
				}
                		;

term:		terms {}
		|	
		SUB terms %prec UMINUS {}	
		| IDENT parenExpression  {
			string temp = newTemp();
			symTable.push_back(Symbol(temp, "INTEGER"));
			lstStr::iterator iter = find(funcTable.begin(), funcTable.end(), *($1));
			if (iter == funcTable.end()) cout << "ERROR: " + *($1) + " not a function\n";
			else milCode.push_back(genQuad("call", *($1), temp));
			opList.push_back(temp);
			$$.name = new string(temp);
			
			
		}
		;

terms:		number {
			string temp = newTemp();
			$$.name = new string (temp);
			symTable.push_back(Symbol(temp, "INTEGER"));
			milCode.push_back(genQuad("=", temp, to_string($1)));
			opList.push_back(temp);
		}		 
		| var {
			string temp = newTemp();
			$$.name = new string (temp);
			symTable.push_back(Symbol(temp, "INTEGER"));
			string oldOp = opList.back();
			opList.pop_back();
			if (oldOp[0] == '[') { // looking at an array
				string newOp = string(oldOp,3, oldOp.size()-3);
				milCode.push_back(genQuad("=[]", temp, newOp));
			}
			else milCode.push_back(genQuad("=", temp, oldOp));
			
		}
		| L_PAREN expression R_PAREN {} 
		; 
		  
parenExpression: L_PAREN expressions R_PAREN {
			while (!paramTable.empty()) {
				milCode.push_back("param " + paramTable.back());
				paramTable.pop_back();
			}

		}

expressions:	  expression {
			paramTable.push_back(opList.back());
			opList.pop_back();
		 }
		| expression COMMA expressions {
			paramTable.push_back(opList.back());
			opList.pop_back();
		}
			
		;

vars:		  var {}
                | var COMMA vars {}
                ;

var:		ident {
			string ident = *($1);
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) cout << "ERROR: var not found\n";
				else {
					if (iter->type != "INTEGER") cout << "ERROR: var not an int\n";
					else {
						opList.push_back(ident);
						identStack.push(ident);
						$$.value = iter->value;
					}
				}
			$$.name = new string(*$1);
                  }
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
			string ident = *($1);
				Table::iterator iter = find(symTable.begin(), symTable.end(), ident);
				if (iter == symTable.end()) cout << "ERROR: var not found\n";
				else {
					if (iter->type != "ARRAY") cout << "ERROR: var not an array\n";
					else {
						string oldOp = opList.back();
						opList.pop_back();
						opList.push_back(genQuad("[]", ident, oldOp));
						$$.value = iter->value;
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
	
