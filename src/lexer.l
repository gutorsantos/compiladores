%{
#include <string.h>
#include <stdio.h>
#include "y.tab.h"
%}

%option yylineno

DIGIT                                           [0-9]
SIGN                                            [+-]

ID                                              [a-zA-Z][a-zA-Z0-9_-]*
INTEGER                                         {SIGN}?{DIGIT}+
FLOAT                                           {SIGN}?{DIGIT}*[.]{DIGIT}*
SPACE  		                                    [ \t\n]+
STRING                                          \"[^\"]*\"

OPERATOR                                        [+-/*%&|^<>!]|==|!=|>=|<=|&&|\|\|
COMMENT_BLOCK 				                    [/][*]([^*]|([*]+[^*/]))*[*]+[/]
COMMENT_LINE       			                    (\/\/).*

/** Expressoes regulares para definir os tokens **/

%%
{SPACE}             ;
{COMMENT_BLOCK}     ;
{COMMENT_LINE}      ;
do                  { return DO; }
else                { return ELSE; }
end                 { return END; }
fi                  { return FI; }
if                  { return IF; }
in                  { return IN; }
integer             { return INTEGER; }
let                 { return LET; }
read                { return READ; }
skip                { return SKIP; }
then                { return THEN; }
while               { return WHILE; }
write               { return WRITE; }
":="                { return WALRUS; }
{ID}                { return ID; }
{STRING}            { return STRING; }
{INTEGER}           { yylval = atoi(yytext); return INTEGER_VAL; }
{FLOAT}             { yylval = atof(yytext); return FLOAT_VAL; }

.                   { return (yytext[0]); }
%%

int yywrap(void) {
   return 1;
}

void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
