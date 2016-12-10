LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
SOURCES=item.cpp item.hpp main.cpp character.cpp character.hpp convenience.cpp convenience.hpp map.cpp map.hpp npc.cpp npc.hpp projectile.cpp projectile.hpp room.cpp room.hpp settings.cpp settings.hpp tile.cpp tile.hpp weapon.cpp weapon.hpp monster.cpp monster.hpp
OBJECTS=main.o character.o convenience.o  item.o map.o npc.o projectile.o room.o tile.o monster.o settings.o weapon.o
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
