#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <token_str.h>

ASTNode* create_node(int type, void* value) {
    ASTNode* node = NULL;
    node = (ASTNode*) malloc(sizeof(ASTNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;

    if (type == NUMBER) {
        node->value.intval = *(int*) value; // Preencher com o valor adequado
    } else if (type == NUMBER_FLOAT) {
        node->value.floatval = *(double*) value; // Preencher com o valor adequado
    } else if (type == STRING) {
        node->value.stringval = (char*) value; // Preencher com o valor adequado
    } else {
        node->value.id = (char*) value; // Preencher com o valor adequado
    }

    return node;
}

void free_ast(ASTNode* node) {
    if (node == NULL)
        return;

    if (node->type == NUMBER || node->type == DECLARATION) {
        free(node->value.id);
    } else {
        freeAST(node->left);
        freeAST(node->right);
    }

    free(node);
}

ASTNode* add_left_child(ASTNode* parent, ASTNode* child) {
    if (parent != NULL && child != NULL)
        parent->left = child;

    return parent;
}

ASTNode* add_right_child(ASTNode* parent, ASTNode* child) {
    if (parent != NULL && child != NULL)
        parent->right = child;
        
    return parent;
}


void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

void print_ast(ASTNode* node, int indent) {
    if (node == NULL)
        return;

    switch (node->type) {
        case DECLARATION:
            printf("Declaration: %s\n", node->value.id);
            break;
        case COMMAND:
            printf("Commands:\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case SKIP:
            print_indent(indent);
            printf("Skip\n");
            break;
        case READ:
            print_indent(indent);
            printf("Read: %s\n", node->value.id);
            break;
        case WRITE:
            print_indent(indent);
            printf("Write:\n");
            print_ast(node->left, indent + 1);
            break;
        case ASSGNOP:
            print_indent(indent);
            printf("Assign: %s\n", node->left->value.id);
            print_ast(node->right, indent + 1);
            break;
        case IF:
            print_indent(indent);
            printf("If:\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right->left, indent + 1);
            print_ast(node->right->right, indent + 1);
            break;
        case WHILE:
            print_indent(indent);
            printf("While:\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case NUMBER:
            print_indent(indent);
            printf("Number: %d\n", node->value.intval);
            break;
    }
}