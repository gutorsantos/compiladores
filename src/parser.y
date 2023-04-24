%{
int yylex (void);
void yyerror (char const *);
int main();
%}

// definitions


%%

one : '1'

%%

// subroutines
