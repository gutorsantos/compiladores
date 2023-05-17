#include <stdio.h>
#include <the_parser.h>
 #include "../generated/y.tab.h"
#include <token_str.h>

int main(int argc, char* argv[]) {
    FILE* input_file = fopen(argv[1], "r");
    yyin = input_file;

    // printf("Tokens: \n");
    // int token;
    // while ((token = yylex()) != YYEOF) {
    //     printf("%s '%s'\n", token_str(token), yytext);
    // }

    printf("-----------------------------------\n");
    yyparse ();
    printf ( "Parse Completed\n" );
    if ( errors == 0 ) {
        print_code ();
        fetch_execute_cycle();
    }

    return 0;
}
