#include <stdio.h>

#include "lex.yy.h"
#include "test.h"
#include "y.tab.h"
#include "token_str.h"

int main(int argc, char* argv[]) {
    FILE* input_file = fopen(argv[1], "r");
    yyin = input_file;

    int token;
    while ((token = yylex()) != YYEOF) {
        printf("%s '%s'\n", token_str(token), yytext);
    }

    return 0;
}
