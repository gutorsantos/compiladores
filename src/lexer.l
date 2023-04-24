%{
   // Definitions
%}
%option yylineno

/** Definição dos tokens **/

DIGIT                                           [0-9]
SIGN                                            [+-]

ID                                              [a-z][a-z0-9_-]*
INTEGER                                         {SIGN}?{DIGIT}+
FLOAT                                           {SIGN}?{DIGIT}+[.]{DIGIT}*
SPACE  		                                    [ \t\n]+

OPERATOR                                        [+-/*%&|^<>!]|==|!=|>=|<=|&&|\|\|
COMMENT_BLOCK 				                    [/][*]([^*]|([*]+[^*/]))*[*]+[/]
COMMENT_LINE       			                    (\/\/).*

/** Expressoes regulares para definir os tokens **/

%%
{SPACE}             ;
{COMMENT_BLOCK}     ;
{COMMENT_LINE}      ;
{INTEGER}           { yyval = atoi(yytext); return INTEGER; }
{FLOAT}             { yyval = atof(yytext); return FLOAT; }
{ID}                { return ID; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
{                   { return LBRACKET; }
}                   { return RBRACKET; }
\[                  { return LBRACE; }
\]                  { return RBRACE; }
{OPERATOR}          { return OPERATOR; }
%%

int yywrap(void) {
   return 1;
}
