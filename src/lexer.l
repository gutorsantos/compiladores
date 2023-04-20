%{
   // Definitions
%}
%option yylineno

/** Definição dos tokens **/

DIGIT                                           [0-9]
SIGN                                            [+-]

ID               			                        [a-z][a-z0-9_-]*
INTEGER             	                           {SIGN}?{DIGIT}+
FLOAT               	                           {SIGN}?{DIGIT}+[.]{DIGIT}*
SPACE						                           [ \t\n]+

COMMENT_BLOCK 				                        [/][*]([^*]|([*]+[^*/]))*[*]+[/]
COMMENT_LINE       			                     (\/\/).*

/** Expressoes regulares para definir os tokens **/

%%

%%

int yywrap(void) {
   return 1;
}