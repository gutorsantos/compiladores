#ifndef STACK_MACHINE_H
#define STACK_MACHINE_H

#include <stdio.h>

enum code_ops { HALT, STORE, JMP_FALSE, GOTO, DATA, LD_INT, LD_VAR, READ_INT, WRITE_INT, LT, EQ, GT, ADD, SUB, MULT, DIV, PWR };

extern char *op_name[];

typedef struct {
    enum code_ops op;
    int arg;
} instruction;

extern instruction code[999];
extern int stack[999];

extern int pc;
extern instruction ir;
extern int ar;
extern int top;
extern char ch;

void fetch_execute_cycle();

#endif