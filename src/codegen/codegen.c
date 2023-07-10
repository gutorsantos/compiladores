#include "codegen.h"
#include <stdio.h>

int codegen(ASTNode *node, FILE *out) {
    if (!node) {
        fprintf(stderr, "\x1b[93mWARNING:\x1b[0m found null node\n");
        return 0;
    }

    char* id;
    symrec* symbol;
    int var, temp_a, temp_b;

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
        case AST_ASSIGNMENT: // x = ?
            id = node->value.id;
            symbol = getsym(id);
            fprintf(stderr, "\x1b[94m[codegen]\x1b[0m assignment: %s\n", id);
            temp_a = codegen(node->right, out); // expression
            fprintf(out, "  # x := expr\n");
            fprintf(out, "  lw t0 %d(s11)\n", temp_a);
            fprintf(out, "  sw t0 %d(s11)\n\n", symbol->offset);
            free_var(temp_a);
            break;
        case AST_INTEGER: // 1234
            // NOTE: var is not freed
            var = alloc_var();
            fprintf(out, "  # integer: %d\n", node->value.intval);
            fprintf(out, "  li t0 %d\n", node->value.intval);
            fprintf(out, "  sw t0 %d(s11)\n\n", var);
            return var;
        case AST_BINARY_OPERATION: // left op right
            // TODO: implement other binary operations
            // NOTE: var is not freed
            var = alloc_var();
            temp_a = codegen(node->left, out); // left
            temp_b = codegen(node->right, out); // right
            fprintf(out, "  # expr := left op right\n");
            fprintf(out, "  lw t0 %d(s11)\n", temp_a);
            fprintf(out, "  lw t1 %d(s11)\n", temp_b);
            fprintf(out, "  add t2 t0 t1 # +\n");
            fprintf(out, "  sw t2 %d(s11)\n\n", var);
            free_var(temp_a);
            free_var(temp_b);
            return var;
        case AST_WRITE:
            temp_a = codegen(node->left, out); // expression
            fprintf(out, "  # write(expr)\n");
            fprintf(out, "  lw t0 %d(s11)\n", temp_a);
            fprintf(out, "  print_int(t0)\n\n");
            free_var(temp_a);
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
