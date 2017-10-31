CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic -std=c++11 -g
EXEC = bin/rshell
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	mkdir -p bin 		
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@ 

clean:
	rm -f $(EXEC) $(OBJECTS)
	rmdir bin
