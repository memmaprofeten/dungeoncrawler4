#ifndef TILE_HH
#define TILE_HH
#include <SFML/Graphics.hpp>
#include <string>

/**
 * An enum defining the possible tile types.
 */
enum TileType{
	Floor,
	Wall
};

/**
 * The Tile class represents a cell in a room's grid.
 * A tile holds information about its texture, position and whether or not it
 * it can be walked on.
 */
class Tile{
public:

	/**
	 * Tile constructor
	 * Constructs a tile of the given type, at the given index in a Room grid
	 * and on the given position, using the the given sprite.
	 */
	Tile(int type, sf::Vector2f position, sf::Vector2i index, sf::Sprite* freeSprite);

	/**
	 * Returns whether or not entities can go through this tile.
	 */
	bool isPenetrable() const;

	/**
	 * Returns a string representation of the tile.
	 */
	std::string toString() const;

private:
	TileType material;				// The tile type of the tile
	bool penetrable;				// Whether or not the tile is penetrable
	sf::Vector2f tilePosition;		// The position of the tile
	sf::Vector2i tileIndex;			// The index of the tile in the room grid
	sf::Texture texture;			// The texture of the tile
	sf::Sprite* sprite;				// A pointer to the tile's sprite
	int textureIndex;				// The index of the tile's texture
};

#endif
