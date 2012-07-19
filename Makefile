CC = g++
CFLAGS = -c -g
BIN = ./peg
SRC = $(shell find src -name *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -rf $(OBJ) $(BIN)

vg:
	valgrind --dsymutil=yes $(BIN)
