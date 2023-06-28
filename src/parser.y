%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/codegen/ast.h"

#define YYDEBUG 1

void yyerror(char*);
int yylex(void);
extern int yylineno;
%}

%union semrec{
    struct ASTNode* node;
} 

%start program
%token <id> ASSGNOP
%token DO
%token ELSE
%token END
%token <id> IDENTIFIER
%token <lbls> IF WHILE
%token IN 
%token LET 
%token INTEGER 
%token FLOAT
%token <intval> NUMBER
%token <floatval> NUMBER_FLOAT
%token <id> STRING
%token READ 
%token READ_FT
%token SKIP
%token THEN
%token WRITE
%token WRITE_FT

%left '-' '+'
%left '*' '/'
%right '^'

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

id_seq:         /* empty */
                | id_seq IDENTIFIER ','                         {}
                ;

commands:       /* empty */
                | commands command ';'                               
                ;

command:        SKIP
                | READ IDENTIFIER                               {}
                | WRITE exp                                     {}
                | IDENTIFIER ASSGNOP exp                        {}
                | IF exp                                        {}
                    THEN commands                               {}
                  ELSE                                          {}
                    commands
                  END                                           {}
                | WHILE                                         {}
                    exp                                         {}
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
                | '(' exp ')'
                ;

%%

void yyerror(char *s) {
    printf("Error: %d!\n", --yylineno);
}
