#include "symbol_table.h"

/** putsym to put an identifier into the table */
symrec * putsym(char *symbol_name) {
    symrec *node;
    node = (symrec *) malloc(sizeof(symrec));
    node->name = (char *) malloc(strlen(symbol_name)+1);
    strcpy(node->name, symbol_name);
    node->next = (symrec *) sym_table;
    sym_table = node;
    return node;
}

symrec * getsym(char *symbol_name) {
    symrec *node;

    for(node = sym_table; node != (symrec *)0; node = node->next) {
        if(strcmp(node->name, symbol_name) == 0)
            return node;
    }
    return 0;
}

symrec *identifier;
symrec *sym_table = (symrec *)0;