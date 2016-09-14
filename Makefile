CC=clang++
CXXFLAGS=-std=c++14 -Wall -Werror -ggdb3 -O2
LINKFLAGS=-pthread
SOURCES=foo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=foo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LINKFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
