CC          = g++
LD          = g++ 
CFLAG       = -Wall

SRC_DIR     = ./src/2023
BIN_DIR     = ./bin

all: $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(wildcard $(SRC_DIR)/*.cpp))

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CC) -g $(CFLAG) $< -o $@

clean:
	rm -f $(BIN_DIR)/*