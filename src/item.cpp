#include "item.hpp"
#include "character.hpp"
#include "convenience.hpp"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

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

void Item::dogoldthingy(Character& player){
  //Gives player gold equal to value of the item.
  std::cout<< "Player picked up " << value << " gold!" << std::endl;
  player.givegold(value);
}

void Item::dohealythingy(Character& player){
  //Set player health to either their max health, or their health + a percentage of max hp.
  std::cout<< "Player has picked up a healing item, healing for " << value << " of their max health." << std::endl;
  player.sethealth(int(std::min(float(player.getMaxHealth()),player.getHealth()+(player.getMaxHealth()*value))));
}

void Item::doweaponthingy(Character& player){
  std::cout << "Weapon Pickup has been called. Player HP to make compiler happy: " << player.getHealth() << std::endl;
}

void Item::draw(sf::RenderWindow& window, Character& player){
  sf::CircleShape tile(3.0f);
    tile.setOrigin(1.5f,1.5f);
    tile.setPosition(pos);

    switch(type){
    case 1:
      tile.setFillColor(sf::Color::Yellow);
      break;
    case 2:
      tile.setFillColor(sf::Color::Green);
      break;
    case 3:
      tile.setFillColor(sf::Color::White);
      break;
    }

    window.draw(tile);
    //Checks if player's xy position is within the item's area. If it is, calls the relevant "do thing" function, and disables the item.
    if (((pos.x - 1.5f)< player.getPosition().x) && (player.getPosition().x < (pos.x + 1.5f)) && ((pos.y - 1.5f) < player.getPosition().y) && (player.getPosition().y < (pos.y + 1.5f))){
    //if (cv::distance(pos, player.getPosition()) < 1.5f){
      switch(type){
      case 1:
	dogoldthingy(player);
	break;
      case 2:
	dohealythingy(player);
	break;
      case 3:
	doweaponthingy(player);
      }

      active = false;
    }
}

sf::Texture Item::getTexture() const { return texture; }

Item::Item (std::string namei, int typei, float valuei, std::string texturefilei, sf::Vector2f posi){
  name = namei;
  type = typei;
  value = valuei;
  textureFile = texturefilei;
  pos = posi;
  active = true;
  if (!texture.loadFromFile(textureFile)) {
      throw std::runtime_error(std::string("Could not load Item texture") + textureFile + ".");
  }
}


void CreateItem(std::vector<Item>& itemstorage, sf::Vector2f position){
  std::string name;
 int type;
 float value;
 std::string texturefile;
 sf::Vector2f pos;

//Set position to one given in input.
 pos = position;

//Initialize random number generator.
 srand(time(NULL));

 type = rand() % 3 + 1;

//1: Gold, 1-100 per drop, 2: Healing, between 20% and 50%, 3: Weapon.
 switch(type){
 case 1:
   name = "Gold!";
   value = ceil(rand()%100+1);
   break;
 case 2:
   name = "Potion of Healing!";
   value = float((ceil(rand()%30+20))/100);
   break;
 case 3:
   name = "Weapon!";
   value = 0;
   break;
 }


 Item newitem = Item(name, type, value, "Placeholder for eventual real texture filepath.", pos);

 itemstorage.push_back(newitem);

}
