/* Juan's Grammar for CS152 */
/* mini_l.y */

%{
#define YY_NO_UNPUT


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int yylineno;	
extern char *yytext;

void yyerror(char const*);
int yylex(void);
#define YYSTYPE int
%}

%start		prog_start	
%token	<reserved>   FUNCTION
%token		IDENT
%token		     SEMICOLON
%token	<reseved>    BEGIN_PARAMS BEGIN_LOCALS BEGIN_BODY
%token		     END_PARAMS END_LOCALS END_BODY
%token	<int_val>    NUMBER
%left		     ADD MULT DIV MOD AND OR
%left   <arithmetic> SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN
%right  <arithmetic> SUB 
%right		NOT

%union{
   int		int_val;
   char*   	reserved;
   char		arithmetic;
}

%%
prog_start:	functions {printf("prog_start -> functions\n");}
functions:	function functions | %empty {printf("HELLOOOOOOOOOO\n");}
function: 	FUNCTION IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS {printf("HELLOOOOOOOOOO\n");}
declarations:	END_LOCALS BEGIN_BODY statements END_BODY {printf("HELLOOOOOOOOOO\n");}
statements:	%empty {printf("HELLOOOOOOOOOO\n");}

%%

int main() {
   yyparse();

   return 0;
}

void
yyerror (char const *s)
{
  fprintf (stderr, "ERROR: %s at symbol \"%s \" on line %d\n", s, yytext,yylineno);
}


