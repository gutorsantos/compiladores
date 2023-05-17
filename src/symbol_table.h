#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <code_generator.h>
typedef struct {
    char *name;
    int offset;
    struct symrec *next;
} symrec;

extern symrec *identifier;
extern symrec sym_table;

symrec * putsym(char *symbol_name);
symrec * getsym(char *symbol_name);


#endif
