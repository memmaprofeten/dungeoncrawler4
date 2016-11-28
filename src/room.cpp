#include "room.hpp"
#include "settings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "settings.hpp"
Room::Room(std::string const file) {
	int x = 0;
	int y = 0;
	std::string line;
	std::ifstream mapFile (file);
	if (mapFile.is_open()){
		getline(mapFile, line);
		std::istringstream iss(line);
		iss >> width >> height;
		room = std::vector<std::vector<Tile>>(width, std::vector<Tile>(height, Tile(0,sf::Vector2f(0,0), sf::Vector2i(0,0))));
		while(getline(mapFile, line)){
			x=0;
			for(unsigned int i = 0; i < line.size(); i++){
				getTile(x,y) = Tile((int)line[i]-48, sf::Vector2f(s::blockDim*x,s::blockDim*y), sf::Vector2i(x,y));		// TODO: Define the block dimensions properly
				x++;
			}
			y++;
		}
		mapFile.close();
	} else {
		throw std::runtime_error(std::string("Could not find or open file '") + file + "'.");
	}
}

int Room::getWidth() const {
	return width;
}

int Room::getHeight() const {
	return height;
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
    throw std::runtime_error(std::string("The coordinates (") + std::to_string(x) + ", " + std::to_string(y) + ") are out of bounds!");
}

Tile& Room::getTile(sf::Vector2f pos) {
	return getTile((int)pos.x / s::blockDim, (int)pos.y / s::blockDim);
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

void Room::draw(sf::RenderWindow& window, float blockDim) {
	for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
			getTile(i, j).draw(window, blockDim);
        }
    }
}

void Room::print() {
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            std::cout << getTile(i, j).toString() << " ";
        }
        std::cout << std::endl;
    }
}
