#ifndef SCANNER_H
#define SCANNER_H

typedef struct {
    char *name;
    struct symrec *next;
} symrec;

extern struct symrec sym_table;

symrec * putsym(char *symbol_name);
symrec * getsym(char *symbol_name);


#endif
