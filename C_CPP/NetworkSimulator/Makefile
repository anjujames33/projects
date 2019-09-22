# Set compiler
CC = gcc

# Set binary name
BIN_NAME = network_simulator

# Set directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin

# Set compilation flags for compiler
CFLAGS = -I$(INC_DIR)
CPPFLAGS = -Wall -ggdb -Wno-unused-variable -Wno-sign-compare
LDFLAGS = -lstdc++ -lm

# Specify the source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BIN_NAME):$(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

all: $(BIN_NAME)

clean:
	rm -rf $(OBJ_DIR) 
	rm -rf $(BIN_DIR)
