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
class Character;

class Room {
public:

	/**
	 * Constructor creating the room by loading it from the given file.
	 */
	Room(std::string const file, Character* character);

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
	 * Checks whether the room contains the given position (= not out of bounds).
	 */
	 bool hasPosition(sf::Vector2f pos);

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
	 * Updates the projectiles in the room and draws them.
	 */
	void drawProjectiles(sf::RenderWindow& window, float elapsed);

	/**
	 * Prints the room to std::cout.
	 */
	void print();

	//Returns refernce to a sprite that is not in use
	sf::Sprite* getSprite();

	//std::vector<Projectile> getProjectiles();

	/**
	 * Adds a projectile with the input parameters as constructor parameters
	 * to this room and returns the projectile index of this projectile in the
	 * Room's projectile buffer.
	 * NB! Always use this method to add a projectile - never use the Projectile
	 * class' explicit constructor! (This method will try to reactivate a
	 * deactivated projectile class in its projectile buffer and assign these
	 * parameters to it.)
	 */
	Projectile& createProjectile(bool shotbyplayer, int damagein, int radiusin, float speedin, int txtrIndex);

  std::vector<Monster*>& getmonsters();
  
private:
	int width;
	int height;
	Character* character;
	std::vector<std::vector<Tile>> room;	// 2D-array of tile-objects mapping the game room.
	std::vector<sf::Sprite> sprites;//all sprites used in the game
	std::vector<bool> spritesInUse;	//value telling if sprite is to bedrawn
	std::vector<Projectile> projectiles; //Projectile objects
	std::vector<int> freeProjectiles;		// A vector of projectile indices that are free for replacing
	std::vector<Monster*> monsters;
};

#endif
