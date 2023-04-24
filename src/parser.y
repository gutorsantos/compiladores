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

%%

one : '1'

%%

// subroutines
