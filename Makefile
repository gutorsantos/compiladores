TARGET_EXEC := compiler

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
# CPPFLAGS := $(INC_FLAGS) -MMD -MP -Wall -I./
CFLAGS   := $(INC_FLAGS) -Wall -I./

# Linking flags
# -lfl: links flex
LDFLAGS := -lfl

LEX     := flex
YACC    := yacc -d

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) y.tab.c lex.yy.c
	$(CC) $(OBJS) y.tab.c lex.yy.c -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c y.tab.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build step for flex
lex.yy.c: src/lexer.l
	$(LEX) src/lexer.l

# Build step for yacc
y.tab.c y.tab.h: src/parser.y
	$(YACC) src/parser.y

# # Build step for C++ source
# $(BUILD_DIR)/%.cpp.o: %.cpp
# 	mkdir -p $(dir $@)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f lex.yy.c y.tab.c y.tab.h

-include $(DEPS)
