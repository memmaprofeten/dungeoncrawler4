#include "map.hpp"
#include "room.hpp"
#include "character.hpp"

Map::Map(Character& c) : room("../resources/rooms/start.txt", &c) {
    atRoom = 0;
    character = &c;
    roomMap.push_back(roomContainer { open, false, "test", -1, 1, -1, -1 });
}

Room& Map::getRoom() {
    return room;
}

Room& Map::switchRoom(int neighbour) {
    (void)neighbour;
    // TODO: Find the correct room
    return room;
}

void Map::defineRooms() {
    // TODO: Define rooms
    return;
}
