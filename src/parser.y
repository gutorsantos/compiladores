%{

%}

// definitions

%token INTEGER
%token FLOAT
%token ID
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LBRACE
%token RBRACE
%token OPERATOR

%%

expr_atom: INTEGER
    | FLOAT
    | ID
    | LPAREN expr RPAREN

expr: expr_atom
    | expr_atom OPERATOR expr

%%

// subroutines
