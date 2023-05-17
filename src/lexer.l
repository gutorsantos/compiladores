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

/** {DIGIT}+           { yylval.intval = atoi(yytext); return NUMBER; }*/
%%
":="                { return ASSGNOP; }
{SPACE}             ;
{COMMENT_BLOCK}     ;
{COMMENT_LINE}      ;
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
.                   { return (yytext[0]); }
%%

// {ID}                { return yylval.id = (char *) strdup(yytext); return IDENTIFIER; }
int yywrap(void) {
   return 1;
}

void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
