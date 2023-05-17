#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <stack_machine.h>

extern int data_offeset;
extern int code_offset;

int data_location();
int gen_label();
int reserve_loc();

void gen_code(enum code_ops operation, int arg);
void back_patch(int addr, enum code_ops operation, int arg);
void print_code();

#endif
