
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
     IF = 260,
     ELSE = 261,
     WHILE = 262,
     CONTINUE = 263,
     BREAK = 264,
     INT = 265,
     RETURN = 266,
     MAIN = 267,
     VOID = 268,
     PREDEFINED_FUNCTION = 269,
     ASSIGN = 270,
     ADD = 271,
     SUB = 272,
     MUL = 273,
     DIV = 274,
     MOD = 275,
     LESS = 276,
     LESS_EQUAL = 277,
     GREATER = 278,
     GREATER_EQUAL = 279,
     EQUAL = 280,
     NOTEQUAL = 281,
     BITWISE_AND = 282,
     BITWISE_OR = 283,
     BITWISE_XOR = 284,
     LOGICAL_AND = 285,
     LOGICAL_OR = 286,
     NOT = 287,
     BITWISE_NOT = 288,
     SEMICOLON = 289,
     LEFT_BRACE = 290,
     RIGHT_BRACE = 291,
     LEFT_PAREN = 292,
     RIGHT_PAREN = 293,
     COMMA = 294,
     UNKNOWN = 295
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 74 "E:/CompilerLabs/Compilerlab4/parser.y"

    int index;



/* Line 1676 of yacc.c  */
#line 98 "E:/CompilerLabs/Compilerlab4/cmake-build-debug/parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


