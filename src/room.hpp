#include "tile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdexcept>

class Room {
public:

	/**
	 * Constructor creating the room by loading it from the given file.
	 */
	Room(std::string const file);

	/**
	 * Checks whether the room contains the coordinates at (x, y) (= not out of bounds).
	 */
	bool hasCoordinate(int x, int y);

	/**
	 * Returns a reference to the tile at coordinates (x, y).
	 * If (x, y) are invalid coordinates, an error is thrown.
	 */
	Tile& getTile(int x, int y);

	/**
	 * Returns a vector of neighbour coordinates to teh coordinate at (x, y).
	 * If 'includingSelf' is true, the original coordinate is included.
	 * If 'includingDiagonals' is true, the diagonal neighbours are included.
	 * If 'includingOutsiders' is true, such neighbours that are out of bounds are included.
	 */
	std::vector<sf::Vector2i> getNeighbours(int x, int y, bool includingSelf, bool includingDiagonals, bool includingOutsiders);

	/**
	 * Draws the room.
	 */
	void draw(sf::RenderWindow& window, float blockDim);

	/**
	 * Prints the room to std::cout.
	 */
	void print();

private:
	int width;
	int height;
	std::vector<std::vector<Tile>> room;	// 2D-array of tile-objects mapping the game room.
};
