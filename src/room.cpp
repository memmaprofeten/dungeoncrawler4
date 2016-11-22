#include "room.hpp"
#include <fstream>
#include <iostream>
#include <functional>

Room::Room(std::string const file) {
	int x = 0;
	int y = 0;
	width = 80;			// TODO: Find out the width from the map file!
	height = 60;		// TODO: Find out the height from the map file!
	std::string line;
	std::ifstream mapFile (file);
	if (mapFile.is_open()){
		std::vector<std::vector<Tile>> room2(80, std::vector<Tile>(60, Tile(0,sf::Vector2f(0,0), std::make_tuple (0,0))));
		room = room2;
		while(getline(mapFile, line)){
			x=0;
			for(unsigned int i = 0; i < line.size(); i++){
				getTile(x,y) = Tile((int)line[i]-48, sf::Vector2f(10*x,10*y), std::make_tuple (x,y));
				x++;
			}
			y++;
		}
		mapFile.close();
	} else {
		throw std::runtime_error(std::string("Could not find or open file '") + file + "'.");
	}

	/*
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
	*/
}

bool Room::hasCoordinate(int x, int y) {
	if (x < 0) {
		std::cout << "--x<0" << std::endl;
	}
	if (y < 0) {
		std::cout << "--y<0" << std::endl;
	}
	if (x >= width) {
		std::cout << "--x >= width" << std::endl;
	}
	if (y >= height) {
		std::cout << "--y >= height" << std::endl;
	}
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
