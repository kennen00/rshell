CC=g++
CFLAGS=-Wall -Werror -pedantic -std=c++11
EXEC=bin/rshell
SOURCE=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

%.o: %.cpp
	$(CC) -c $(CFLAGS) 

clean:
	rm -f $(EXEC) $(OBJECTS)
