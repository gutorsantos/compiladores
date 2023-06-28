#include "parser.h"

unsigned int errors;
lbs *lbs_list = NULL;

lbs * newlbl() {
    return (lbs *) malloc(sizeof(lbs));
}

void install(char *sym_name) {
    symrec *s;
    s = getsym(sym_name);
    
    if(s == 0)
        s = putsym(sym_name);
    else {
        errors++;
        printf("%s ja esta definido\n", sym_name);
    }
}

void context_check(int operation, char* sym_name) {
    symrec *identifier;
    identifier = getsym(sym_name);

    if(identifier == 0) {
        errors++;
        printf("%s nao esta declarado", sym_name);
    }
    // else
    //     gen_code(operation, identifier->offset);
}