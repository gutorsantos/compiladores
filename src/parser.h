// #ifndef PARSER_H
// #define PARSER_H

// #include "symbol_table.h"
// #include <stdio.h>

// extern FILE* yyin;
// extern unsigned int errors;

// static inline void report_errors();

// typedef struct lbs {
//     int for_goto;
//     int for_jmp_false;
//     struct lbs* next;
// } lbs;

// extern lbs* lbs_list = NULL;

// static struct lbs* create_label();
// static inline void clear_label_list(lbs* ptr);
// static inline void install(char* sym_name);
// static inline void context_check(enum code_ops operation, char* sym_name);
// int yyparse();
// static inline void parse_file(char file[]);


// #endif
