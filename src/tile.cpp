#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include "settings.hpp"
#include "room.hpp"
//TODO: Replace Texture indexes with something more correct
//Assigning the right parameters to Tile
Tile::Tile(int type, sf::Vector2f position, sf::Vector2i index, sf::Sprite* freeSprite){
	switch(type){
		case 0 :
			penetrable = true;
			material = Floor;
			textureIndex = 2; //replace with sensible
			break;
		case 1 :
			penetrable = false;
			material = Wall;
			textureIndex = 6; //This to
			break;
		}
	tilePosition = position;
	tileIndex = index;
	sprite = freeSprite;
	sprite->setPosition(position.x,position.y);
	sprite->setTexture(s::textures[textureIndex]);
	sprite->setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
}
//Returns if character can walk through tile
bool Tile::isPenetrable() const {
	return penetrable;
}
//We don't need this
/*void Tile::draw(sf::RenderWindow& window, float blockDim){
//TODO: Make new draw function, or discard it comletely
//	if (material == Wall) {

		sf::RectangleShape block(sf::Vector2f(blockDim, blockDim));
		block.setPosition(tileIndex.x * blockDim, tileIndex.y * blockDim);
		block.setFillColor(tileColor);
		window.draw(block);

		sprite.setTexture(texture);
		sprite.setPosition(tileIndex.x * blockDim, tileIndex.y * blockDim);
		sprite.setScale(sf::Vector2f(blockDim / 32.0f, blockDim / 32.0f));
		window.draw(sprite);
}
}
*/
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
