#include <stdio.h>

#include "lex.yy.h"
#include "test.h"
#include "y.tab.h"

const char* stringify_token(int token_id) {
    switch (token_id) {
        case ID: return "ID";
        case INTEGER: return "INTEGER";
        case FLOAT: return "FLOAT";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACKET: return "LBRACKET";
        case RBRACKET: return "RBRACKET";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case OPERATOR: return "OPERATOR";
        case STRING: return "STRING";
        case SEMICOLON: return "SEMICOLON";
        default: return "???";
    }
}

int main(int argc, char* argv[]) {
    FILE* input_file = fopen(argv[1], "r");
    yyin = input_file;

    int tok;
    while ((tok = yylex()) != YYEOF) {
        printf("%s <%s>\n", stringify_token(tok), yytext);
    }

    return 0;
}
