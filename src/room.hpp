#include <tile.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
class Room {
public:
/*Constructor creating room from an array of strings.
*/
	Room(std::string const file);
	draw(sf::RenderWindow window);
private:
/*2D-array of tile-objects mapping the game room.*/
	std::vector<std::vector<Tile>> room;	
};
