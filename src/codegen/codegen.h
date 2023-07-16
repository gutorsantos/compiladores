#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "allocator.h"
#include "../symbol_table/symbol_table.h"

int codegen(ASTNode *root, FILE *out);
void gen_binary_op(FILE *out, char op);
void copy_template_to_file(FILE *out);
void make_data_section(FILE *out);

#endif
