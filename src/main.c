#include <stdio.h>

#include "y.tab.h"


int main(int argc, char* argv[]) {
    FILE* input_file = fopen(argv[1], "r");
    yyin = input_file;

    int token;
    while ((token = yylex()) != YYEOF) {
        printf("%s '%s'\n", token_str(token), yytext);
    }
    // yyparse ();
    // printf ( "Parse Completed\n" );
    // if ( errors == 0 ) {
    //     print_code ();
    //     fetch_execute_cycle();
    // }

    return 0;
}
