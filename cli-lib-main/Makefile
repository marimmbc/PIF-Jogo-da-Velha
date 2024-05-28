# Variables
CC=gcc
CFLAGS=-Iinclude -Wall
LDFLAGS=
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

# Executable Name
EXEC=$(BIN_DIR)/jogo_da_velha

# Source and Object Files
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(EXEC)

$(EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Object files dependencies
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
