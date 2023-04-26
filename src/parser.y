%{
int yylex (void);
void yyerror (char const *);
%}

// definitions
%token ID
%token INTEGER
%token FLOAT
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LBRACE
%token RBRACE
%token OPERATOR
%token STRING
%token SEMICOLON
%token DO
%token ELSE
%token END
%toknen FI
%token IF
%token IN
%token LET
%token READ
%ẗoken SKIP
%token THEN
%token WHILE
%token WRITE

%%

one : '1'

%%

// subroutines
