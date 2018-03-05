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

struct Symbol; // forward declaration

typedef vector<string> vecStr;
typedef vector<Symbol> vecSym;
typedef stack<Symbol> stackSym;


bool inSymTable(string);
bool inArrayList(string);
string genQuad(string op, string src1, string src2, string dest);
string genLabel();
string genTemp();

struct Symbol{
    Symbol(string n):name(n) {}
    Symbol(string n, string t):name(n),type(t) {}
    string name;
    string type;
    int value;
    bool operator==(const string &rhs) {
       return !(this->name.compare(rhs)); // returns true if strings are equal
    }
};

   

int currentTemp=0; 	// the current number of temporary variables
int currentLabel=1; 	// the current number of labels

vecStr milCode;		// holds the code generated
vecSym identList;    	// holds list of identifiers seen
vecSym symTable; 	// holds list of symbols
vecSym paramList;       // for function calls
vecStr stmntsList; 	// hold the final statements for the MIL code
stackSym paramQ;	
bool addtoParams = false;
%}

%union{
   int		iVal;
   string* 	strVal;
typedef struct Attributes{
   string* name;
   string* type;
   string* code;
}Attributes;
   Attributes attribute;
   vector<Attributes> *vecA;
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
%type<attribute> ident identifiers
%type<attribute> var


%%
prog_start:	functions
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
		cout << "declaration sees: " << *($1.name) << endl;
		
                }
		| identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER
                ;

statements:       statement SEMICOLON statements
                | /*empty*/
                ;

statement:        var ASSIGN expression
                | IF ifCond ENDIF
                | IF ifCond ELSE statements ENDIF
       		| WHILE bool_exp loop
		| DO loop WHILE bool_exp
  		| FOREACH ident IN ident loop
		| READ vars
                | WRITE vars
                | CONTINUE
                | RETURN expression
                ;

ifCond:		bool_exp THEN statements
                ;

loop:		BEGINLOOP statements ENDLOOP
                ;

bool_exp:	  relation_and_exp
                | relation_and_exp OR relation_and_exp
		; 

relation_and_exp: relation_exp
                | relation_exp AND relation_and_exp
                ;

relation_exp:	  NOT relation_exp
		| expression comp expression
                | TRUE
                | FALSE
                | L_PAREN bool_exp R_PAREN
                ;

comp:	   	  EQ
		| NEQ
		| LT
		| GT
		| LTE
		| GTE
                ;

expression:	  multiplicative_expression
                | multiplicative_expression ADD expression
                | multiplicative_expression SUB expression
		;

multiplicative_expression:	  term
				| term MULT term
				| term DIV term
				| term MOD term
                		;

term:		  SUB number %prec UMINUS {
		     string newTemp = genTemp(); 
		     milCode.push_back(genQuad("-", "0", to_string($2), newTemp));
                     
                  }
                | number{
                 }
		| var
		| SUB var %prec UMINUS
                | L_PAREN expression R_PAREN
                | SUB L_PAREN expression R_PAREN  %prec UMINUS
		| ident L_PAREN expressions R_PAREN
		;

expressions:	  expression
		  {
		    paramQ.push(identList.back());	
		    cout << "Pushed " << identList.back().name << "onto stack\n";
		    identList.pop_back();

		 }
		| expression exprList
		;

exprList:	COMMA expressions
		;

vars:		  var {
		    cout << "IN vars\n";
		  }
                | var COMMA vars
                ;

var:		ident {
                    if (inSymTable(*$1.name)) {
                        identList.back().type = "INTEGER"; // not an array identifier
			cout << "var ident was in table\n";
	            }
		    $$ = $1;
                }
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
  		    Symbol temp = identList.back();
		    identList.pop_back();
                    if (inArrayList(*($1.name))) {
		       identList.push_back(temp); 
  		    }
                }
		;

identifiers:      ident {
		 *($$.name) = *($1.name);
		cout << "identifiers sees: " << *($1.name) << endl;
 		}
                   
		| ident COMMA identifiers
		;

ident:		IDENT {
                    if (!inSymTable(*($1))) { // have not seen before
		        identList.push_back(Symbol(*($1)));
                    }
                    else {
			cout << "Error at line: " << currLine << "redeclaring: " << $1 << "\n";
		    }
	        *($$.name) = *($1);	
			
                }
                ;

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

// return true if string s is in list
bool inSymTable(string s){
    vecSym::iterator sym = find(symTable.begin(), symTable.end(), s);
    if (sym == symTable.end()) { // symbol not in table
        return false;
    }
    if (!(sym->type.compare("INTEGER"))) {
        return true;
    }
    cout << "Error, invalid type\n";
    return false; 
}

// return true if string s in in list
bool inArrayList(string s){
    vecSym::iterator sym = find(symTable.begin(), symTable.end(), s);
    for (auto i : symTable) { cout << "var " << i.name << endl;}
    if (sym == symTable.end()) { // symbol not in table
        cout << "Error at line " << currLine << ", position " << currPos
              << s << " is undeclared\n";
        return false;
    }
    cout << "symbol type is: " << sym->type << endl;
    if (!(sym->type.compare("INTEGER"))) {
        cout << "Error, not an array\n";
        return false;
    }
    return true;
}

string genTemp() {
    return "t" + to_string(currentTemp++);
}

string genLabel() {
    return "L" + to_string(currentLabel++);
}

string genQuad(string op, string src1, string src2, string dest) {
    return ". " + op + " " + dest + ", " + src1 + ", " + src2; 
}
