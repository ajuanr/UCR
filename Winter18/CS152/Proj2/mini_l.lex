/* 
 *     Lexical Analysis
 */

letter          [a-zA-Z]
digit           [0-9]
COMMENT         "##".*
WHITESPACE      [ \t]+
NEWLINE         [\n]
IDENT           {letter}({letter}|{digit})*(_+({letter}|{digit})+)*
BADSTART        ((({digit}|_)+({letter}|{digit})+)+)
BADEND          (({letter}|{digit})+_+)+
PLUS            [\+]
MINUS           [\-]
MULT            [\*]
DIV             [\/]
MOD             [\%]
OTHERSPECIAL    []:;,\(\)[]
ASSIGN		:=
COMPARE         ==|<>|<|>|<=|>=

%{
#include <stdlib.h>
#include "y.tab.h"

int* findWord(char*, const char*[],int);
int charToEnum(const char*); 

int currPos = 0; int currLine = 1;
// identifiers and reserved words
const int numIdent = 27;
const char *lexPattern[] = {"function","beginparams","endparams","beginlocals",
                            "endlocals","beginbody", "endbody","integer",
                            "array","of","if","then","endif","else","while",
                            "do","beginloop","endloop","continue","read",
                            "write","and","or","not","true","false","return"};
// other special characters
const int numSpecial = 8;
const char *spclLexPattern[] = {";",":",",","(",")","[","]"};
// comparison operators
const int numCmp = 6;
const char *cmpLexPattern[] = {"==","<>","<",">","<=",">="};
%}

%%
{COMMENT}      {;}
{IDENT}        {
                 int *result = findWord(yytext, lexPattern, numIdent);
                 yylval.strVal = yytext;
                 currPos += yyleng;
                 if (result[0]){ 
                    free(result);
                    return charToEnum(yytext);
                 }
                 else {
                   free(result);
                   return charToEnum(yytext);
                }
               }
{OTHERSPECIAL} {int *result = findWord(yytext, spclLexPattern, numSpecial);
                 currPos += yyleng;
                 if (result[0]) {
                    free(result);
                    yylval.charVal = yytext[0];
                    return charToEnum(yytext); 
                 }
                free(result);
               }
{COMPARE}      {int *result = findWord(yytext, cmpLexPattern, numCmp);
                 currPos += yyleng;
                 if (result[0]) {
                    yylval.strVal = yytext;
                    return charToEnum(yytext); 
                    free(result);
                 }
               }
{ASSIGN}      {currPos += yyleng; return ASSIGN;}
{digit}+      {currPos += yyleng; yylval.iVal = atoi(yytext);return NUMBER;}
{PLUS}        {currPos += yyleng; yylval.charVal = yytext[0]; return ADD;}
{MINUS}       {currPos += yyleng; yylval.charVal = yytext[0]; return SUB;}
{MULT}        {currPos += yyleng; yylval.charVal = yytext[0];  return MULT;}
{DIV}         {currPos += yyleng; yylval.charVal = yytext[0];  return DIV;}
{MOD}         {currPos += yyleng; yylval.charVal = yytext[0]; return MOD;}
{WHITESPACE}  {currPos += yyleng;}
{NEWLINE}            {currLine++; currPos = 0;}
{BADSTART}    {printf("Error at line %d, column %d: Identifier \"%s\" must begin with a letter\"\n", currLine, currPos, yytext); exit(1);}
{BADEND}      {if (isdigit(yytext[0])) {
                 printf("Error at line %d, column %d: Identifier \"%s\" must start with a letter and cannot end with an underscore\"\n", currLine, currPos, yytext); exit(0);}
               else {
                 printf("Error at line %d, column %d: Identifier \"%s\" cannot end with an underscore\"\n", currLine, currPos, yytext); exit(1);}
               }
.             {printf("Error at line %d, column %d: unrecognized symbol \"%s\"\n", currLine, currPos, yytext); exit(1);}
%%

int* findWord(char *word, const char *list[], int size) {
    // pos 0: word found? 0 for false 1 for true
    // pos 1: index of the word
    int *result = (int*) malloc(2 * sizeof(int));
    if(result == NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    result[0] = 0; result[1] = -1;
    int i;
    for (i=0; i != size; ++i)
        if (!strcmp(word, list[i])) {
            result[0] = 1; // found word in list of reserved words
            result[1] = i; // the index of the word
            return result;
        }
    return result;
}

int charToEnum(const char * s) {
   if (!strcmp(s,"function"))	return FUNCTION;
   if (!strcmp(s,"beginparams"))return BEGIN_PARAMS;
   if (!strcmp(s,"endparams")) 	return END_PARAMS;
   if (!strcmp(s,"beginlocals"))return BEGIN_LOCALS;
   if (!strcmp(s,"endlocals")) 	return END_LOCALS;
   if (!strcmp(s,"beginbody"))	return BEGIN_BODY;
   if (!strcmp(s,"endbody"))	return END_BODY;
   if (!strcmp(s,";")) 		return SEMICOLON;
   if (!strcmp(s,":"))		return COLON;
   if (!strcmp(s, ","))		return COMMA;
   if (!strcmp(s, "("))		return L_PAREN;
   if (!strcmp(s, ")"))		return R_PAREN;
   if (!strcmp(s,"["))		return L_SQUARE_BRACKET;
   if (!strcmp(s,"]"))		return R_SQUARE_BRACKET;
   if (!strcmp(s,"integer"))	return INTEGER;
   if (!strcmp(s,"array"))	return ARRAY;
   if (!strcmp(s,"of"))		return OF;
   if (!strcmp(s,"if"))		return IF;
   if (!strcmp(s,"then"))	return THEN;
   if (!strcmp(s,"endif"))	return ENDIF;
   if (!strcmp(s,"else"))	return ELSE;
   if (!strcmp(s,"while"))	return WHILE;
   if (!strcmp(s,"do"))		return DO;
   if (!strcmp(s,"foreach"))	return FOREACH;
   if (!strcmp(s,"read"))	return READ;
   if (!strcmp(s,"write"))	return WRITE;
   if (!strcmp(s,"beginloop"))	return BEGINLOOP; 
   if (!strcmp(s,"endloop"))	return ENDLOOP;
   if (!strcmp(s,"continue"))	return CONTINUE;
   if (!strcmp(s,"and"))	return AND;
   if (!strcmp(s,"or"))		return OR;
   if (!strcmp(s,"not"))	return NOT;
   if (!strcmp(s,"true"))	return TRUE;
   if (!strcmp(s,"false"))	return FALSE;
   if (!strcmp(s,"return"))	return RETURN;
   if (!strcmp(s,"=="))		return EQ;
   if (!strcmp(s,"<"))		return LT;
   if (!strcmp(s,">"))		return GT;
   if (!strcmp(s,"<="))		return LTE;
   if (!strcmp(s,">="))		return GTE;
   if (!strcmp(s,"<>"))		return NEQ;
return IDENT;
}
