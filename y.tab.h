/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ASSGNOP = 258,                 /* ASSGNOP  */
    DO = 259,                      /* DO  */
    ELSE = 260,                    /* ELSE  */
    END = 261,                     /* END  */
    FLOAT = 262,                   /* FLOAT  */
    IDENTIFIER = 263,              /* IDENTIFIER  */
    IF = 264,                      /* IF  */
    WHILE = 265,                   /* WHILE  */
    IN = 266,                      /* IN  */
    INTEGER = 267,                 /* INTEGER  */
    LET = 268,                     /* LET  */
    READ = 269,                    /* READ  */
    READ_FT = 270,                 /* READ_FT  */
    SKIP = 271,                    /* SKIP  */
    THEN = 272,                    /* THEN  */
    WRITE = 273,                   /* WRITE  */
    WRITE_FT = 274                 /* WRITE_FT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ASSGNOP 258
#define DO 259
#define ELSE 260
#define END 261
#define FLOAT 262
#define IDENTIFIER 263
#define IF 264
#define WHILE 265
#define IN 266
#define INTEGER 267
#define LET 268
#define READ 269
#define READ_FT 270
#define SKIP 271
#define THEN 272
#define WRITE 273
#define WRITE_FT 274

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "src/parser.y"
            // Acrescentar tipos aqui
    int intval;     // Inteiro
    float floatval; // Float 
    char* id;       // Identificadores
    struct lbs* lbls;

#line 112 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
