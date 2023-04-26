%{
int yylex (void);
void yyerror (char const *);
%}

// definitions
%token ID INTEGER_VAL FLOAT_VAL WALRUS OPERATOR
%token STRING DO ELSE END FI IF IN INTEGER LET
%token READ SKIP THEN WHILE WRITE
%%

one : '1'

%%

// subroutines
