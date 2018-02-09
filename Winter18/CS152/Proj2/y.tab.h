/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FUNCTION = 258,
    IDENT = 259,
    INTEGER = 260,
    OF = 261,
    ARRAY = 262,
    READ = 263,
    IF = 264,
    THEN = 265,
    ENDIF = 266,
    ELSE = 267,
    WHILE = 268,
    DO = 269,
    BEGIN_PARAMS = 270,
    BEGIN_LOCALS = 271,
    BEGIN_BODY = 272,
    IN = 273,
    BEGINLOOP = 274,
    ENDLOOP = 275,
    END_PARAMS = 276,
    END_LOCALS = 277,
    END_BODY = 278,
    CONTINUE = 279,
    WRITE = 280,
    TRUE = 281,
    FOREACH = 282,
    FALSE = 283,
    RETURN = 284,
    NUMBER = 285,
    ADD = 286,
    MULT = 287,
    DIV = 288,
    MOD = 289,
    AND = 290,
    OR = 291,
    SEMICOLON = 292,
    COLON = 293,
    COMMA = 294,
    L_PAREN = 295,
    R_PAREN = 296,
    L_SQUARE_BRACKET = 297,
    R_SQUARE_BRACKET = 298,
    EQ = 299,
    NEQ = 300,
    LT = 301,
    GT = 302,
    LTE = 303,
    GTE = 304,
    SUB = 305,
    NOT = 306,
    ASSIGN = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "mini_l.y" /* yacc.c:1909  */

   int		iVal;
   char*   	strVal;
   char		charVal;

#line 113 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
