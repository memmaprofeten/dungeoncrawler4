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

	Tile(int type, sf::Vector2f position, std::tuple<int,int> index);
	bool isPenetrable() const;
	void drawTile(sf::RenderWindow window);
	std::string toString() const;
private:
/*boolean telling if the tile is penetrabble
Color of the tile
position in room
*/
	TileType material;
	bool penetrable;
	sf::Color tileColor;
	sf::Vector2f tilePosition;
	std::tuple<int,int> tileIndex;
};
