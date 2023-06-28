#ifndef AST_H
#define AST_H

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

typedef union {
    int intval; // Valor inteiro
    float floatval; // Valor float
    char* stringval; // Valor string
    char* id; // Identificador
    char operation;
    struct ASTNode* exp;
} UnionTypes;

typedef struct ASTNode {
    int type; // Tipo do nó da AST (por exemplo, número, identificador, operação, etc.)
    UnionTypes value;
    struct ASTNode* left; // Filho esquerdo
    struct ASTNode* right; // Filho direito
} ASTNode;

ASTNode* create_node(int type, UnionTypes value);
void free_ast(ASTNode* node);
void print_indent(int indent);
void print_ast(ASTNode* node, int indent);

ASTNode* add_left_child(ASTNode* parent, ASTNode* child);
ASTNode* add_right_child(ASTNode* parent, ASTNode* child);
// ASTNode* add_child(ASTNode* parent, ASTNode* child);


extern ASTNode* root;
#endif