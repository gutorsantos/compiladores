#include "stack_machine.h"

char *op_name[] = {"halt", "store", "jmp_false", "goto", "data", "ld_int", "ld_var", "in_int", "out_int", "lt", "eq", "gt", "add", "sub", "mult", "div", "pwr" };

instruction code[999];
int stack[999];

int pc = 0;
instruction ir;
int ar = 0;
int top = 0;
char ch;

void fetch_execute_cycle() {
    // ?
}