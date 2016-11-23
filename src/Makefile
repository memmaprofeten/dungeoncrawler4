LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
SOURCES=item.hpp main.cpp character.cpp character.hpp convenience.cpp convenience.hpp map.hpp projectile.cpp projectile.hpp room.cpp room.hpp tile.cpp tile.hpp weapon.hpp
OBJECTS=main.o character.o convenience.o projectile.o room.o tile.o monster.o
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
