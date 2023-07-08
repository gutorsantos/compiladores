#include <stdio.h>
#include "../generated/lex.yy.h"
#include "../generated/y.tab.h"
#include "codegen/ast.h"
#include "codegen/codegen.h"
#include "parser/parser.h"

int main(int argc, char* argv[]) {
    yyin = fopen(argv[1], "r");
    printf("-----------------------------------\n");
    yyparse();
    printf ( "Parse Completed\n" );
    print_ast(root, 2);
    if (errors != 0) {
        printf("Erro encontrado na linha %d\n", errors);
        exit(1);
    }

    FILE* output = fopen("output.s", "w");
    codegen(root, output);
    fclose(output);

    return 0;
}
