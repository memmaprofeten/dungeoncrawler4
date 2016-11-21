#include "weapon.hpp"
#include "item.hpp"
#include <string>
#include <list>

/*Can it be made so that only one instance of character can
be created?*/
class Character {
public:
/*Constructor taking name, type and level with default value 1
This can be used to initiate higher level characters if we decide
to implement a save feature

moving function

attacking and getting attacked functions

item pickup*/
private:
/*
name
type
level
list of weapons
list of other items

Basic variables. Possibly forgetting something though.*/
  std::string name; //Name of player. User input or based on class?
  int level; //Character level of player. Starts at 1
  std::list<Weapon> weapons; //List of weapons carried by player.
  std::list<Item> items; //List of items carried by player.
  Weapon equippedweapon; //currently equipped weapon.
  int maxhealth; //Player's maximum health.
  int health; //Player's current health.
  float movespeed; //Players movement speed.
  int xp; //Player's current experience amount.
  int xpfornextlevel; //amount required for player to level up.
};
