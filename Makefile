CC=g++
CFLAGS=-c -std=c++11 -Wall
DEBUGFLAG=-DNDEBUG -O3
LDFLAGS=
SOURCES=Dictionary.cpp Anagramatic.cpp CharCounter.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Anagramatic

all: $(SOURCES) $(EXECUTABLE)
    
debug: DEBUGFLAG=-DDEBUG -g
debug: clean all

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) -MMD $(CFLAGS) $(DEBUGFLAG) $< -o $@

-include *.d

clean:
	rm -f $(EXECUTABLE)
	rm -f *.o *.d
