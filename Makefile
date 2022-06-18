CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -g -O2
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
BIN = game

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS) $(LFLAGS)
	
%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
	
run: $(BIN)
	./$(BIN)
	
clean:
	rm -rf $(BIN) $(OBJS)
