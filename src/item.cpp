#include "item.hpp"
#include "room.hpp"
#include "weapon.hpp"
#include "character.hpp"
#include "convenience.hpp"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <cmath>

Item::~Item() {}

std::string Item::getname() const{
    return name;
}

int Item::gettype() const{
    return type;
}

float Item::getvalue() const{
    return value;
}

//case 1, gold. case 2, healing item. case 3, random weapon
void Item::dothing(Character& player){
    switch(type){
        case 1:
            applyGoldEffects(player);
            break;
        case 2:
            applyConsumableEffects(player);
            break;
        case 3:
            applyWeaponEffects(player);
            break;
    }
}

sf::Vector2f Item::getpos() const{
    return pos;
}

sf::Sprite& Item::getDropSprite() { return dropSprite; }

sf::Sprite& Item::getInventorySprite() { return inventorySprite; }

void Item::applyGoldEffects(Character& player){
    //Gives player gold equal to value of the item:
    std::cout<< "Player picked up " << value << " gold!" << std::endl;
    player.givegold(value);
}

void Item::applyConsumableEffects(Character& player){
    //Set player health to either their max health, or their health + a percentage of max hp:
    std::cout<< "Player has used a healing item, healing for " << value << "  health." << std::endl;
    player.sethealth(int(std::min(float(player.getMaxHealth()),player.getHealth()+value)));
}

void Item::applyWeaponEffects(Character& player){
    std::cout << "Player has equipped weapon " << representedweapon->getName() << "." << std::endl;
    player.equipweapon(representedweapon);
}

void Item::draw(sf::RenderWindow& window, Character& player){
    window.draw(dropSprite);
}

Item::Item (std::string namei, int typei, float valuei, int textureIndexi, sf::Vector2f posi, int leveli){
    name = namei;
    type = typei;
    value = valuei;
    textureIndex = textureIndexi;
    pos = posi;
    level = leveli;
    representedweapon = NULL;
    sellable = true;
    baseprice = 100;

    dropSprite.setTexture(s::textures[textureIndex]);
    dropSprite.setOrigin(16.0f, 16.0f);
    dropSprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    dropSprite.setPosition(pos);
    inventorySprite.setTexture(s::textures[textureIndex]);
}


Item::Item(sf::Vector2f position, int leveli){

    type = rand() % 3 + 1;
    representedweapon = NULL;
    int weapontype;
    //1: Gold, 1-100 per drop, 2: Healing, between 20% and 50%, 3: Weapon:
    switch(type){
        case 1:
            name = "Gold!";
            value = ceil(rand()%100+1);
            textureIndex = 15;
            break;
        case 2:
            name = "Potion of Healing!";
            value = float(rand() % (leveli*5) + 1);
            textureIndex = 17;
            break;
        case 3:
            value = ((rand() % 255) + 1);
            weapontype = (rand()%2)+1;
            switch(weapontype){
                case 1:
                    representedweapon = new RangedWeapon(leveli, value);
                    name = representedweapon->getName();
                    break;
                case 2:
                    representedweapon = new MeleeWeapon(leveli, value);
                    name = representedweapon->getName();
                    break;
            }
            textureIndex = representedweapon->gettextureindex();
            break;
        default:        // This can't currently be reached by the randomizer, but it is implemented to allow extension in the future.
            name = "Trinket";
            value = 0;
            textureIndex = 6;
            break;
    }

    pos = position;
    level = leveli;
    sellable = true;
    baseprice = rand()%400+1;

    dropSprite.setTexture(s::textures[textureIndex]);
    dropSprite.setOrigin(16.0f, 16.0f);
    dropSprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    dropSprite.setPosition(pos);
    inventorySprite.setTexture(s::textures[textureIndex]);
}

Item::Item(std::string namei, Weapon* weaponi, int leveli, int textureIndexi, sf::Vector2f posi){
    name = namei;
    representedweapon = weaponi;
    level = leveli;
    textureIndex = textureIndexi;
    pos = posi;
    level = leveli;
    type = 3;
    value = 0;
    sellable = false;
    baseprice = 100;

    dropSprite.setTexture(s::textures[textureIndex]);
    dropSprite.setOrigin(16.0f, 16.0f);
    dropSprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    dropSprite.setPosition(pos);
    inventorySprite.setTexture(s::textures[textureIndex]);
}
