/* 
 *     Lexical Analysis
 */

letter          [a-zA-Z]
digit           [0-9]
COMMENT         "##".*
WHITESPACE      [ \t]
IDENT           {letter}({letter}|{digit})*(_+({letter}|{digit})+)*
BADSTART        ((({digit}|_)+({letter}|{digit})+)+)
BADEND          (({letter}|{digit})+_+)+
PLUS            [\+]
MINUS           [\-]
MULT            [\*]
DIV             [\/]
MOD             [\%]
OTHERSPECIAL    []:;,\(\)[]|:=
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
const char *token[] = {"FUNCTION","BEGIN_PARAMS","END_PARAMS","BEGIN_LOCALS", 
                       "END_LOCALS", "BEGIN_BODY","END_BODY", "INTEGER",
                       "ARRAY","OF","IF","THEN","ENDIF","ELSE","WHILE","DO",
                       "BEGINLOOP","ENDLOOP","CONTINUE","READ","WRITE","AND",
                       "OR","NOT","TRUE","FALSE","RETURN"};
// other special characters
const int numSpecial = 8;
const char *spclLexPattern[] = {";",":",",","(",")","[","]",":="};
const char *spclToken[] = {"SEMICOLON","COLON","COMMA","L_PAREN","R_PAREN",
                           "L_SQUARE_BRACKET","R_SQUARE_BRACKET","ASSIGN"};
// comparison operators
const int numCmp = 6;
const char *cmpLexPattern[] = {"==","<>","<",">","<=",">="};
const char *cmpToken[] = {"EQ","NEQ","LT","GT","LTE","GTE"};

%}

%%
{COMMENT}      {;}
{IDENT}        {int *result = findWord(yytext, lexPattern, numIdent);
                 if (result[0]){ 
                    //return token[result[1]];
                    printf("%d\n",charToEnum(lexPattern[result[1]]));
                    return charToEnum(lexPattern[result[1]]);
                    //printf("%s\n",token[result[1]]); 
                 }
                 else {
                   return IDENT;
                   //printf("IDENT %s\n",yytext);
                }
                currPos += yyleng;
                free(result);
               }
{OTHERSPECIAL} {int *result = findWord(yytext, spclLexPattern, numSpecial);
                 if (result[0]) //printf("HELLOO %s\n",spclToken[result[1]]);
                    printf("%d\n",charToEnum(spclLexPattern[result[1]]));
                    //return spclToken[result[1]];
                currPos += yyleng;
                free(result);
               }
{COMPARE}      {int *result = findWord(yytext, cmpLexPattern, numCmp);
                  if (result[0]) printf("%s\n",cmpToken[result[1]]) ;
                  else
                    printf("IDENTIFIER %s\n",yytext);
                 currPos += yyleng;
                 free(result);
               }

{digit}+      {currPos += yyleng; return NUMBER;}
{PLUS}        {currPos += yyleng; return ADD;}
{MINUS}       {currPos += yyleng; return SUB;}
{MULT}        {currPos += yyleng; return MULT;}
{DIV}         {currPos += yyleng; return DIV;}
{MOD}         {currPos += yyleng; return MOD;}
{WHITESPACE}  {currPos += yyleng;}
\n            {currLine++; currPos = 0;}
{BADSTART}    {printf("Error at line %d, column %d: Identifier \"%s\" must begin with a letter\"\n", currLine, currPos, yytext); exit(1);}
{BADEND}      {if (isdigit(yytext[0])) {
                 printf("Error at line %d, column %d: Identifier \"%s\" must start with a letter and cannot end with an underscore\"\n", currLine, currPos, yytext); exit(0);}
               else {
                 printf("Error at line %d, column %d: Identifier \"%s\" cannot end with an underscore\"\n", currLine, currPos, yytext); exit(1);}
               }
.             {printf("Error at line %d, column %d: unrecognized symbol \"%s\"\n", currLine, currPos, yytext); exit(1);}
%%

/*
main()
{
  yylex();
}
*/
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
   if (s == "function")		return FUNCTION;
   if (s == "beginparams")	return BEGIN_PARAMS;
   if (s == "endparams") 	return END_PARAMS;
   if (s == "beginlocals") 	return BEGIN_LOCALS;
   if (s == "endlocals") 	return END_LOCALS;
   if (s == "beginbody")	return BEGIN_BODY;
   if (s == "endbody")		return END_BODY;
   if (s == ";") 		return SEMICOLON;
   if (s == ":")		return COLON;
   if (!strcmp(s, ","))		return COMMA;
   if (!strcmp(s, "("))		return L_PAREN;
   if (!strcmp(s, ")"))		return R_PAREN;
   if (s == "[")		return L_SQUARE_BRACKET;
   if (s == "]")		return R_SQUARE_BRACKET;

return IDENT;

}
