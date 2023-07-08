#include "codegen.h"
#include <stdio.h>

void codegen(ASTNode *node, FILE *out) {
    switch (node->type) {
        case AST_PROGRAM:
            copy_template_to_file(out);
            codegen(node->left, out);
            codegen(node->right, out);
            make_data_section(out);
            break;
        case AST_COMMANDS:

            break;
        default:
            fprintf(stderr, "[codegen] node->type <%d> não é um tipo válido.\n", node->type);
            break;
    }
}

void copy_template_to_file(FILE *out) {
    FILE *template = fopen("template.s", "r");
    if (!template) {
        fprintf(stderr, "Error: template.s não foi encontrado.\n");
        fprintf(stderr, "Certifique-se de que você está rodando o compilador no diretório que contém o arquivo ""template.s!\n");
        exit(1);
    }

    int size = sizeof(char) * 4096;
    char* buffer = malloc(size);
    while (fgets(buffer, size, template)) {
        fputs(buffer, out);
    }
    free(buffer);

    fputc('\n', out);
    fclose(template);
}

void make_data_section(FILE *out) {
    fprintf(stderr, "make_data_section is not implemented yet!\n");
}
