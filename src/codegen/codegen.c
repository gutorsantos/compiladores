#include "codegen.h"
#include <stdio.h>

int codegen(ASTNode *node, FILE *out) {
    if (!node) {
        return 0;
    }

    char* id;
    symrec* symbol;
    int var, temp_a, temp_b, block_label, else_label, done_label;

    switch (node->type) {
        case AST_PROGRAM:
            copy_template_to_file(out);
            codegen(node->left, out);
            codegen(node->right, out);
            make_data_section(out);
            break;
        case AST_DECLARATIONS:
            // Variáveis já são alocadas no parser.y
            break;
        case AST_COMMANDS:
            codegen(node->left, out); // commands (list)
            codegen(node->right, out); // command
            break;
        case AST_ASSIGNMENT: // x = ?
            id = node->value.id;
            symbol = getsym(id);
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
        case AST_IDENTIFIER: // x
            id = node->value.id;
            symbol = getsym(id);
            var = alloc_var();
            fprintf(out, "  # identifier: %s\n", id);
            fprintf(out, "  lw t0 %d(s11)\n", symbol->offset);
            fprintf(out, "  sw t0 %d(s11)\n\n", var);
            return var;
        case AST_NOT: // not expr
            // NOTE: var is not freed
            var = alloc_var();
            temp_a = codegen(node->left, out); // left
            fprintf(out, "  # expr := not left\n");
            fprintf(out, "  lw t0 %d(s11)\n", temp_a);
            fprintf(out, "  xori t0 t0 1\n");
            fprintf(out, "  sw t0 %d(s11)\n\n", var);
            free_var(temp_a);
            return var;
        case AST_BINARY_OPERATION: // left op right
            // NOTE: var is not freed
            var = alloc_var();
            temp_a = codegen(node->left, out); // left
            temp_b = codegen(node->right, out); // right
            fprintf(out, "  # expr := left op right\n");
            fprintf(out, "  lw t0 %d(s11)\n", temp_a);
            fprintf(out, "  lw t1 %d(s11)\n", temp_b);
            gen_binary_op(out, node->value.operation);
            fprintf(out, "  sw t2 %d(s11)\n\n", var);
            free_var(temp_a);
            free_var(temp_b);
            return var;
        case AST_READ:
            id = node->value.id;
            symbol = getsym(id);
            fprintf(out, "  # read(%s)\n", id);
            fprintf(out, "  read_int(t0)\n");
            fprintf(out, "  sw t0 %d(s11)\n\n", symbol->offset);
            break;
        case AST_IF:
            temp_a = codegen(node->value.exp, out); // expression
            else_label = label_count++;
            done_label = label_count++;
            fprintf(out, "  # if expr then A else B\n");
            fprintf(out, "  lw t0 %d(s11)\n", temp_a);
            fprintf(out, "  beqz t0 L%d\n\n", else_label);
            free_var(temp_a);
            codegen(node->left, out); // THEN commands
            fprintf(out, "  j L%d\n\n", done_label);
            fprintf(out, "L%d:\n\n", else_label);
            codegen(node->right, out); // ELSE commands
            fprintf(out, "L%d:\n\n", done_label);
            break;
        case AST_WHILE:
            block_label = label_count++;
            done_label = label_count++;
            fprintf(out, "  # while expr do A end\n");
            fprintf(out, "L%d:\n\n", block_label);
            temp_a = codegen(node->value.exp, out); // expression
            fprintf(out, "  lw t0 %d(s11)\n", temp_a);
            fprintf(out, "  beqz t0 L%d\n\n", done_label);
            free_var(temp_a);
            codegen(node->left, out); // commands
            fprintf(out, "  j L%d\n", block_label);
            fprintf(out, "L%d:\n\n", done_label);
            break;
        case AST_SKIP:
            fprintf(out, "  # skip\n");
            break;
        case AST_WRITE:            temp_a = codegen(node->value.exp, out); // expression
            temp_a = codegen(node->value.exp, out); // expression
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

void gen_binary_op(FILE *out, char op) {
    switch (op) {
        case '+':
            fprintf(out, "  add t2 t0 t1\n");
            break;
        case '-':
            fprintf(out, "  sub t2 t0 t1\n");
            break;
        case '*':
            fprintf(out, "  mul t2 t0 t1\n");
            break;
        case '/':
            fprintf(out, "  div t2 t0 t1\n");
            break;
        case '%':
            fprintf(out, "  rem t2 t0 t1\n");
            break;
        case '<':
            fprintf(out, "  slt t2 t0 t1\n");
            break;
        case '>':
            fprintf(out, "  slt t2 t1 t0\n");
            break;
        case '=':
            fprintf(out, "  sub t0 t0 t1\n");
            fprintf(out, "  seqz t2 t0\n");
            break;
        case '^':
            // TODO: isso é exponenciação?
            fprintf(out, "  xor t2 t0 t1\n");
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

    fclose(template);
}

void make_data_section(FILE *out) {
    fprintf(out, "\n.data\n");
    fprintf(out, "  variables: .space %d\n", var_len);
}
