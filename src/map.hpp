#ifndef MAP_HH
#define MAP_HH

#include <string>
#include <vector>
#include "room.hpp"

class Character;
class Item;
class Weapon;

enum RoomType {
	open,			// 'open' represents static, 'open world'-like rooms that the player might often return to. These rooms are typically less hostile and contain friendly NPCs, shops, quest givers or similar.
	dungeon			// 'dungeon' represent dynamic adventure rooms that do not require any preservation logic (often visited once and never returned to).
};

/* A struct that represents a room on an abstract scale.
 * The roomContainer struct describes some metadata about the room. In
 * particular, it describes the room's position on the map in terms of its
 * neighbouring rooms. A room can have a maximum of 4 neighbours (one per side)
 * and these are (ideally) accessed when the player walks out of bounds in
 * either of these four directions.
 * The container also holds a pointer to the Room object itself, if the room is
 * currently in use. Otherwise, it is simply used to represent the room even
 * when the room itself is not loaded.
 */
struct roomContainer {
	RoomType type;					// The type of the room
	bool active;					// Whether or not the room represented by this struct instance is currently in use (initialized)
	std::string roomPath;			// A path to the room file describing this room
	int neighbourEast;				// The index of the eastern neighbour (negative if no such neighbour exists)
	int neighbourSouth;				// The index of the southern neighbour (negative if no such neighbour exists)
	int neighbourWest;				// The index of the western neighbour (negative if no such neighbour exists)
	int neighbourNorth;				// The index of the northern neighbour (negative if no such neighbour exists)
};

class Map {
public:

	/* The Map constructor, which creates a map according to a predfined way.
	 */
	Map(Character& c);

	/* Returns a reference to the current room object.
	 */
	Room& getRoom();

	/* Switches to the room that is the ith neighbour of the current room, where
	 * i is defined by the 'neighbour' parameter. If the neighbour index is
	 * invalid for the current room, it selects a default room instead. The
	 * method then returns a reference to the new room.
	 * The neighbour indices are defined in the following way:
	 * 		- 0: east
	 * 		- 1: south
	 * 		- 2: west
	 * 		- 3: north
	 */
	Room& switchRoom(int neighbour);

private:
	std::vector<roomContainer> roomMap;	// A vector containing roomContainers representing all the rooms of the map
	int atRoom;							// The index of the room that the character is currently in
	Room room;							// The object itself of the current room
	Character* character;				// A pointer to the character

	/**
	 * Defines the topology of the map. NB! This function is to be called only once, by the constructor.
	 */
	void defineRooms();
};

#endif
