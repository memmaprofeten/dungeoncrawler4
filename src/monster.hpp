#ifndef MONSTER_HH
#define MONSTER_HH

#include "weapon.hpp"
#include "item.hpp"
#include "character.hpp"
#include <string>
/*The basic class for monsters/enemies*/
class Monster{
public:
  Monster(){};
  ~Monster(){};
/*Constructor similar to the character
each monster assigned random item at creation

Attacking and getting attacked

Moving function which is triggerd when character is close enough
or maybe always running around at random
*/

/*
General "return value" functions.
*/
  std::string getname();
  int gethealth();
  int getxponkill();
  int getattackdamage();
  float getmovespeed();
  //Weapon getcarriedweapon();
  //Item getcarrieditem();
  int getaggrorange();
  sf::Vector2f getPosition();
  void setxypos(int x, int y);
  void changexypos(int xchange, int ychange);

/*
Reduce monster health. To be called by whatever handles the monster getting hit.
*/

  int reducehealth(int reducedby);

/*
Functions to be called by the AI code. In theory, handle movement and attacking.
Monster attack function virtual so ranged and melee monsters attack differently.
*/
  bool monsteraggrocheck(Character player);
  int getdistancetoplayer(Character player);
  virtual void monsterattack(Character player) =0; //Handles attack by the monster.
  virtual void monsterai(Character player, sf::RenderWindow& window, float elapsed) =0; //Handles monster AI.
  void monstermove(int xdir, int ydir, float elapsed); //Handles movement.
  //bool monsteraggrocheck(Character player);//Checks if player is within range of monster.

  //For drawing the monster.
  void draw(sf::RenderWindow& window);

protected:
  std::string monstername; //Enemy name.
  int health; //Enemy health.
  int xponkill; //Experience given to player when killed.
  int attackdamage; //Damage dealt on attack.
  float movespeed; //Movementspeed of enemy.
  //Item carrieditem; //Item to be carried. Dropped on death.
  //Weapon carriedweapon; //Weapon carried. Dropped on death.
  int aggrorange; //AI Parameter. How close the player has to be for the AI to aggro.
  sf::Vector2f position;
  bool aggrostate; //If the monster is actively chasing/attacking the player.
/*
type
health
level
weapon
item (to be picked up by character after death
isAlive)
*/
};

class RangedMonster : public Monster {
public:
  void monsterattack(Character player);
  void monsterai(Character player, sf::RenderWindow&, float elapsed);
  RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, int aggrorangei, float projectilespeedi, float attackrangei);

private:
  float projectilespeed; //How fast the projectile fired by the enemy moves.
  float attackrange; //At what distance the enemy attacks.
};

class MeleeMonster : public Monster{
public:
  void monsterattack(Character player);
  void monsterai(Character player, sf::RenderWindow& window, float elapsed);
  MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, int aggrorangei, int attackrangei);

private:
  int attackrange; //Radius of the enemy's attack swing


};

#endif
