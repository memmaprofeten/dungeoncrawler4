#include "tile.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class Room {
public:
/*Constructor creating room from an array of strings.
*/
	Room(std::string const file);
	Tile& getTile(int x, int y);
	void draw(sf::RenderWindow window);
	void print();
private:
/*2D-array of tile-objects mapping the game room.*/
	int width;
	int height;
	std::vector<std::vector<Tile>> room;
};
