#include <tile.hpp>
#include <SFML/Graphics.hpp>
//Assigning the right parameters to Tile
Tile::Tile(int type, sf::Vector2f position){
	switch(type){
		case '0' :
			tileColor = White;
			penetrable = true;
			break;
		case '1' :
			tileColor = Black;
			penetrable = false;
			break;
		}
	tilePosition = 
};
//Returns if character can walk through tile 
bool Tile::isPenetrable() const {
	return penetrable;
};

void Tile::draw(sf::RenderWindow window){
	sf::RectangleShape tile(sf::Vector2f(10,10));
	tile.setposition(this.tileposition.x, this.tilePosition.y);
	window.draw(tile);
};			
