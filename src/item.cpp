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
    dogoldthingy(player);
    break;
  case 2:
    dohealythingy(player);
    break;
  case 3:
    doweaponthingy(player);
    break;
  }
}

bool Item::isactive() const{
  return active;
}

sf::Vector2f Item::getpos() const{
  return pos;
}

sf::Sprite& Item::getDropSprite() { return dropSprite; }

sf::Sprite& Item::getInventorySprite() { return inventorySprite; }

void Item::dogoldthingy(Character& player){
  //Gives player gold equal to value of the item.
  std::cout<< "Player picked up " << value << " gold!" << std::endl;
  player.givegold(value);
}

void Item::dohealythingy(Character& player){
  //Set player health to either their max health, or their health + a percentage of max hp.
  std::cout<< "Player has used a healing item, healing for " << value << "  health." << std::endl;
  player.sethealth(int(std::min(float(player.getMaxHealth()),player.getHealth()+value)));
}

void Item::doweaponthingy(Character& player){
  std::cout << "Player has equipped weapon " << representedweapon->getName() << "." << std::endl;
  player.equipweapon(representedweapon);
}

void Item::draw(sf::RenderWindow& window, Character& player){
    //sf::CircleShape tile(3.0f);
    //tile.setOrigin(1.5f,1.5f);
    //tile.setPosition(pos);


    /*switch(type){
    case 1:
      tile.setFillColor(sf::Color::Yellow);
      break;
    case 2:
      tile.setFillColor(sf::Color::Green);
      break;
    case 3:
      tile.setFillColor(sf::Color::White);
      break;
    }*/

    //Checks if player's xy position is within the item's area. If it is, calls the relevant "do thing" function, and disables the item.
    if (((pos.x - 3.0f)< player.getPosition().x) && (player.getPosition().x < (pos.x + 3.0f)) && ((pos.y - 3.0f) < player.getPosition().y) && (player.getPosition().y < (pos.y + 3.0f))){
    //if (cv::distance(pos, player.getPosition()) < 1.5f){
      switch(type){
      case 1:
	dogoldthingy(player);
	active = false;
	break;
      case 2:
	player.addItem(this);
	active = false;
	break;
      case 3:
	player.addItem(this);
	active = false;
	break;
      }
    }
	window.draw(dropSprite);
}

//sf::Texture Item::getTexture() const { return texture; }

Item::Item (std::string namei, int typei, float valuei, int textureIndexi, sf::Vector2f posi, int leveli){
  name = namei;
  type = typei;
  value = valuei;
  //textureFile = texturefilei;
  textureIndex = textureIndexi;
  pos = posi;
  active = true;
  level = leveli;
  representedweapon = NULL;
  /*if (!texture.loadFromFile(textureFile)) {
      throw std::runtime_error(std::string("Could not load Item texture") + textureFile + ".");
  }*/
  sellable = true;
  baseprice = 100;

  dropSprite.setTexture(s::textures[textureIndex]);
  inventorySprite.setTexture(s::textures[textureIndex]);
}


Item::Item(sf::Vector2f position, int leveli){

//Initialize random number generator.
 srand(time(NULL));

 type = rand() % 3 + 1;

//1: Gold, 1-100 per drop, 2: Healing, between 20% and 50%, 3: Weapon.
 switch(type){
 case 1:
   name = "Gold!";
   value = ceil(rand()%100+1);
   textureIndex = 7;
   representedweapon = NULL;
   break;
 case 2:
   name = "Potion of Healing!";
   value = float(rand() % (leveli*5) + 1);
   textureIndex = 7;
   representedweapon = NULL;
   break;
 case 3:
   textureIndex = 8;
   value = ((rand() % 255) + 1);

   int weapontype = (rand()%2)+1;
   switch(weapontype){
   case 1:{
     representedweapon = new RangedWeapon(leveli, value);
     name = representedweapon->getName();
     break;
   }
   case 2:{
     representedweapon = new MeleeWeapon(leveli, value);
     name = representedweapon->getName();
     break;
   }
   }
   break;
 }

 pos = position;
 level = leveli;
 active = true;
 sellable = true;
 baseprice = rand()%400+1;

 dropSprite.setTexture(s::textures[textureIndex]);
 inventorySprite.setTexture(s::textures[textureIndex]);
}

Item::Item(std::string namei, Weapon* weaponi, int leveli, int textureIndexi, sf::Vector2f posi){
  name = namei;
  representedweapon = weaponi;
  level = leveli;
  //textureFile = texturefilei;
  textureIndex = textureIndexi;
  pos = posi;
  level = leveli;
  active = true;
  type = 3;
  value = 0;
  sellable = false;
  baseprice = 100;

  dropSprite.setTexture(s::textures[textureIndex]);
  inventorySprite.setTexture(s::textures[textureIndex]);
}
