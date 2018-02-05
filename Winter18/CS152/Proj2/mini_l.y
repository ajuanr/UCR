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

%token   <IDENTIFIER> T_Identifier 
%token		FUNC
%token		IDENT
%token		SEMICOLON
%token		BEGIN_PARAMS
%token		END_PARAMS
%token		BEGIN_LOCALS
%token		END_LOCALS
%token		BEGIN_BODY
%token		END_BODY
/*%union{
   int		int_val;
   string*	everything;
}*/

%%
prog_start:	functions
functions:	function functions | %empty
function: 	FUNC IDENT SEMICOLON BEGIN_PARAMS declarations END_PARAMS BEGIN_LOCALS
declarations:	END_LOCALS BEGIN_BODY statements END_BODY
statements:	%empty

%%

void
yyerror (char const *s)
{
  fprintf (stderr, "ERROR: %s at symbol \"%s \" on line %d\n", s, yytext,yylineno);
}
/*
int yyerror(char const  *s) {
  
  printf(stderr, "ERROR: %s at symbol \"%s \" on line %d", s, yytext, yylineno);
  exit(1);
}
*/
