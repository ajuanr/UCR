/* Juan's Grammar for CS152 */
/* mini_l.y */

%{
#define YY_NO_UNPUT


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int currLine;	
extern int currPos;
extern char *yytext;

void yyerror(char const*);
int yylex(void);
%}

%union{
   int		iVal;
   char*   	strVal;
   char		charVal;
   
}
%error-verbose
%token		   	FUNCTION
%token  		INTEGER OF ARRAY READ IF THEN ENDIF ELSE WHILE DO 
%token		    	BEGIN_PARAMS BEGIN_LOCALS BEGIN_BODY IN BEGINLOOP ENDLOOP
%token			END_PARAMS END_LOCALS END_BODY CONTINUE WRITE TRUE FOREACH
%token 			FALSE RETURN
%token	<iVal>   	NUMBER
%left		 	ADD MULT DIV MOD AND OR
%left    		SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET 
%left			EQ NEQ LT GT LTE GTE
%right  	 	SUB 
%right			NOT UMINUS
%right  		ASSIGN
%token  <strVal>	IDENT

%type<iVal> number
%type<strVal> ident identifiers


%%
prog_start:	functions
                ;
functions:	function functions
                | /*empty*/
                ;
function: 	FUNCTION ident SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY
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

term:		  SUB number %prec UMINUS
                | number
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

vars:		  var
                | var varList
                ;

varList:	COMMA vars
		;

var:		  ident
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET
		;

identifiers:      ident {$$ = $1;}
		| ident identList
		;

identList:      COMMA identifiers

ident:		IDENT {$$ = $1;}
                ;

number:		NUMBER {$$ = $1;}
                ;

%%

int main() {
   yyparse();

   return 0;
}

void
yyerror (char const *s)
{
  fprintf (stderr, "error at line %d:  \"%s\"\n", currLine, s);
}

