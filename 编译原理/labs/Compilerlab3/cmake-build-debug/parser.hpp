
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
     NUMBER = 258,
     IDENTIFIER = 259,
     INT = 260,
     RETURN = 261,
     MAIN = 262,
     VOID = 263,
     PREDEFINED_FUNCTION = 264,
     ASSIGN = 265,
     ADD = 266,
     SUB = 267,
     MUL = 268,
     DIV = 269,
     MOD = 270,
     LESS = 271,
     LESS_EQUAL = 272,
     GREATER = 273,
     GREATER_EQUAL = 274,
     EQUAL = 275,
     NOTEQUAL = 276,
     BITWISE_AND = 277,
     BITWISE_OR = 278,
     BITWISE_XOR = 279,
     LOGICAL_AND = 280,
     LOGICAL_OR = 281,
     NOT = 282,
     BITWISE_NOT = 283,
     SEMICOLON = 284,
     LEFT_BRACE = 285,
     RIGHT_BRACE = 286,
     LEFT_PAREN = 287,
     RIGHT_PAREN = 288,
     COMMA = 289,
     UNKNOWN = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 69 "E:/CompilerLabs/Compilerlab3/parser.y"

    int index;



/* Line 1676 of yacc.c  */
#line 93 "E:/CompilerLabs/Compilerlab3/cmake-build-debug/parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


