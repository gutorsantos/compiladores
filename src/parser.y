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

%union semrec{
    int intval;
    float floatval;
    char* stringval;
    char* id;
    struct ASTNode* node;
    char operation;
}

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

%type <node> program declarations id_seq commands command exp 
%type <operation> '+' '-' '*' '/' '=' '>' '<' '^' 

%start program

%%

program:        LET 
                    declarations
                IN                                              {root = create_node(AST_PROGRAM, (UnionTypes) {}); root->left = $2;}
                    commands
                END                                             {$$ = root;}
                ;

declarations:   /* empty */                                     {$$ = NULL;}
                | INTEGER id_seq IDENTIFIER '.'                 {$$ = create_node(AST_DECLARATIONS, (UnionTypes) {}); install($3);}
                ;

id_seq:         /* empty */                                     {$$ = NULL;}
                | id_seq IDENTIFIER ','                         {install($2); $$ = create_node(AST_IDENTIFIER, (UnionTypes) { .id = $2 }); $$->left=$1;}
                ;

commands:       /* empty */                                     {$$ = NULL;}
                | commands command ';'                          {$$ = create_node(AST_COMMANDS, (UnionTypes) {}); $$->left = $1; $$->right = $2;}                              
                ;

command:        SKIP                                            {$$ = create_node(AST_SKIP, (UnionTypes) {});}
                | READ IDENTIFIER                               {$$ = context_check(AST_READ, $2);}
                | WRITE exp                                     {$$ = create_node(AST_WRITE, (UnionTypes) { .exp = $2 });}
                | IDENTIFIER ASSGNOP exp                        {$$ = context_check(AST_ASSIGNMENT, $1);}
                | IF exp                                        
                    THEN commands                               
                  ELSE                                          
                    commands
                  FI                                            {$$ = create_node(AST_IF, (UnionTypes) { .exp = $2 }); $$->left=$4; $$->right=$6;}
                | WHILE                                         
                    exp                                         
                  DO
                    commands
                  END                                           {$$ = create_node(AST_WHILE, (UnionTypes) { .exp = $2 }); $$->left=$4;}
                ;

exp:            NUMBER                                          {$$ = create_node(AST_INTEGER, (UnionTypes) { .intval = $1 });}
                | IDENTIFIER                                    {$$ = context_check(AST_IDENTIFIER, $1);}
                | exp '<' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | exp '=' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | exp '>' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | exp '+' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | exp '-' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | exp '*' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | exp '/' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | exp '^' exp                                   {$$ = create_node(AST_BINARY_OPERATION, (UnionTypes) { .operation = $2 }); $$->left=$1; $$->right=$3;}
                | '(' exp ')'                                   {$$ = $2;}
                ;

%%

void yyerror(char *s) {
    printf("Error: %d!\n", --yylineno);
}
