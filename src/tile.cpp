#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include "settings.hpp"
#include "room.hpp"

Tile::Tile(int type, sf::Vector2f position, sf::Vector2i index, sf::Sprite* freeSprite){
	switch(type){
		case 0 :
			penetrable = true;
			material = Floor;
			textureIndex = 2;
			break;
		case 1 :
			penetrable = false;
			material = Wall;
			textureIndex = 6;
			break;
		}
	tilePosition = position;
	tileIndex = index;
	sprite = freeSprite;
	sprite->setPosition(position.x,position.y);
	sprite->setTexture(s::textures[textureIndex]);
	sprite->setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
}

bool Tile::isPenetrable() const {
	return penetrable;
}

std::string Tile::toString() const {
	switch(material){
		case Floor:
			return "0";
		case Wall:
			return "1";
		default:
			return "?";		// Undefined tile type
	}
}
