/** Projeto Final
 *  Autores: Enzo Yoshio Niho, Gustavo Rodrigues dos Santos, João Pedro Sadéri da Silva, Leonardo Alves Riether
 *  Matriculas: 19/0027304, 19/0014121, 17/0126021, 19/0032413
 *  Materia: Compiladores - Turma 1
 *  Ano: 2023 - 1o semestre 
 *  Data: 19/07/2023
 */

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
