#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

void codegen(ASTNode *root, FILE *out);
void copy_template_to_file(FILE *out);
void make_data_section(FILE *out);

#endif
