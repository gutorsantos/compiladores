#ifndef PARSER_H
#define PARSER_H

#include "../symbol_table/symbol_table.h"
#include "../codegen/ast.h"
#include <stdio.h>

extern FILE* yyin;
extern unsigned int errors;

// static inline void report_errors();

typedef struct lbs{
    int for_goto;
    int for_jmp_false;
    struct lbs *next;
} lbs;

extern lbs *lbs_list;

lbs* newlbl();
void install(char* sym_name);
ASTNode* context_check(int operation, char* sym_name);
int yyparse();

// static inline void clear_label_list(lbs* ptr);
// static inline void parse_file(char file[]);


#endif