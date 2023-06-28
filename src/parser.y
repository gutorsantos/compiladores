%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/codegen/ast.h"
#include "../src/parser/parser.h"

#define YYDEBUG 1

void yyerror(char*);
int yylex(void);
extern int yylineno;
%}

%token <id> IDENTIFIER
%token <intval> NUMBER
%token <floatval> NUMBER_FLOAT
%token <stringval> STRING
%token SKIP
%token READ
%token WRITE
%token LET
%token IN
%token END
%token IF
%token FI
%token DO
%token THEN
%token ELSE
%token WHILE
%token INTEGER 
%token <id> ASSGNOP

%left '-' '+'
%left '*' '/' 
%right '^'

%start program

%%

program:        LET 
                    declarations
                IN                                              {}
                    commands
                END                                             {}
                ;

declarations:   /* empty */                                     {}
                | INTEGER id_seq IDENTIFIER '.'                 {}
                ;

id_seq:         /* empty */                                     {}
                | id_seq IDENTIFIER ','                         {}
                ;

commands:       /* empty */                                     {}
                | commands command ';'                          {}                              
                ;

command:        SKIP                                            {}
                | READ IDENTIFIER                               {}
                | WRITE exp                                     {}
                | IDENTIFIER ASSGNOP exp                        {}
                | IF exp                                        
                    THEN commands                               
                  ELSE                                          
                    commands
                  FI                                            {}
                | WHILE                                         
                    exp                                         
                  DO
                    commands
                  END                                           {}
                ;

exp:            NUMBER                                          {}
                | IDENTIFIER                                    {}
                | exp '<' exp                                   {}
                | exp '=' exp                                   {}
                | exp '>' exp                                   {}
                | exp '+' exp                                   {}
                | exp '-' exp                                   {}
                | exp '*' exp                                   {}
                | exp '/' exp                                   {}
                | exp '^' exp                                   {}
                | '(' exp ')'                                   {}
                ;

%%

void yyerror(char *s) {
    printf("Error: %d!\n", --yylineno);
}
