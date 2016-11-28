#include "character.hpp"
#include "settings.hpp"

Character::Character(const std::string& n, bool t, const std::string& txtrPath, int l) : name(n), type(t), level(l), texturePath(txtrPath) {
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Could not load character texture.");
    }
    sprite.setTexture(texture);
    setRotation(s::characterRotationOffset);
    sprite.setOrigin(16, 16);
    sprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    pos = sf::Vector2f(0, 0);
}

std::string Character::getName() const { return name; }

sf::Vector2f Character::getPosition() const { return pos; }

void Character::move(sf::Vector2f dpos) {
    // TODO: Check collisions
    pos += dpos;
    sprite.move(dpos.x, dpos.y);
}

int Character::getRotation() { return rotation; }

void Character::setRotation(int angle) {
    rotation = s::characterRotationOffset + angle;
    sprite.setRotation(rotation);
}

void Character::draw(sf::RenderWindow& window) {
    // TODO: Check if charecter would go through impenetrable obstacle
    window.draw(sprite);
}

void Character::reducehealth(int damage){
  health -= damage;
}
