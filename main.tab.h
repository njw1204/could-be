
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MAINPROG = 258,
     FUNCTION = 259,
     PROCEDURE = 260,
     BEGIN_BODY = 261,
     END_BODY = 262,
     IF = 263,
     THEN = 264,
     ELIF = 265,
     ELSE = 266,
     NOP = 267,
     WHILE = 268,
     FOR = 269,
     RETURN = 270,
     PRINT = 271,
     IN = 272,
     TYPE_INT = 273,
     TYPE_FLOAT = 274,
     ID = 275,
     INTEGER = 276,
     FLOAT = 277,
     OTHER = 278,
     OP_PLUS = 279,
     OP_MINUS = 280,
     OP_MULT = 281,
     OP_DIV = 282,
     OP_LT = 283,
     OP_GT = 284,
     OP_NE = 285,
     OP_LE = 286,
     OP_GE = 287,
     OP_EQ = 288,
     OP_NOT = 289,
     DE_SEMICOLON = 290,
     DE_COMMA = 291,
     DE_DOT = 292,
     DE_ASSIGN = 293,
     DE_LP = 294,
     DE_RP = 295,
     DE_LSB = 296,
     DE_RSB = 297,
     DE_COLON = 298
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 21 "main.y"

	char name[1024];
	int intData;
	float floatData;



/* Line 1676 of yacc.c  */
#line 103 "main.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


