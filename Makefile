# Project
PROJECT := error
CC := gcc

# Dirs
BUILD_DIR := build
SRC_DIR := src
INC_DIR := include
TEST_DIR := test
OBJ_DIR := $(BUILD_DIR)/obj
DOC_DIR := doc
LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include
EXAMPLE_DIR := example

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC_PRIV := $(wildcard $(SRC_DIR)/*.h)
INC := $(INC_DIR)/$(PROJECT).h
TEST_MAIN := $(TEST_DIR)/test.c
TEST_EXE := $(BUILD_DIR)/test
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXAMPLE_MAIN := $(EXAMPLE_DIR)/example.c
EXAMPLE_EXE := $(BUILD_DIR)/example

# Rules
.PHONY: all debug test example clean install uninstall doc

all: CFLAGS := -O3 -march=native -flto
all: CPPFLAGS := -DNDEBUG
all: $(LIB_SO) $(LIB_A)

debug: $(LIB_SO) $(LIB_A)

test: CFLAGS := -Iinclude -Isrc
test: CC := bear -- clang
test: $(TEST_EXE)
	./$<

example: LDFLAGS := -L/usr/local/lib -lerror
example: $(EXAMPLE_EXE)
	./$<

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR) compile_commands.json

install:
	cp $(LIB_SO) $(LIB_INSTALL_DIR)
	cp $(LIB_A) $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

uninstall:
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_SO)))
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_A)))
	rm $(addprefix $(INC_INSTALL_DIR)/, $(notdir $(INC)))

doc:
	doxygen

$(LIB_SO): $(OBJ) | $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(LIB_A): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(TEST_EXE): $(TEST_MAIN) $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(EXAMPLE_EXE): $(EXAMPLE_MAIN) | $(BUILD_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_PRIV) $(INC) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@
