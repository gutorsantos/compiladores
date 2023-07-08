#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int var;
    struct list *next;
} list;

extern int var_count;
extern list* free_vars;

int alloc_var();
void free_var(int x);

extern int label_count;

#endif
