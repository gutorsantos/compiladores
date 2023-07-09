#include "codegen.h"
#include <stdio.h>

int codegen(ASTNode *node, FILE *out) {
    if (!node) {
        fprintf(stderr, "\x1b[93mWARNING:\x1b[0m found null node\n");
        return 0;
    }

    char* id;
    symrec* symbol;

    switch (node->type) {
        case AST_PROGRAM:
            copy_template_to_file(out);
            fprintf(out, "  # s11 é o ponteiro de variáveis e não deve ser alterado\n");
            fprintf(out, "  la s11 variables\n\n");
            codegen(node->left, out);
            codegen(node->right, out);
            make_data_section(out);
            break;
        case AST_DECLARATIONS:
            break;
        case AST_COMMANDS:
            codegen(node->left, out); // commands (list)
            codegen(node->right, out); // command
            break;
        case AST_ASSIGNMENT:
            id = node->value.id;
            symbol = getsym(id);
            fprintf(stderr, "\x1b[94m[codegen]\x1b[0m assignment: %s\n", id);
            int result = codegen(node->right, out); // expression
            fprintf(out, "  lw t0 %d(s11)\n", result);
            fprintf(out, "  sw t0 %d(s11)\n", symbol->offset);
            break;
        default:
            fprintf(stderr, "\x1b[94m[codegen]\x1b[0m node->type <%s> não é um tipo válido.\n", ASTNodeTypeNames[node->type]);
            break;
    }

    return 0;
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

    fclose(template);
}

void make_data_section(FILE *out) {
    fprintf(out, "\n.data\n");
    fprintf(out, "  variables: .space %d\n", var_len);
}
