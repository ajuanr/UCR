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
    bool operator==(const string &rhs) {
       return !(this->name.compare(rhs)); // returns true if strings are equal
    }
};

   

int currentTemp=0; 	// the current number of temporary variables
int currentLabel=1; 	// the current number of labels

vecSym arrayList;
vecStr identList;    	// holds list of identifiers seen
vecSym symTable; 	// holds list of symbols
vecSym paramList;       // for function calls
vecStr stmntsList; 	// hold the final statements for the MIL code

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
%type<strVal> ident identifiers
%type<vecA> vars varList 
%type<attribute> var 

%%
prog_start:	functions
                ;
functions:	function functions
                | /*empty*/
                ;
function: 	FUNCTION ident SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY {
                    for (auto stmnt : stmntsList) {
			cout << stmnt << endl;

                    }

                }
                ;
declarations:	declaration SEMICOLON declarations
                | /*empty*/
                ;

declaration:    identifiers COLON INTEGER
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
                     
                  }
                | number {
}
		| var
		| SUB var %prec UMINUS
                | L_PAREN expression R_PAREN
                | SUB L_PAREN expression R_PAREN  %prec UMINUS
		| ident L_PAREN expressions R_PAREN
		;

expressions:	  expression
		| expression exprList
		;

exprList:	COMMA expressions
		;

vars:		  var {
                  $$->push_back($1);
                }
                | var varList {
                     $$->push_back($1);
		     for (int i = 0; i != $2->size(); ++i) cout << (*$2)[i].name << endl;
                }
                ;

varList:	COMMA vars {
     		    $$ = $2;
                }
		;

var:		ident {
                  if (inSymTable(*($1))) { // symbol has already been declared
                      cout << "Error at line " << currLine << ", position " << currPos
	                   << ". " << *($1) << " is undeclared\n";
			exit(1);
		  }
                  identList.push_back(*($1));
                  $$.name = $1;
                }
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {
                }
		;

identifiers:      ident 
		| ident identList
		;

identList:      COMMA identifiers
		;

ident:		IDENT {
                    *($$) = ". _" + *($1);
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
    if (!(sym->type.compare("int"))) {
        return true;
    }
    cout << "Error, invalid type\n";
    return false; 
}

// return true if string s in in list
bool inArrayList(string s){
    vecSym::iterator sym = find(symTable.begin(), symTable.end(), s);
    if (sym == symTable.end()) { // symbol not in table
        cout << "Error at line " << currLine << ", position " << currPos
             << ". " << s << " is undeclared\n";
        return false;
    }
    if (!(sym->type.compare("int"))) {
        cout << "Error, not an array\n";
        return false;
    }
    return true;
}



