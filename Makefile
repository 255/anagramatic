CC=g++
CFLAGS=-c -std=c++11 -Wall
DEBUGFLAG=-DNDEBUG
LDFLAGS=
SOURCES=Dictionary.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Dictionary

all: $(SOURCES) $(EXECUTABLE)
    
debug: DEBUGFLAG=-DDEBUG
debug: clean all

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(DEBUGFLAG) $< -o $@

clean:
	rm -f $(EXECUTABLE)
	rm -f *.o
