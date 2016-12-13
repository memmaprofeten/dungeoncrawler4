#ifndef MONSTER_HH
#define MONSTER_HH

#include <string>
#include <SFML/Graphics.hpp>
#include "projectile.hpp"

class Character;
class Item;
class Room;

class Monster{
public:
  Monster();
  virtual ~Monster();
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
  float getaggrorange();
  sf::Vector2f getPosition();
  void setxypos(int x, int y);
  void changexypos(float xchange, float ychange);
  bool isactive() const;

/*
Reduce monster health. To be called by whatever handles the monster getting hit.
*/
  void reducehealth(int reducedby);

/*
Functions to be called by the AI code. In theory, handle movement and attacking.
Monster attack function virtual so ranged and melee monsters attack differently.
*/
  bool monsteraggrocheck(Character player);
  float getdistancetoplayer(Character player);
  virtual void monsterattack(Character& player) =0; //Handles attack by the monster.
  virtual void monsterai(Character& player, float elapsed) =0; //Handles monster AI.
  void monstermove(sf::Vector2f direction, float elapsed); //Handles movement.
  //bool monsteraggrocheck(Character player);//Checks if player is within range of monster.

  //For drawing the monster.
  //void draw(sf::RenderWindow& window);

protected:
  std::string monstername; //Enemy name.
  int health; //Enemy health.
  int xponkill; //Experience given to player when killed.
  int attackdamage; //Damage dealt on attack.
  float movespeed; //Movementspeed of enemy.
  float aggrorange; //AI Parameter. How close the player has to be for the AI to aggro.
  sf::Vector2f position;
  Room* room;   // Pointer to the room that the monster is currently in
  bool aggrostate; //If the monster is actively chasing/attacking the player.
  float attacktimer; //Amount of time inbetween attacks.
  float timebetweenattacks; //explanatory
  bool active;
  sf::Sprite* sprite; //Pointer to sprite object
  int textureIndex;
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
  void monsterai(Character& player, float elapsed);
  //Constructor
  RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, float aggrorangei, float projectilespeedi, float attackrangei, Room* roomi, /*std::vector<Projectile>* projectiles*/ float timebetweenattacksi);
  RangedMonster(sf::Vector2f positioni, Room* roomi, int leveli);
  ~RangedMonster();

private:
  float projectilespeed; //How fast the projectile fired by the enemy moves.
  float attackrange; //At what distance the enemy attacks.
};

class MeleeMonster : public Monster{
public:
  //Virtual functions from Monster.
  void monsterattack(Character& player);
  void monsterai(Character& player, float elapsed);
  //Constructor
  MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, float aggrorangei, int attackrangei, Room* roomi, float timebetweenattacksi);
  MeleeMonster(sf::Vector2f positioni, Room* roomi, int leveli);
  ~MeleeMonster();

private:
  int attackrange; //Radius of the enemy's attack swing
};

#endif
