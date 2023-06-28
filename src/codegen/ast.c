#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    AST_PROGRAM,
    AST_DECLARATIONS,
    AST_COMMANDS,
    AST_SKIP,
    AST_READ,
    AST_WRITE,
    AST_ASSIGNMENT,
    AST_IF,
    AST_WHILE,
    AST_EXPRESSION,
    AST_INTEGER,
    AST_FLOAT,
    AST_IDENTIFIER,
    AST_BINARY_OPERATION
} ASTNodeType;

ASTNode* create_node(int type, char* value) {
    ASTNode* node = NULL;
    node = (ASTNode*) malloc(sizeof(ASTNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;

    if (type == AST_INTEGER) {
        node->value.intval = atoi(value); // Preencher com o valor adequado
    } else if (type == AST_FLOAT) {
        node->value.floatval = atof(value); // Preencher com o valor adequado
    } else {
        node->value.id = (char*) value; // Preencher com o valor adequado
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

    // switch (node->type) {
    //     case DECLARATION:
    //         printf("Declaration: %s\n", node->value.id);
    //         break;
    //     case COMMAND:
    //         printf("Commands:\n");
    //         print_ast(node->left, indent + 1);
    //         print_ast(node->right, indent + 1);
    //         break;
    //     case SKIP:
    //         print_indent(indent);
    //         printf("Skip\n");
    //         break;
    //     case READ:
    //         print_indent(indent);
    //         printf("Read: %s\n", node->value.id);
    //         break;
    //     case WRITE:
    //         print_indent(indent);
    //         printf("Write:\n");
    //         print_ast(node->left, indent + 1);
    //         break;
    //     case ASSGNOP:
    //         print_indent(indent);
    //         printf("Assign: %s\n", node->left->value.id);
    //         print_ast(node->right, indent + 1);
    //         break;
    //     case IF:
    //         print_indent(indent);
    //         printf("If:\n");
    //         print_ast(node->left, indent + 1);
    //         print_ast(node->right->left, indent + 1);
    //         print_ast(node->right->right, indent + 1);
    //         break;
    //     case WHILE:
    //         print_indent(indent);
    //         printf("While:\n");
    //         print_ast(node->left, indent + 1);
    //         print_ast(node->right, indent + 1);
    //         break;
    //     case NUMBER:
    //         print_indent(indent);
    //         printf("Number: %d\n", node->value.intval);
    //         break;
    // }
}