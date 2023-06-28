#include <stdio.h>
#include "../generated/lex.yy.h"
#include "../generated/y.tab.h"
#include "codegen/ast.h"
#include "parser/parser.h"


int main(int argc, char* argv[]) {
    yyin = fopen(argv[1], "r");
    printf("-----------------------------------\n");
    yyparse();
    printf ( "Parse Completed\n" );
    print_ast(root, 2);
    if ( errors == 0 ) {
        // print_code ();
        // fetch_execute_cycle();
    }


    return 0;
}