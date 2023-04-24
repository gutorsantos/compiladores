%{
   // Definitions
#include <stdio.h>
#include "y.tab.h"
%}

%option yylineno

DIGIT                                           [0-9]
SIGN                                            [+-]

ID                                              [a-z][a-z0-9_-]*
INTEGER                                         {SIGN}?{DIGIT}+
FLOAT                                           {SIGN}?{DIGIT}+[.]{DIGIT}*
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
{INTEGER}           { yylval = atoi(yytext); return INTEGER; }
{FLOAT}             { yylval = atof(yytext); return FLOAT; }
{ID}                { return ID; }
{STRING}            { return STRING; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LBRACKET; }
"}"                 { return RBRACKET; }
"["                 { return LBRACE; }
"]"                 { return RBRACE; }
{OPERATOR}          { return OPERATOR; }
";"                 { return SEMICOLON; }
%%

int yywrap(void) {
   return 1;
}

void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
