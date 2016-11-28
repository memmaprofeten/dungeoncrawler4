#include "character.hpp"
#include "settings.hpp"
#include "tile.hpp"

Character::Character(const std::string& n, bool t, float s, sf::Vector2f p, const std::string& txtrPath, const std::string& sdwPath, int l) : name(n), type(t), level(l), speed(s), pos(p), texturePath(txtrPath), shadowPath(sdwPath) {
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Could not load character texture.");
    }
    sprite.setTexture(texture);
    setRotation(s::characterRotationOffset);
    sprite.setOrigin(16, 16);
    sprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    sprite.setPosition(p);

    if (!shadowTexture.loadFromFile(shadowPath)) {
        throw std::runtime_error("Could not load character shadow.");
    }
    shadowSprite.setTexture(shadowTexture);
    shadowSprite.setOrigin(16, 8);
    shadowSprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    shadowSprite.setPosition(p);

    room = NULL;
}

std::string Character::getName() const { return name; }

sf::Vector2f Character::getPosition() const { return pos; }

void Character::move(sf::Vector2f dir, float elapsed, sf::View& view) {
    sf::Vector2f dpos = elapsed * speed * dir;
    if (room == NULL) {
        throw std::runtime_error("Character has no room assigned!");
    }
    sf::Vector2f dposHor = sf::Vector2f(dpos.x, 0);
    sf::Vector2f dposVer = sf::Vector2f(0, dpos.y);
    Tile& horTile = room->getTile(pos + dposHor);
    Tile& verTile = room->getTile(pos + dposVer);
    if (horTile.isPenetrable()) {
        pos += dposHor;
        sprite.move(dpos.x, 0);
        shadowSprite.move(dpos.x, 0);
        view.move(dpos.x, 0);
    }
    if (verTile.isPenetrable()) {
        pos += dposVer;
        sprite.move(0, dpos.y);
        shadowSprite.move(0, dpos.y);
        view.move(0, dpos.y);
    }
}

int Character::getRotation() { return rotation; }

void Character::setRotation(int angle) {
    rotation = s::characterRotationOffset + angle;
    sprite.setRotation(rotation);
}

Room* Character::getRoom() { return room; }

void Character::setRoom(Room* r) { room = r; }

void Character::draw(sf::RenderWindow& window) {
    window.draw(shadowSprite);
    window.draw(sprite);
}

void Character::reducehealth(int damage){
  health -= damage;
}
