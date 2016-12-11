#include "character.hpp"
#include "settings.hpp"
#include "tile.hpp"
#include "item.hpp"
#include "room.hpp"
#include "weapon.hpp"

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

    health = getMaxHealth();
    gold = 0;
    room = NULL;
}

std::string Character::getName() const { return name; }

sf::Vector2f Character::getPosition() const { return pos; }

void Character::setPosition(sf::Vector2f newPosition) {
    pos = newPosition;
}

void Character::move(sf::Vector2f dir, float elapsed) {
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
        //sprite.move(dpos.x, 0);
    }
    if (verTile.isPenetrable()) {
        pos += dposVer;
        //sprite.move(0, dpos.y);
    }
}

sf::Vector2f Character::getHypotheticalPosition(sf::Vector2f dir, float elapsed) const {
    return getPosition() + elapsed * speed * dir;
}

int Character::getRotation() { return rotation; }

void Character::setRotation(int angle) {
    rotation = s::characterRotationOffset + angle;
    sprite.setRotation(rotation);
}

Room* Character::getRoom() { return room; }

void Character::setRoom(Room* r) { room = r; }

void Character::draw(sf::RenderWindow& window) {
    shadowSprite.setPosition(pos.x, pos.y);
    sprite.setPosition(pos.x, pos.y);
    window.draw(shadowSprite);
    window.draw(sprite);
}

std::vector<Item>& Character::getInventory() { return inventory; }

void Character::addItem(Item item) {
    inventory.push_back(item);
}

bool Character::consumeItem(int i) {
    if (i < 0 || i >= (int)inventory.size()) return false;
    // TODO: Check if item can be consumed
    // TODO: If it can, get the perks and remove it from the inventory. If not, return false.
    inventory[i].dothing(*this);
    if (inventory[i].gettype() == 2){
      inventory.erase(inventory.begin() + i);
      return true;
    }
    return false;
}

int Character::getHealth() const { return health; }

int Character::getMaxHealth() const {
    return 9 + level;      // NB! This algorithm can be changed for something more complex if there is need for it.
}

void Character::reducehealth(int damage){
  health -= damage;
}

void Character::teleport(sf::Vector2f dpos){
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
    }
    if (verTile.isPenetrable()) {
        pos += dposVer;
        sprite.move(0, dpos.y);
        shadowSprite.move(0, dpos.y);
    }
}

void Character::givegold(int goldin){
  gold += goldin;
}

int Character::getgold() const{
  return gold;
}

void Character::sethealth(int newhealth){
  health = newhealth;
}

void Character::givexp(int amount){
  if (xp + amount >= xpfornextlevel){
    xp = (xp+amount)-xpfornextlevel;
    level += 1;
    health = 9 + level;
  }
  else{
    xp += amount;
  }
}

int Character::getlevel(){
  return level;
}

void Character::equipweapon(Weapon* newweapon){
  //Commented out. Causes crash. Will feex. UPDATE: Is feeex.
  int weapontype = newweapon->getType();
  switch(weapontype){
  case 1:
    equippedmeleeweapon = newweapon;
    break;
  case 2:
    equippedrangedweapon = newweapon;
    break;
    }
}
