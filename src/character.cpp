#include "character.hpp"
//#include "settings.hpp"

Character::Character(const std::string& n, bool t, const std::string& txtrPath, int l) : name(n), type(t), level(l), texturePath(txtrPath) {
    float blockDim = 10.0f;
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Could not load character texture.");
    }
    sprite.setTexture(texture);
    sprite.setRotation(270);
    sprite.setOrigin(16, 16);
    sprite.setScale(sf::Vector2f(blockDim / 32.0f, blockDim / 32.0f));
    pos = sf::Vector2f(0, 0);
}

std::string Character::getName() const { return name; }

sf::Vector2f Character::getPosition() const { return pos; }

//std::string Character::getTexture() const { return texture; }

void Character::move(sf::Vector2f dpos) {
    // TODO: Check collisions
    pos += dpos;
    sprite.move(dpos.x, dpos.y);
}

void Character::draw(sf::RenderWindow& window) {
    // TODO: Check if charecter would go through impenetrable obstacle
    window.draw(sprite);
}
