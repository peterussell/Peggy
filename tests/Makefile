CXX:= g++
CPPFLAGS:= -c -g -IUnitTest++/src -I../
BIN:= peg-tests
DIRS:= . ../src/Game ../src/Core Game Core
SRC:= $(foreach I,$(DIRS),$(wildcard $(I)/*.cpp))
OBJ:= $(SRC:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ -lUnitTest++ -LUnitTest++

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ $< 

clean:
	rm -rf $(OBJ) $(BIN)
