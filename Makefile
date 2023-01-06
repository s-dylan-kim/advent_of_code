CC          = g++
LD          = g++ 
CFLAG       = -Wall

SRC_DIR     = ./src
BIN_DIR     = ./bin

all: $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(wildcard $(SRC_DIR)/*.cpp))

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAG) $< -o $@

clean:
	rm -f $(BIN_DIR)/*