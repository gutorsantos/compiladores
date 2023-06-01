#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

// todo: RISC V instructions
enum code_ops { HALT, STORE, JMP_FALSE, GOTO, DATA, LD_INT, LD_VAR, READ_INT, WRITE_INT, LT, EQ, GT, ADD, SUB, MULT, DIV, PWR };
char *op_name[] = {"halt", "store", "jmp_false", "goto", "data", "ld_int", "ld_var", "in_int", "out_int", "lt", "eq", "gt", "add", "sub", "mult", "div", "pwr" };

struct instruction {
    enum code_ops op;
    int arg;
};
struct instruction code[999];

extern int data_offset;
extern int code_offset;

int data_location();
int gen_label();
int reserve_loc();

void gen_code(enum code_ops operation, int arg);
void back_patch(int addr, enum code_ops operation, int arg);
void print_code();

#endif
