# Set compiler
CC = gcc

# Set binary name
ENCRYPTION_BIN = encrypt
DECRYPTION_BIN = decrypt

# Set directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin

# Set compilation flags for compiler
CFLAGS = -I$(INC_DIR)
#CPPFLAGS = -Wall -ggdb -Wno-unused-variable -Wno-sign-compare
CPPFLAGS = -Wall -ggdb
LDFLAGS = -lstdc++ -lm -lssl -lcrypto

# Specify the source and object files
ENCRYPTION_SRC := $(wildcard $(SRC_DIR)/project2_encryption.cpp)
DECRYPTION_SRC := $(wildcard $(SRC_DIR)/project2_decryption.cpp)

ENCRYPTION_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(ENCRYPTION_SRC))
DECRYPTION_OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(DECRYPTION_SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(ENCRYPTION_BIN):$(ENCRYPTION_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

$(DECRYPTION_BIN):$(DECRYPTION_OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

all: $(ENCRYPTION_BIN) $(DECRYPTION_BIN)

clean:
	rm -rf $(OBJ_DIR) 
	rm -rf $(BIN_DIR)
	rm -rf files/ciphertext.txt 
	rm -rf files/new_plain_text.txt 
	rm -rf files/signed_cipher 
	rm -rf files/symmetric.txt
