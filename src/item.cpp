#include "item.hpp"
#include "character.hpp"
#include <iostream>
#include <algorithm>

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

void Item::dogoldthingy(Character& player){
  player.givegold(value);
}

void Item::dohealythingy(Character& player){
  //Set player health to either their max health, or their health + a percentage of max hp.
  player.sethealth(int(std::min(float(player.getMaxHealth()),player.getHealth()+(player.getMaxHealth()*value))));
}

void Item::doweaponthingy(Character& player){
  std::cout << "Weapon Pickup has been called. Player HP to make compiler happy: " << player.getHealth() << std::endl;
}

/*
void CreateItem(Room& Roomi){

}
*/
