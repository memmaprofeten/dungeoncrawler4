#include "room.hpp"
#include <string>
#include <iostream>

Room::Room(std::string const file) {
    (void)file; // TODO: Parse and load file
    std::cout << "test" << std::endl;
    std::vector<Tile> temp;
    temp.push_back(Tile(1, sf::Vector2<int>(0,0)));
    temp.push_back(Tile(0, sf::Vector2<int>(0,1)));
    temp.push_back(Tile(0, sf::Vector2<int>(0,2)));
    room.push_back(temp);
    temp.clear();
    temp.push_back(Tile(1, sf::Vector2<int>(1,0)));
    temp.push_back(Tile(1, sf::Vector2<int>(1,1)));
    temp.push_back(Tile(0, sf::Vector2<int>(1,2)));
    room.push_back(temp);
    temp.clear();
    temp.push_back(Tile(0, sf::Vector2<int>(2,0)));
    temp.push_back(Tile(1, sf::Vector2<int>(2,1)));
    temp.push_back(Tile(0, sf::Vector2<int>(2,2)));
    room.push_back(temp);
    temp.clear();
    width = 3;
    height = 3;
}

Tile& Room::getTile(int x, int y) {
    // TODO: Check bounds
    return room[x][y];
}

void Room::print() {
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            std::cout << getTile(i, j).toString() << " ";
        }
        std::cout << std::endl;
    }
}
