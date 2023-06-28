#ifndef AST_H
#define AST_H

// enum node_type {
//     PROGRAM,
//     DECLARATION,
//     COMMANDS,
//     ID,
//     SKIP,
//     READ,
//     WRITE,
//     ASSIGN,
//     IF,
//     ELSE,
//     WHILE,
//     NUMBER,
//     NUMBER_FLOAT,
//     STRING
// };

typedef struct ASTNode {
    int type; // Tipo do nó da AST (por exemplo, número, identificador, operação, etc.)
    union {
        int intval; // Valor inteiro
        float floatval; // Valor float
        char* stringval; // Valor string
        char* id; // Identificador
    } value;
    struct ASTNode* left; // Filho esquerdo
    struct ASTNode* right; // Filho direito
} ASTNode;

ASTNode* create_node(int type, char* value);
void free_ast(ASTNode* node);
void print_indent(int indent);
void print_ast(ASTNode* node, int indent);

ASTNode* add_left_child(ASTNode* parent, ASTNode* child);
ASTNode* add_right_child(ASTNode* parent, ASTNode* child);

#endif