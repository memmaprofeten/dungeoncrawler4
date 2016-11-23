#include "tile.hpp"
#include <SFML/Graphics.hpp>
//Assigning the right parameters to Tile
Tile::Tile(int type, sf::Vector2f position, sf::Vector2i index){
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

void Tile::draw(sf::RenderWindow& window, float blockDim){
	if (!penetrable) {
		sf::RectangleShape block(sf::Vector2f(blockDim, blockDim));
		block.setPosition(tileIndex.x * blockDim, tileIndex.y * blockDim);
		block.setFillColor(sf::Color::Green);
		window.draw(block);
	}
}

std::string Tile::toString() const {
	if (penetrable) {
		return "0";
	} else {
		return "1";
	}
}
