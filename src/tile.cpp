#include "tile.hpp"
#include <SFML/Graphics.hpp>
//Assigning the right parameters to Tile
Tile::Tile(int type, sf::Vector2f position, sf::Vector2i index){
	switch(type){
		case 0 :
			if(!texture.loadFromFile("../resources/img/floor_32_2.png")){
				throw std::runtime_error("Could not load floor sprite.");
			}
			penetrable = true;
			material = Floor;
			break;
		case 1 :
			if(!texture.loadFromFile("../resources/img/wall_32.png")){
				throw std::runtime_error("Could not load wall sprite.");
			} 
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
//	if (material == Wall) {
/*
		sf::RectangleShape block(sf::Vector2f(blockDim, blockDim));
		block.setPosition(tileIndex.x * blockDim, tileIndex.y * blockDim);
		block.setFillColor(tileColor);
		window.draw(block);
*/		
		sprite.setTexture(texture);
		sprite.setPosition(tileIndex.x * blockDim, tileIndex.y * blockDim); 
		sprite.setScale(sf::Vector2f(blockDim / 32.0f, blockDim / 32.0f));
		window.draw(sprite);
//	}
}

std::string Tile::toString() const {
	if (penetrable) {
		return "0";
	} else {
		return "1";
	}
}
