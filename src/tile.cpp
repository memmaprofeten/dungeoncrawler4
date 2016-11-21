#include "tile.hpp"
#include <SFML/Graphics.hpp>
//Assigning the right parameters to Tile
Tile::Tile(int type, sf::Vector2f position, std::tuple<int,int> index){
	switch(type){
		case 0 :
			tileColor = sf::Color::White;
			penetrable = true;
			material = Floor;
			break;
		case 1 :
			tileColor = sf::Color::Black;
			penetrable = false;
			material = Wall;
			break;
		}
	tilePosition = position;
	tileIndex = index;
}
//Returns if character can walk through tile
bool Tile::isPenetrable() const {
	return penetrable;
}

void Tile::drawTile(sf::RenderWindow window){
	sf::RectangleShape tile(sf::Vector2f(10,10));
	tile.setPosition(this->tilePosition.x, this->tilePosition.y);
	window.draw(tile);
}

std::string Tile::toString() const {
	if (penetrable) {
		return "0";
	} else {
		return "1";
	}
}
