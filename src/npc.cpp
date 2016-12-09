#include "settings.hpp"
#include "npc.hpp"
#include "item.hpp"

Npc::Npc(std::string s) {
  texture.loadFromFile(s);
  sprite.setTexture(texture);
  sprite.setOrigin(16, 16);
  sprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
  setRotation(120);
}

void Npc::setPosition(sf::Vector2f newPosition) {
  pos = newPosition;
}

void Npc::setRotation(int angle) {
    sprite.setRotation(angle);
}

void Npc::draw(sf::RenderWindow& window) {
    //shadowSprite.setPosition(pos.x, pos.y);
    sprite.setPosition(pos.x, pos.y);
    //window.draw(shadowSprite);
    window.draw(sprite);
}


Shopkeeper::Shopkeeper(std::string s) : Npc(s) {
  inventory.push_back(Item("Doughnut", 4, 3, "../resources/img/doughnut_32.png", sf::Vector2f(0, 0),1));
  inventory.push_back(Item("Ice cream", 4, 2, "../resources/img/sword1_32.png", sf::Vector2f(0, 0),1));
  inventory.push_back(Item("Cake", 4, 5, "../resources/img/sword1_32.png", sf::Vector2f(0, 0),1));
}
