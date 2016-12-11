#include "map.hpp"
#include "room.hpp"
#include "character.hpp"
#include <time.h>
#include <cmath>
#include <time.h>
#include "item.hpp"
#include "weapon.hpp"

Map::Map(Character& c) : room("welcome_room.txt", &c) {        // TODO: Replace with "welcome_room.txt"
    atRoom = s::startingRoomIndex;
    character = &c;
    roomMap.push_back(roomContainer { open,     true, "main_cave1.txt",             1, 2, 4, 5 });      // 0    (default room)
    roomMap.push_back(roomContainer { open,     true, "main_cave2.txt",             -1, 3, 0, -1 });    // 1
    roomMap.push_back(roomContainer { open,     true, "main_cave3.txt",             3, -1, -1, 0 });    // 2
    roomMap.push_back(roomContainer { open,     true, "main_cave4.txt",             -1, -1, 2, 1 });    // 3

    roomMap.push_back(roomContainer { open,     true, "welcome_room.txt",           0, -1, -1, -1 });   // 4

    roomMap.push_back(roomContainer { dungeon,  true, "",                           5, 0, 5, 5 });      // 5

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
    // TODO: Clean old room? Copy constructor?
    if (roomMap[atRoom].type == open) {
        room = Room(roomMap[atRoom].roomPath, character);
    } else {
        srand(time(NULL));
        float p = (float)(rand() % 1000) / 999.0f * 0.13f + 0.6f;
        std::cout << "Generating dungeon with p = " << p << "." << std::endl;
        room = Room(60, 60, p, 3, std::vector<bool>{true, true, true, true});
    }
    return room;
}

void Map::defineRooms() {
    // TODO: Define rooms
    return;
}
