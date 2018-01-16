SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
CFLAGS := -Iinclude -I/usr/local/include
LDFLAGS := -L/usr/local/lib -lsfml-system -lsfml-window -lsfml-graphics
COMMON := -O2 -g -Wall -Wextra -std=c++14
BIN := main

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS) $(COMMON)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) $(COMMON)

clean:
	@-rm -f $(BIN)
	@-rm -f src/*.o

run: $(BIN)
	./$(BIN)

.PHONY: all clean run
