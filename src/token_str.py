"""
    Generates a token_str function in a header file (token_str.h)
    based on the contents of the input file (should be src/parser.y)
"""

def generate_tokens():
    with open("src/parser.y", "r") as f:
        for line in f:
            prefix = "%token "
            if line.startswith(prefix):
                token = line[len(prefix):].strip()
                yield token

print("""\
#ifndef TOKEN_STR_H
#define TOKEN_STR_H

#include "y.tab.h"

static inline const char* token_str(int token) {
    switch (token) {"""\
)

for token in generate_tokens():
    print(f"        case {token}: return \"{token}\";")

print("""\
        default: return \"<UNKNOWN>\";
    }
}

#endif
""")

