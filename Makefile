TARGET_EXEC := compiler

BUILD_DIR := ./build
GEN       := ./generated
SRC_DIRS  := ./src

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
INC_DIRS := $(shell find $(SRC_DIRS) -type d) ./ $(GEN)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
# CPPFLAGS := $(INC_FLAGS) -MMD -MP -Wall -I./
CFLAGS   := $(INC_FLAGS) -Wall

# Linking flags
# -lfl: links flex
LDFLAGS := -lfl

LEX     := flex
YACC    := yacc -d

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(GEN)/y.tab.c $(GEN)/lex.yy.c
	$(CC) $(OBJS) $(GEN)/y.tab.c $(GEN)/lex.yy.c -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c $(GEN)/y.tab.h $(GEN)/lex.yy.h $(GEN)/token_str.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build step for flex
$(GEN)/lex.yy.c $(GEN)/lex.yy.h: src/lexer.l
	mkdir -p $(dir $@)
	$(LEX) -o $(GEN)/lex.yy.c --header-file=$(GEN)/lex.yy.h $<

# Build step for yacc
$(GEN)/y.tab.c $(GEN)/y.tab.h: src/parser.y
	mkdir -p $(dir $@)
	$(YACC) -o $(GEN)/y.tab.c -H $<

# Build step for token_str
$(GEN)/token_str.h: src/token_str.py src/parser.y
	mkdir -p $(dir $@)
	python3 $< > $@

# # Build step for C++ source
# $(BUILD_DIR)/%.cpp.o: %.cpp
# 	mkdir -p $(dir $@)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(GEN)

run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC)

-include $(DEPS)
