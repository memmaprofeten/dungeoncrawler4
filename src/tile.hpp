#include <SFML/Color.hpp>
#include <SFML/Graphics>

/*For simplicity the tiles are either floor or wall*/
class Tile{
public:
/*
Simple constructor: is given char as parameter and returns a tile object
a couple tiles per room has some kind of item on them

bool isPenetrable; that returns if characters can walk over this tile*/

	Tile(int type, sf::Vector position);
	bool isPenetrable() const;
	drawTile(sf::RenderWindow window);
private:
/*boolean telling if the tile is penetrabble
Color of the tile
position in room
*/
	bool penetrable;
	sf::Color tileColor; 
	sf::Vector2f tilePosition;
};
