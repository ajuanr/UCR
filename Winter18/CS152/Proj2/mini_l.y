/* Juan's Grammar for CS152 */
/* mini_l.y */

%{
#define YY_NO_UNPUT


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int currLine;	
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
%token	<strVal>   	FUNCTION
%token  <strVal>	IDENT INTEGER OF ARRAY READ IF THEN ENDIF ELSE WHILE DO 
%token	<strVal>    	BEGIN_PARAMS BEGIN_LOCALS BEGIN_BODY IN BEGINLOOP ENDLOOP
%token	<strVal>	END_PARAMS END_LOCALS END_BODY CONTINUE WRITE TRUE FOREACH
%token 	<strVal>	FALSE RETURN
%token	<iVal>   	NUMBER
%left	<strVal> 	ADD MULT DIV MOD AND OR
%left   <charVal>	SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET 
%left	<strVal>	EQ NEQ LT GT LTE GTE
%right  <charVal> 	SUB 
%right	<charVal>	NOT 
%right   <strVal>	ASSIGN


%%
prog_start:	functions {printf("prog_start -> functions\n");}
                ;
functions:	function functions {printf("functions -> function functions\n");}
                | %empty {printf("functions -> epsilon\n");}
                ;
function: 	FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS  declarations END_LOCALS BEGIN_BODY statements END_BODY {printf("FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS declarations END_LOCALS BEGIN_BODY statements END_BODY\n");}
                ;
declarations:	declaration SEMICOLON declarations {printf("declaration -> declaration SEMICOLON declarations\n");}
                | %empty {printf("functions -> epsilon\n");}
                ;
declaration:    identifiers COLON INTEGER {printf("declaration -> identifiers COLON INTEGER\n");}
                |%empty {printf("TEMPORARY\n");}
                ;
statements:     statement SEMICOLON statements {printf("statement SEMICOLON statements\n");} 
		| %empty {printf("statements->empty\n");}
                ;
statement:	READ vars {printf("statements->READ vars\n");}
                | WRITE vars {printf("statements -> WRITE vars\n");}
                | IF bool_exp THEN statements ENDIF {printf("statement -> IF bool_exp THEN statements ENDIF");}
		| DO BEGINLOOP statements ENDLOOP WHILE bool_exp {printf("statement -> DO BEGINLOOP statements ENDLOOP WHILE bool_exp\n");}
                | var ASSIGN expression {printf("statement -> var ASSIGN expression\n");}
                | CONTINUE {printf("statement -> CONTINUE\n");}
                |%empty {printf("statement->empty\n");}
                ;
vars:		var {printf("vars->vars\n");}
var:		ident {printf("var-> ident\n");}
                | ident L_SQUARE_BRACKET expression R_SQUARE_BRACKET
		;
identifiers:	identifiers COLON INTEGER
		| ident {printf("identifiers -> ident\n");}
		;
bool_exp:	relation_and_expression {printf("bool_exp -> relation_and_expression\n");}
relation_and_expression:	relation_exp {printf("relation_and_expression -> relation_exp\n");}
relation_exp:	expression comp expression {printf("relation_exp -> expression comp expression\n");}
ident:		IDENT {printf("ident -> IDENT %s\n", yytext);}
		;
comp:		LT {printf("comp -> LT\n");}
		| GT {printf("comp -> GT\n");}
		| GTE {printf("comp -> GTE\n");}
		| LTE {printf("comp -> LTE\n");}
		| EQ {printf("comp -> EQ\n");}
                ;
expression:	multiplicative_expression {printf("expression -> multiplicative_expression\n");}
                | multiplicative_expression ADD multiplicative_expression {printf("expression -> multiplicative_expression ADD multiplicative_expression\n");}
		;
multiplicative_expression:	term {printf("multiplicative_expression -> term\n");}
                ;
term:		NUMBER {printf("term -> NUMBER\n");}
		| var {printf("term -> var\n");}
                | L_PAREN expression R_PAREN {printf("term -> L_PAREN expression R_PAREN\n");}
		;
%%
int main() {
   yyparse();

   return 0;
}

void
yyerror (char const *s)
{
  fprintf (stderr, "ERROR: %s at symbol \"%s \" on line %d\n", s, yytext,currLine);
}


