#include "allocator.h"

int var_len = 0;
list* free_vars = NULL;

// L0:, L1:, L2:, ...
int label_count = 0;

int alloc_var() {
    if (free_vars == NULL) {
        // no free variables, let's create a new one
        int var = var_len;
        var_len += 4;
        return var;
    }

    list* head = free_vars;
    free_vars = free_vars->next;
    int var = head->var;
    free(head);
    return var;
}

void free_var(int x) {
    list* new_head = malloc(sizeof(list));
    new_head->var = x;
    new_head->next = free_vars;
    free_vars = new_head;
}
 
