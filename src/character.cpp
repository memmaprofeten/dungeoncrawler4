#include "character.hpp"
#include "settings.hpp"
#include "tile.hpp"
#include "item.hpp"
#include "room.hpp"
#include "weapon.hpp"
#include <SFML/Audio.hpp>

Character::Character(const std::string& n, bool t, float s, sf::Vector2f p, int textureIndex, int shadowIndex, int l) : name(n), type(t), level(l), speed(s), pos(p) {
    sprite.setTexture(s::textures[textureIndex]);
    setRotation(s::characterRotationOffset);
    sprite.setOrigin(16, 16);
    sprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    sprite.setPosition(p);
    shadowSprite.setTexture(s::textures[shadowIndex]);
    shadowSprite.setOrigin(16, 8);
    shadowSprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    shadowSprite.setPosition(p);

    weaponAnim.set(p, sf::Vector2f(0, 0), 0.0f, 600.0f,  8, sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f), sf::Vector2f(32, 32), 0.2f);

    health = getMaxHealth();
    gold = 0;
    room = NULL;
    xpfornextlevel = 10;
}

Character::~Character() {
    /*for (unsigned i=0; i<inventory.size(); ++i) {     // This should no longer be needed (make sure)
        delete inventory[i];
    }*/
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
    }
    if (verTile.isPenetrable()) {
        pos += dposVer;
    }
}

sf::Vector2f Character::getHypotheticalPosition(sf::Vector2f dir, float elapsed) const {
    return getPosition() + elapsed * speed * dir + s::floatCorrection * dir;
}

int Character::getRotation() { return rotation; }

void Character::setRotation(int angle) {
    rotation = s::characterRotationOffset + angle;
    sprite.setRotation(rotation);
}

Room* Character::getRoom() { return room; }

void Character::setRoom(Room* r) { room = r; }

void Character::draw(sf::RenderWindow& window, float elapsed) {
    shadowSprite.setPosition(pos.x, pos.y);
    sprite.setPosition(pos.x, pos.y);
    window.draw(shadowSprite);
    if (weaponAnim.active) {
        weaponAnim.pos = pos;
        weaponAnim.draw(window, elapsed);
    }
    window.draw(sprite);
}

void Character::initiateMeleeAttack() {
    weaponAnim.rRot = rotation;
    weaponAnim.restart();
}

std::vector<Item*>& Character::getInventory() { return inventory; }

void Character::addItem(Item* item) {
    inventory.push_back(item);
}

bool Character::consumeItem(int i) {
    if (i < 0 || i >= (int)inventory.size()) return false;
    Item* item = inventory[i];
    bool res = false;
    switch(item->gettype()) {
        case 1:     // gold
            break;
        case 2:     // consumable
            res = true;
            break;
        case 3:     // weapon
            break;
        default:
            break;
    }
    item->dothing(*this);
    if (res) {
        inventory.erase(inventory.begin() + i);
    }
    return res;
}

int Character::getHealth() const { return health; }

int Character::getMaxHealth() const {
    return 9 + level;
}

void Character::reducehealth(int damage){
    health -= damage;
    if (health <= 0){
        minorcharactersound.setBuffer(s::soundbuffers[4]);
        minorcharactersound.play();
        // NB! Game defining death logic is handled by the main function.
    }
    else{
        majorcharactersound.setBuffer(s::soundbuffers[5]);
        majorcharactersound.play();
    }
}

void Character::teleport(sf::Vector2f dpos){
    if (room == NULL) {
        throw std::runtime_error("Character has no room assigned!");
    }
    sf::Vector2f dposHor = sf::Vector2f(dpos.x, 0);
    sf::Vector2f dposVer = sf::Vector2f(0, dpos.y);
    if (room->hasPosition(pos + dpos)) {      // Make sure the character is not being teleported out of bounds
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
}

void Character::givegold(int goldin){
    gold += goldin;
}

int Character::getgold() const{
    return gold;
}

void Character::sethealth(int newhealth){
    health = std::min(newhealth, getMaxHealth());
}

void Character::givexp(int amount){
    if (xp + amount >= xpfornextlevel){
        xp = (xp+amount)-xpfornextlevel;
        level += 1;
        health = 9 + level;
        xpfornextlevel += 10;

        majorcharactersound.setBuffer(s::soundbuffers[6]);
        majorcharactersound.play();
    }
    else{
        xp += amount;
    }
}

int Character::getlevel(){
    return level;
}

void Character::equipweapon(Weapon* newweapon){
    int weapontype = newweapon->getType();
    switch(weapontype){
        case 1:
            equippedmeleeweapon = newweapon;
            weaponAnim.updateTexture(newweapon->gettextureindex(), sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f), sf::Vector2f(32, 32));
            break;
        case 2:
            equippedrangedweapon = newweapon;
            break;
    }
}

Weapon* Character::getmeleeweapon() const{
    return equippedmeleeweapon;
}

Weapon* Character::getrangedweapon() const{
    return equippedrangedweapon;
}
