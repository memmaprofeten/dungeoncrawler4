#include "map.hpp"
#include "room.hpp"
#include "character.hpp"
#include <time.h>
#include <cmath>
#include <time.h>
#include "item.hpp"
#include "weapon.hpp"

Map::Map(Character& c) : room("welcome_room.txt", &c) {
    atRoom = s::startingRoomIndex;
    character = &c;
    defineRooms();
}

void Map::defineRooms() {
    roomMap.push_back(roomContainer { open,     true, "main_cave1.txt",             1,  2,  4,  5 });       // 0    (default room)
    roomMap.push_back(roomContainer { open,     true, "main_cave2.txt",             -1, 3,  0,  -1 });      // 1    (friendly room, not currently in use)
    roomMap.push_back(roomContainer { open,     true, "main_cave3.txt",             3,  -1, -1, 0 });       // 2    (friendly room, not currently in use)
    roomMap.push_back(roomContainer { open,     true, "main_cave4.txt",             -1, -1, 2,  1 });       // 3    (friendly room, not currently in use)
    roomMap.push_back(roomContainer { open,     true, "welcome_room.txt",           0,  0,  -1, -1 });      // 4    (welcome room)
    roomMap.push_back(roomContainer { dungeon,  true, "",                           5,  0,  5,  5 });       // 5    (random dungeon)
}

Room& Map::getRoom() {
    return room;
}

Room& Map::switchRoom(int neighbour) {
    roomContainer& currentRoom = roomMap[atRoom];
    int newRoomIndex;
    switch (neighbour) {
        case 0:
            newRoomIndex = currentRoom.neighbourEast;
            break;
        case 1:
            newRoomIndex = currentRoom.neighbourSouth;
            break;
        case 2:
            newRoomIndex = currentRoom.neighbourWest;
            break;
        case 3:
            newRoomIndex = currentRoom.neighbourNorth;
            break;
        default:
            newRoomIndex = -1;
            break;
    }
    if (newRoomIndex < 0) newRoomIndex = 0;
    currentRoom.active = false;
    atRoom = newRoomIndex;
    roomMap[atRoom].active = true;
    if (roomMap[atRoom].type == open) {     // Load static (open) room from file
        room = Room(roomMap[atRoom].roomPath, character);
    } else {                                // Generate a random dungeon room
        float p = (float)(rand() % 1000) / 999.0f * 0.13f + 0.6f;
        std::cout << "Generating dungeon with p = " << p << "." << std::endl;
        room = Room(60, 60, p, 3, std::vector<bool>{
                roomMap[atRoom].neighbourEast >= 0,
                roomMap[atRoom].neighbourSouth >= 0,
                roomMap[atRoom].neighbourWest >= 0,
                roomMap[atRoom].neighbourNorth >= 0
            }, character);
    }
    if (roomMap[atRoom].type == dungeon) {
    	for (int i=0; i < s::monstersPerRoom; i++){
    		bool found = false;
    		sf::Vector2f position;
    		// Iterate to find a free place in the room:
    		while(!found){
                position = sf::Vector2f((float) (rand() % ((room.getWidth() - 1) * (int) s::blockDim)) + 0.5f * s::blockDim, (float) (rand() % ((room.getHeight() - 1) * (int) s::blockDim)) + 0.5f * s::blockDim);
                if(room.getTile(position).isPenetrable()){
    				found = true;
    				// Create a random monster:
    				if(rand() % 2 == 0){
    					room.addmonster(new MeleeMonster(position, &room, character->getlevel()));
    				}
    				else {
    					room.addmonster(new RangedMonster(position, &room, character->getlevel()));
    				}
    			}
    		}
    	}
    }
    return room;
}
