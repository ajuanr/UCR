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
    INTEGER = 259,
    OF = 260,
    ARRAY = 261,
    READ = 262,
    IF = 263,
    THEN = 264,
    ENDIF = 265,
    ELSE = 266,
    WHILE = 267,
    DO = 268,
    BEGIN_PARAMS = 269,
    BEGIN_LOCALS = 270,
    BEGIN_BODY = 271,
    IN = 272,
    BEGINLOOP = 273,
    ENDLOOP = 274,
    END_PARAMS = 275,
    END_LOCALS = 276,
    END_BODY = 277,
    CONTINUE = 278,
    WRITE = 279,
    TRUE = 280,
    FOREACH = 281,
    FALSE = 282,
    RETURN = 283,
    NUMBER = 284,
    ADD = 285,
    MULT = 286,
    DIV = 287,
    MOD = 288,
    AND = 289,
    OR = 290,
    SEMICOLON = 291,
    COLON = 292,
    COMMA = 293,
    L_PAREN = 294,
    R_PAREN = 295,
    L_SQUARE_BRACKET = 296,
    R_SQUARE_BRACKET = 297,
    EQ = 298,
    NEQ = 299,
    LT = 300,
    GT = 301,
    LTE = 302,
    GTE = 303,
    SUB = 304,
    NOT = 305,
    UMINUS = 306,
    ASSIGN = 307,
    IDENT = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "mini_l.y" /* yacc.c:1909  */

   int		iVal;
   string* 	strVal;
   

#line 114 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
