#include "settings.hpp"
#include "npc.hpp"
#include "item.hpp"
#include "character.hpp"
#include "convenience.hpp"
#include <iostream>

Npc::Npc(int textureIndex, sf::Vector2f pos) {
    sprite.setTexture(s::textures[textureIndex]);
    setPosition(pos);
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

bool Npc::isInRange() const {
    return inRange;
}

std::vector<Item*>& Npc::getInventory() {
    return inventory;
}

void Npc::draw(sf::RenderWindow& window, Character& player) {
    //shadowSprite.setPosition(pos.x, pos.y);
    sprite.setPosition(pos.x, pos.y);
    //window.draw(shadowSprite);
    window.draw(sprite);

    // When to activate NPC functions
    if(cv::distance(pos, player.getPosition()) < 1.5f*s::blockDim) {
        inRange = true;
    }
    else {
        inRange = false;
    }
}

Shopkeeper::Shopkeeper(int texture, sf::Vector2f pos) : Npc(texture, pos) {
    inventory.push_back(new Item("Doughnut", 4, 3, 7, sf::Vector2f(0, 0),1));
    inventory.push_back(new Item("Ice cream", 4, 2, 8, sf::Vector2f(0, 0),1));
    inventory.push_back(new Item("Cake", 4, 5, 8, sf::Vector2f(0, 0),1));
}
