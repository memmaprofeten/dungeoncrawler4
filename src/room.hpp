#ifndef ROOM_HH
#define ROOM_HH


#include "tile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdexcept>
#include "monster.hpp"
class Projectile;
class Room {
public:

	/**
	 * Constructor creating the room by loading it from the given file.
	 */
	Room(std::string const file);

	/**
	 * Returns the width of the room (in blocks)
	 */
	int getWidth() const;

	/**
	 * Returns the height of the room (in blocks)
	 */
	int getHeight() const;

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
	 * Returns a reference to the tile at position pos.
	 * If pos is out of bounds, an error is thrown.
	 */
	Tile& getTile(sf::Vector2f pos);

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
	void draw(sf::RenderWindow& window);

	/**
	 * Prints the room to std::cout.
	 */
	void print();

	//Returns refernce to a sprite that is not in use
	sf::Sprite* getSprite();

	
private:
	int width;
	int height;
	std::vector<std::vector<Tile>> room;	// 2D-array of tile-objects mapping the game room.
	std::vector<sf::Sprite> sprites;//all sprites used in the game
	std::vector<bool> spritesInUse;	//value telling if sprite is to bedrawn
	std::vector<Projectile> projectiles; //Projectile objects, 
	std::vector<Monster> monsters;
};

#endif
