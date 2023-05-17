// #include <parser.h>

// static unsigned int errors = 0;

// static inline void report_errors() {
//     if (!errors)
//         printf("Nenhum erro encontrado\n");

//     else
//     {
//         printf("%d erro(s) encontrado(s)\n", errors);
//         exit(1);
//     }
// }

// static lbs* lbs_list = NULL;

// static struct lbs* create_label() {
//     lbs* ptr = (struct lbs *) malloc(sizeof(struct lbs));
//     ptr->next = lbs_list;
//     lbs_list = ptr;
    
//     return ptr;
// }

// // Esvazia a lista de labels
// static inline void clear_label_list(lbs* ptr) {
//     if (ptr == NULL) return;

//     clear_label_list(ptr->next);
//     free(ptr);
// } 

// // Insere um identificador na tabela de simbolos
// static inline void install(char* sym_name) { 
//     symrec* s;
//     s = getsym(sym_name);
//     if (s == 0) s = putsym(sym_name);
//     else {
//         errors++;
//         printf("Erro: variavel '%s' ja esta definida\n", sym_name);
//         report_errors();
//     }
// }

// // Checagem de contexto
// static inline void context_check(enum code_ops operation, char* sym_name) {
//     symrec* identifier = getsym(sym_name);
//     if (identifier == 0) {
//         errors++;
//         printf("Erro: variavel '%s' nao foi declarada\n", sym_name);
//         report_errors();
//     }
//     else gen_code(operation, (struct stack_t) {.intval = identifier->offset});
// }



// // Abre e faz parse no arquivo fornecido
// static inline void parse_file(char file[]) {
 
//     yyin = fopen(file, "r");
 
//     if (yyin == NULL) {
//         printf("Não foi possível abrir o arquivo\n");
//         exit(1);
//     }
    
//     yyparse();

//     fclose(yyin);
// }