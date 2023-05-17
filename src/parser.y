%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../src/the_parser.h"
#include "../src/scanner.h"
#include "../src/symbol_table.h"

#define YYDEBUG 1

void yyerror(char*);
int yylex(void);
extern int yylineno;
%}

%union semrec{
    int intval;
    float floatval;
    char* id;
    struct lbs* lbls;
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
                IN                                              {gen_code(DATA, data_location()-1);}
                    commands
                END                                             {gen_code(HALT, 0); YYACCEPT;}
                ;

declarations:   /* empty */                                     {install("0");}
                | INTEGER id_seq IDENTIFIER '.'                 {install($3);}
                ;

id_seq:         /* empty */
                | id_seq IDENTIFIER ','                         {install($2);}
                ;

commands:       /* empty */
                | commands command ';'                               
                ;

command:        SKIP
                | READ IDENTIFIER                               {context_check(READ_INT, $2);}
                | WRITE exp                                     {gen_code(WRITE_INT, 0);}
                | IDENTIFIER ASSGNOP exp                        {context_check(STORE, $1);}
                | IF exp                                        {$1 = (lbs *) newlbl(); $1->for_jmp_false = reserve_loc();}
                    THEN commands                               {$1->for_goto = reserve_loc();}
                  ELSE                                          {back_patch($1->for_jmp_false, JMP_FALSE, gen_label());}
                    commands
                  END                                           {back_patch($1->for_goto, GOTO, gen_label());}
                | WHILE                                         {$1 = (lbs *) newlbl(); $1->for_goto = gen_label();}
                    exp                                         {$1->for_jmp_false = reserve_loc();}
                  DO
                    commands
                  END                                           {gen_code(GOTO, $1->for_goto); 
                                                                 back_patch($1->for_jmp_false, JMP_FALSE, gen_label());}
                ;

exp:            NUMBER                                          {gen_code(LD_INT, $1);}
                | IDENTIFIER                                    {context_check(LD_VAR, $1);}
                | exp '<' exp                                   {gen_code(LT, 0);}
                | exp '=' exp                                   {gen_code(EQ, 0);}
                | exp '>' exp                                   {gen_code(GT, 0);}
                | exp '+' exp                                   {gen_code(ADD, 0);}
                | exp '-' exp                                   {gen_code(SUB, 0);}
                | exp '*' exp                                   {gen_code(MULT, 0);}
                | exp '/' exp                                   {gen_code(DIV, 0);}
                | exp '^' exp                                   {gen_code(PWR, 0);}
                | '(' exp ')'
                ;

%%

void yyerror(char *s) {
    printf("Problema com a analise sintatica na linha %d!\n", --yylineno);
}
