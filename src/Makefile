LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
SOURCES=*.cpp *.cpp *.hpp
OBJECTS=*.o
EXECUTABLE=dungeon
all: $(EXECUTABLE)

$(OBJECT): $(SOURCES)
	$(CC) $(CPPFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	@echo "**Building the game**"
	$(CC) $^ -o $@ $(LIBS) 
clean:
	@echo "**Removing object files and executable**"
	rm -f $(OBJECTS) $(EXECUTABLE)

run: dungeon
	./dungeon
