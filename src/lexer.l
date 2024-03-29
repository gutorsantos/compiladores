%{
#include <string.h>
#include <stdio.h>
#include "../generated/y.tab.h"
#include "../src/codegen/ast.h"
%}

%option yylineno

DIGIT                                           [0-9]
SIGN                                            [+-]

ID                                              [a-zA-Z][a-zA-Z0-9_-]*
NUMBER                                          {SIGN}?{DIGIT}+
NUMBER_FLOAT                                    {SIGN}?{DIGIT}+[.]{DIGIT}*
SPACE  		                                    [ \t\n]+
STRING                                          \"[^\"]*\"

OPERATOR                                        [+-/*%&|^<>!]|==|!=|>=|<=|&&|\|\|
COMMENT_BLOCK 				                        [/][*]([^*]|([*]+[^*/]))*[*]+[/]
COMMENT_LINE       			                     (\/\/).*

/** Expressoes regulares para definir os tokens **/

/** {DIGIT}+           { yylval.intval = atoi(yytext); return NUMBER; }*/
%%
{SPACE}             ;
{COMMENT_BLOCK}     ;
{COMMENT_LINE}      ;
{NUMBER}            { yylval.intval = atoi(yytext); return NUMBER; }
{NUMBER_FLOAT}      { yylval.floatval = atof(yytext); return NUMBER_FLOAT; }
":="                { return ASSGNOP; }
do                  { return DO; }
else                { return ELSE; }
end                 { return END; }
if                  { return IF; }
fi                  { return FI; }
in                  { return IN; }
integer             { return INTEGER; }
let                 { return LET; }
read                { return READ; }
skip                { return SKIP; }
then                { return THEN; }
while               { return WHILE; }
write               { return WRITE; }
{ID}                { yylval.id = (char *) strdup(yytext); return IDENTIFIER; }
{STRING}            { yylval.stringval = (char *) strdup(yytext); return STRING; }
.                   { return (yytext[0]); }
%%

int yywrap(void) {
   return 1;
}

