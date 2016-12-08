#include "map.hpp"
#include "room.hpp"
#include "character.hpp"

Map::Map(Character& c) : room("start.txt", &c) {
    atRoom = 0;
    character = &c;
    roomMap.push_back(roomContainer { open,     true, "start.txt",                  1, -1, -1, -1 });   // 0
    roomMap.push_back(roomContainer { open,     false, "tutorial_dungeon.txt",      -1, -1, 0, -1 });   // 1
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
    room = Room(roomMap[atRoom].roomPath, character);
    return room;
}

void Map::defineRooms() {
    // TODO: Define rooms
    return;
}
