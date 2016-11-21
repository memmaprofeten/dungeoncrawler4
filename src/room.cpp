#include "room.hpp"

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

bool Room::hasCoordinate(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return false;
    }
    return true;
}

Tile& Room::getTile(int x, int y) {
    if (hasCoordinate(x, y)) {
        return room[x][y];
    }
    throw std::runtime_error("The coordinates are out of bounds!");
}

std::vector<sf::Vector2i> Room::getNeighbours(int x, int y, bool includingSelf, bool includingDiagonals, bool includingOutsiders) {
    std::vector<sf::Vector2i> res;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if ((includingSelf || !(dx == 0 && dy == 0)) &&          // Check if this neighbour is the original coordinate
                (includingDiagonals || dx == 0 || dy == 0) &&       // Check if this neighbour is a diagonal neighbour
                (includingOutsiders || (dx >= 0 && dy >= 0 && dx < width && dy < height))   // Check if this neighbour is out of bounds
            ) {
                res.push_back(sf::Vector2i(x + dx, y + dy));
            }
        }
    }
    return res;
}

void Room::print() {
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            std::cout << getTile(i, j).toString() << " ";
        }
        std::cout << std::endl;
    }
}
