#ifndef MONSTER_HH
#define MONSTER_HH

#include "weapon.hpp"
#include "item.hpp"
#include "projectile.hpp"
#include "character.hpp"
#include <string>
/*The basic class for monsters/enemies*/
struct RangedMonster;
struct MeleeMonster;

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
  void changexypos(float xchange, float ychange);

/*
Reduce monster health. To be called by whatever handles the monster getting hit.
*/
  virtual int reducehealth(int reducedby)=0;

/*
Functions to be called by the AI code. In theory, handle movement and attacking.
Monster attack function virtual so ranged and melee monsters attack differently.
*/
  bool monsteraggrocheck(Character player);
  int getdistancetoplayer(Character player);
  virtual void monsterattack(Character& player) =0; //Handles attack by the monster.
  virtual void monsterai(Character& player, sf::RenderWindow& window, float elapsed) =0; //Handles monster AI.
  void monstermove(sf::Vector2f direction, float elapsed); //Handles movement.
  //bool monsteraggrocheck(Character player);//Checks if player is within range of monster.

  //For drawing the monster.
  void draw(sf::RenderWindow& window);

protected:
  std::string monstername; //Enemy name.
  int health; //Enemy health.
  int xponkill; //Experience given to player when killed.
  int attackdamage; //Damage dealt on attack.
  float movespeed; //Movementspeed of enemy.
  int aggrorange; //AI Parameter. How close the player has to be for the AI to aggro.
  sf::Vector2f position;
  bool aggrostate; //If the monster is actively chasing/attacking the player.
  float attacktimer; //Amount of time inbetween attacks.
  float timebetweenattacks; //explanatory
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
  //Virtual functions from Monster.
  void monsterattack(Character& player);
  void monsterai(Character& player, sf::RenderWindow& window, float elapsed);
  int reducehealth(int reducedby);
  //Constructor
  RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, int aggrorangei, float projectilespeedi, float attackrangei, std::vector<Projectile>* projectiles, float timebetweenattacksi, std::vector<RangedMonster>* rangedmonstersi);
  //bool operator==(const RangedMonster inp) const;
  //bool operator==(const MeleeMonster inp) const;
private:
  float projectilespeed; //How fast the projectile fired by the enemy moves.
  float attackrange; //At what distance the enemy attacks.
  std::vector<Projectile>* projectiles;//Pointer to projectile vector to make creating new projectiles easier.
  std::vector<RangedMonster>* monsters;//Pointer to ranged monsters vector so it can erase itself from it.
};

class MeleeMonster : public Monster{
public:
  //Virtual functions from Monster.
  void monsterattack(Character& player);
  void monsterai(Character& player, sf::RenderWindow& window, float elapsed);
  int reducehealth(int reducedby);
  //Constructor
  MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, int aggrorangei, int attackrangei, float timebetweenattacksi, std::vector<MeleeMonster>* meleemonstersi);
  //bool operator==(const MeleeMonster inp) const;
  //bool operator==(const RangedMonster inp) const;
private:
  int attackrange; //Radius of the enemy's attack swing
  std::vector<MeleeMonster>* monsters; //pointer to list containing all melee monsters so it can erase itself when dying.


};

#endif
