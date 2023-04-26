%{
int yylex (void);
void yyerror (char const *);
%}

// definitions
%token ID INTEGER_VAL FLOAT_VAL
%token WALRUS STRING
%token DO ELSE FI IF IN LET WHILE THEN INTEGER END
%token READ WRITE SKIP
%%

one : '1'

%%

// subroutines
