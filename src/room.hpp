#ifndef ROOM_HH
#define ROOM_HH

#include "tile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "monster.hpp"

class Projectile;
class Character;
class Weapon;
class Npc;

class Room {
public:

	/**
	 * Constructor creating the room by loading it from the given file.
	 */
	Room(std::string const file, Character* character);

	/**
	 * Constructor creating a random generated room based on the given
	 * parameters.
	 */
	Room(int width, int height, float p, int randomGenIterations, std::vector<bool> entrances, Character* character);

	/**
	 * The Room destructor
	 */
	~Room();

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
	  * Returns a 2D vector describing in which direction(s) the given position
	  * is out of bounds. If the given position is still within bounds, the
	  * returned vector is the zero vector.
	  */
	 sf::Vector2i getOffsetDirection(sf::Vector2f pos);

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
	 * Performs an attack from the given position, in the given direction, with
	 * the given weapon. If friendly, the attack targets only monsters. If not,
	 * it targets only monsters.
	 */
	void performAttack(bool friendly, sf::Vector2f source, sf::Vector2f direction, const Weapon& weapon);

	/**
	 * Draws the room.
	 */
	void draw(sf::RenderWindow& window);

	/**
	 * Updates the projectiles in the room and draws them.
	 */
	void drawProjectiles(sf::RenderWindow& window, float elapsed);

	/**
	 * Calls the monster AI for each monster in this room and draws them.
	 */
	void drawmonsters(float elapsed, sf::RenderWindow& window);

	/**
	 * Calls any necessary frame calls for the NPCs in this room and draws them.
	 */
	void drawnpcs(sf::RenderWindow& window);

	/**
	 * Returns a reference to the vector containing pointers to all the NPCs in
	 * this room.
	 */
	std::vector<Npc*>& getNpcs();

	/**
	 * Draws the items on the ground.
	 */
	void drawitems(sf::RenderWindow& window);

	/**
	 * Adds an item to the ground.
	 */
	void additem(Item* newitem);

	/**
	 * Identifies if there is any item on the ground within reach from the
	 * the player. If one such item is found, it is picked up. Therefore, a
	 * maximum of 1 item can be picked up each frame.
	 */
	void checkDrops();

	/**
	 * Prints the room to std::cout.
	 */
	void print();

	/**
	 * Returns a 2D vector of booleans representing the room, where a 'true'
	 * value represents a non-penetrable cell and a 'false' value represents
	 * a penetrable cell.
	 */
	std::vector<std::vector<bool>> getPenetrabilityMap();

	/**
	 * Returns refernce to a sprite for the sprite resuse ecosystem.
	 */
	sf::Sprite* getSprite();

	/**
	 * Deactivates a sprite for other instances to use.
	 */
	void deactivateSprite(sf::Sprite* sprite);

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

	/**
	 * Returns a reference to the monster vector of the room, i.e., pointers to
	 * all the monsters that are currently in the room (active or inactive).
	 */
	std::vector<Monster*>& getmonsters();

	/**
	 * Returns a reference to the tile vector of the room, i.e. pointers to all
	 * the items that are currently on the ground in the room.
	 */
	std::vector<Item*>& getitems();

	/**
	 * Returns a pointer to the room's character.
	 */
	Character* getcharacter();

	/**
	 * Adds the given monster to the room.
	 */
	void addmonster(Monster* monsteri);

	/**
	 * Adds the given NPC to the room.
	 */
	void addNpc(Npc* npc);

private:
	int width;									// The room's width, in terms of cells (tiles)
	int height;									// The rooms' height, in terms of cells (tiles)
	Character* character;						// A pointer to the character
	std::vector<std::vector<Tile>> room;		// A 2D-array of tile-objects mapping the game room.
	std::vector<sf::Sprite> sprites;			// All sprites belonging to different objects in this room
	std::vector<bool> spritesInUse;				// A vector of flags telling if the sprite at that index is to be drawn
	std::vector<Projectile> projectiles;		// The rooms' projectiles
	std::vector<int> freeProjectiles;			// A vector of projectile indices that are free for replacement
	std::vector<Monster*> monsters;				// Vector containing pointers to monsters in the room
	std::vector<Npc*> npcs;						// Vector of NPC:s
	std::vector<Item*> itemstorage;				// Vector containing items in the room
};

#endif
