#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <string.h>

typedef struct symrec{
    char *name;
    struct symrec *next;
} symrec;

extern symrec *identifier;
extern symrec *sym_table;

symrec * putsym(char *symbol_name);
symrec * getsym(char *symbol_name);


#endif