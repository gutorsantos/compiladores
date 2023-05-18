%{
#include <string.h>
#include <stdio.h>
#include "../generated/y.tab.h"
%}

%option yylineno

DIGIT                                           [0-9]
SIGN                                            [+-]

ID                                              [a-zA-Z][a-zA-Z0-9_-]*
INTEGER                                         {SIGN}?{DIGIT}+
FLOAT                                           {SIGN}?{DIGIT}*[.]{DIGIT}*
SPACE  		                                      [ \t\n]+
STRING                                          \"[^\"]*\"

OPERATOR                                        [+-/*%&|^<>!]|==|!=|>=|<=|&&|\|\|
COMMENT_BLOCK 				                          [/][*]([^*]|([*]+[^*/]))*[*]+[/]
COMMENT_LINE       			                        (\/\/).*

/** Expressoes regulares para definir os tokens **/

%%
{SPACE}             ;
{COMMENT_BLOCK}     ;
{COMMENT_LINE}      ;
{INTEGER}           { yylval.intval = atoi(yytext); return NUMBER; }
":="                { return ASSGNOP; }
do                  { return DO; }
else                { return ELSE; }
end                 { return END; }
if                  { return IF; }
in                  { return IN; }
integer             { return INTEGER; }
let                 { return LET; }
read                { return READ; }
skip                { return SKIP; }
then                { return THEN; }
while               { return WHILE; }
write               { return WRITE; }
{ID}                { yylval.id = (char *) strdup(yytext); return IDENTIFIER; }
.                   { return (yytext[0]); }
%%

int yywrap(void) {
   return 1;
}

