CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp bigint.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fibonacci

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
