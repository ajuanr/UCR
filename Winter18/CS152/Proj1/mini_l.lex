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

int* findWord(char*, const char*[],int);
%}

%%
{COMMENT}      {;}
{IDENT}        {int *result = findWord(yytext, lexPattern, numIdent);
                 if (result[0]) printf("%s\n",token[result[1]]);
                 else
                   printf("IDENT %s\n",yytext);
                currPos += yyleng;
                free(result);
               }
{OTHERSPECIAL} {int *result = findWord(yytext, spclLexPattern, numSpecial);
                 if (result[0]) printf("%s\n",spclToken[result[1]]);
                 else
                   printf("IDENTIFIER %s\n",yytext);
                currPos += yyleng;
                free(result);
               }
{COMPARE}      {int *result = findWord(yytext, cmpLexPattern, numCmp);
                  if (result[0]) printf("%s\n",cmpToken[result[1]]);
                  else
                    printf("IDENTIFIER %s\n",yytext);
                 currPos += yyleng;
                 free(result);
               }

{digit}+      {printf("NUMBER %s\n", yytext); currPos += yyleng;}
{PLUS}        {printf("ADD\n"); currPos += yyleng;}
{MINUS}       {printf("SUB\n"); currPos += yyleng;}
{MULT}        {printf("MULT\n"); currPos += yyleng;}
{DIV}         {printf("DIV\n"); currPos += yyleng;}
{MOD}         {printf("MOD\n"); currPos += yyleng;}
{WHITESPACE}  {currPos += yyleng;}
\n            {currLine++; currPos = 0;}
{BADSTART}    {printf("Error at line %d, column %d: Identifier \"%s\" must begin with a letter\"\n", currLine, currPos, yytext); exit(0);}
{BADEND}      {if (isdigit(yytext[0])) {
                 printf("Error at line %d, column %d: Identifier \"%s\" must start with a letter and cannot end with an underscore\"\n", currLine, currPos, yytext); exit(0);}
               else {
                 printf("Error at line %d, column %d: Identifier \"%s\" cannot end with an underscore\"\n", currLine, currPos, yytext); exit(0);}
               }
.             {printf("Error at line %d, column %d: unrecognized symbol \"%s\"\n", currLine, currPos, yytext); exit(0);}
%%

#include <stdlib.h>

main()
{
  yylex();
}

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

