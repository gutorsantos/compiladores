#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

ASTNode* root;

ASTNode* create_node(int type, UnionTypes value) {
    ASTNode* node = NULL;
    node = (ASTNode*) malloc(sizeof(ASTNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;

    if (type == AST_INTEGER) {
        node->value.intval = value.intval; // Preencher com o valor adequado
    } else if (type == AST_FLOAT) {
        node->value.floatval = value.floatval; // Preencher com o valor adequado
    } else if (type == AST_EXPRESSION) {
        node->value.exp = value.exp; // Preencher com o valor adequado
    }
    else {
        node->value.id = value.id; // Preencher com o valor adequado
    }

    return node;
}

void free_ast(ASTNode* node) {
    if (node == NULL)
        return;

    if (node->left != NULL) {
        free_ast(node->left);
    }
    
    if (node->right != NULL) {
        free_ast(node->right);
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
        case AST_PROGRAM:
            printf("Program: %s\n", node->value.id);
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case AST_DECLARATIONS:
            printf("Declaration: %s\n", node->value.id);
            print_indent(indent);
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case AST_COMMANDS:
            printf("Commands:\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case AST_SKIP:
            print_indent(indent);
            printf("Skip\n");
            break;
        case AST_READ:
            print_indent(indent);
            printf("Read: %s\n", node->value.id);
            break;
        case AST_WRITE:
            print_indent(indent);
            printf("Write:\n");
            print_ast(node->left, indent + 1);
            break;
        case AST_ASSIGNMENT:
            print_indent(indent);
            printf("Assign: %s\n", node->left->value.id);
            print_ast(node->right, indent + 1);
            break;
        case AST_IF:
            print_indent(indent);
            printf("If:\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right->left, indent + 1);
            print_ast(node->right->right, indent + 1);
            break;
        case AST_WHILE:
            print_indent(indent);
            printf("While:\n");
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case AST_INTEGER:
            print_indent(indent);
            printf("Number: %d\n", node->value.intval);
            break;
        case AST_IDENTIFIER:
            print_indent(indent);
            printf("Id: %s\n", node->value.id);
            break;
    }
}