mkdir -p generated
bison -dv --header=generated/y.tab.h -o generated/y.tab.c src/parser.y
flex  --header-file=generated/lex.yy.h -o generated/lex.yy.c src/lexer.l

gcc generated/lex.yy.c generated/y.tab.c src/codegen/ast.c src/parser/parser.c src/symbol_table/symbol_table.c src/main.c -o compiler
