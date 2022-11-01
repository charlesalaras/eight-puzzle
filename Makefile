CC=g++
DEBUG=-g
TARGET=prog
CFLAGS=-std=c++11

HEADERS= board.h node.h problem.h queue.h search.h
OBJECTS= main.o search.o

default: $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o $@

debug: $(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) -Wall -O0 -o $(TARGET)

clean:
	-rm -f *.o
	-rm -f $(TARGET)
