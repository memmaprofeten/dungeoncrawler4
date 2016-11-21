LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
SOURCES=item.hpp main.cpp map.hpp monster.hpp room.cpp room.hpp tile.cpp tile.hpp weapon.hpp projectile.hpp projectile.cpp
OBJECTS=main.o room.o tile.o
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
