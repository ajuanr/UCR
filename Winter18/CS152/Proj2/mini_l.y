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


%%
prog_start:	functions {printf("prog_start -> functions\n");}
                ;
functions:	function functions {printf("functions -> function functions\n");}
                | %empty {printf("functions -> epsilon\n");}
                ;
function: 	FUNCTION ident SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS  declarations END_LOCALS BEGIN_BODY statements END_BODY {printf("function -> FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY\n");}
                ;
declarations:	declaration SEMICOLON declarations {printf("declaration -> declaration SEMICOLON declarations\n");}
                | %empty {printf("declarations-> epsilon\n");}
                ;

declaration:    identifiers COLON INTEGER {printf("declaration -> identifiers COLON INTEGER\n");}
		| identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER {printf("declaration -> identifiers COLON ARRAY L_SQUARE_BRACKET number R_SQUARE_BRACKET OF INTEGER\n");}
                ;

statements:       statement SEMICOLON statements {printf("statements -> statement SEMICOLON statements\n");} 
                | %empty {printf("statements -> epsilon\n");}
                ;

statement:        var ASSIGN expression {printf("statement -> var ASSIGN expression\n");}
                | IF bool_exp THEN statements ENDIF {printf("statement -> IF bool_exp THEN statements ENDIF\n");}
                | IF bool_exp THEN statements ELSE statements ENDIF {printf("statement -> IF bool_exp THEN statements ENDIF\n");}
       		| WHILE bool_exp loop {printf("statement -> WHILE bool_exp BEGINLOOP statements ENDLOOP\n");}
		| DO loop WHILE bool_exp {printf("statement -> DO BEGINLOOP statements ENDLOOP WHILE bool_exp\n");}
  		| FOREACH ident IN ident loop {printf("statement -> FOREACH IDENT IN IDENT BEGINLOOP statements ENDLOOP\n");}
		| READ vars {printf("statements -> READ vars\n");}
                | WRITE vars {printf("statements -> WRITE vars\n");}
                | CONTINUE {printf("statement -> CONTINUE\n");}
                | RETURN expression {printf("statement -> RETURN expression\n");}
                ;

loop:		BEGINLOOP statements ENDLOOP
                ;

bool_exp:	  relation_and_exp {printf("bool_exp -> relation_and_exp\n");}
                | relation_and_exp OR relation_and_exp {printf("relation_and_exp OR relation_and_exp\n");}
		; 

relation_and_exp: relation_exp {printf("relation_and_expression -> relation_exp\n");}
                | relation_exp AND relation_and_exp {printf("relation_and_exp -> relation_exp AND relation_and_exp\n");}
                ;

relation_exp:	  NOT relation_exp {printf("NOT relation_exp\n");}
		| expression comp expression {printf("relation_exp -> expression comp expression\n");}
                | TRUE {printf("relation_exp -> TRUE\n");}
                | FALSE {printf("relation_exp -> FALSE\n");}
                | L_PAREN bool_exp R_PAREN {printf("L_PAREN bool_exp R_PAREN\n");}
                ;

comp:	   	  EQ {printf("comp -> EQ\n");}
		| NEQ {printf("comp -> NEQ\n");}
		| LT {printf("comp -> LT\n");}
		| GT {printf("comp -> GT\n");}
		| LTE {printf("comp -> LTE\n");}
		| GTE {printf("comp -> GTE\n");}
                ;

expression:	  multiplicative_expression {printf("expression -> multiplicative_expression\n");}
                | multiplicative_expression ADD expression {printf("expression -> multiplicative_expression ADD expression\n");}
                | multiplicative_expression SUB expression {printf("expression -> multiplicative_expression SUB expression\n");}
		;

multiplicative_expression:	  term {printf("multiplicative_expression -> term\n");}
				| term MULT term {printf("multiplicative_expression -> term MULT term\n");}
				| term DIV term {printf("multiplicative_expression -> term MULT term\n");}
				| term MOD term {printf("multiplicative_expression -> term MOD term\n");}
                		;

term:		SUB number %prec UMINUS {printf("term -> SUB number\n");}
                | number {printf("term -> number\n");}
		| var {printf("term -> var\n");}
		| SUB var %prec UMINUS {printf("term ->  SUB var\n");}
                | L_PAREN expression R_PAREN {printf("term -> L_PAREN expression R_PAREN\n");}
                | SUB L_PAREN expression R_PAREN  %prec UMINUS {printf("term -> SUB L_PAREN expression R_PAREN\n");}
		| ident L_PAREN expressions R_PAREN {printf("term -> IDENT L_PAREN expressions R_PAREN\n");}
		;

expressions:	  expression {printf("expressions -> expression\n");}
		| expression COMMA expressions {printf("expressions -> expression COMMA expressions\n");}
		;

vars:		var {printf("vars -> vars\n");}
                | var COMMA vars {printf("vars -> var COMMA vars\n");}
                ;

var:		ident {printf("var-> ident\n");}
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET {printf("var -> ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET\n");}
		;

identifiers:    ident {printf("identifiers -> ident\n");}
		|ident COMMA identifiers  {printf("identifiers -> ident COMMA identifiers\n");}
		;

ident:		IDENT {printf("ident -> IDENT %s\n",$1);}
                ;

number:		NUMBER {printf("number -> NUMBER %d\n", $1);}
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

