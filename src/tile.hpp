#ifndef TILE_HH
#define TILE_HH
#include <SFML/Graphics.hpp>
#include <string>
enum TileType{
	Floor,
	Wall
};
/*For simplicity the tiles are either floor or wall*/
class Tile{
public:
/*
Simple constructor: is given char as parameter and returns a tile object
a couple tiles per room has some kind of item on them

bool isPenetrable; that returns if characters can walk over this tile*/

	Tile(int type, sf::Vector2f position, sf::Vector2i index, sf::Sprite* freeSprite);
	bool isPenetrable() const;
	void draw(sf::RenderWindow& window, float blockDim);
	std::string toString() const;
private:
/*boolean telling if the tile is penetrabble
Color of the tile
position in room
*/
	TileType material;
	bool penetrable;
	sf::Vector2f tilePosition;
	sf::Vector2i tileIndex;
	sf::Texture texture;
	sf::Sprite* sprite; //pointer to sprite
	int textureIndex;
};

#endif
