CFLAGS := -I/usr/local/include
LDFLAGS := -L/usr/local/lib -lsfml-system -lsfml-window -lsfml-graphics
COMMON := -O0 -g -Wall -Wextra -std=c++14
BIN := main

all: $(BIN)

$(BIN): main.o Makefile
	$(CXX) $< -o $@ $(LDFLAGS) $(COMMON)

%.o: %.cpp Makefile
	$(CXX) -c $< -o $@ $(CFLAGS) $(COMMON)

clean:
	@-rm -f $(BIN)
	@-rm -f *.o

run: $(BIN)
	./$(BIN)

.PHONY: all clean run
