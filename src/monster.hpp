#include <weapon.hpp>
#include <item.hpp>
/*The basic class for monsters/enemies*/
class Monster{
public:
/*Constructor similar to the character
each monster assigned random item at creation

Attacking and getting attacked

Moving function which is triggerd when character is close enough
or maybe always running around at random
*/

/*
General "return value" functions.
*/
  const std::string returnname();
  const int returnhealth();
  const int returnxponkill();
  const int returnattackdamage();
  const float returnmovespeed();
  const Weapon returncarriedweapon();
  const Item returncarrieditem();
  const int returnaggrorange();
  const int returnxpos();
  const int returnypos();
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

  virtual void monsterattack() = 0; //Handles attack by the monster.
  void monstermove(int xdir, int ydir); //Handles movement.
  bool monsteraggrocheck(Character player);//Checks if player is within range of monster.
 
private:
  std::string name; //Enemy name.
  int health; //Enemy health.
  int xponkill; //Experience given to player when killed.
  int attackdamage; //Damage dealt on attack.
  float movespeed; //Movementspeed of enemy.
  Item carrieditem; //Item to be carried. Dropped on death.
  Weapon carriedweapon; //Weapon carried. Dropped on death.
  int aggrorange; //AI Parameter. How close the player will have to be for the monster to move towards them.
  int xpos;
  int ypos;
/*
type
health
level
weapon
item (to be picked up by character after death
isAlive)
*/};

class RangedMonster : public Monster {
public:
  void monsterattack(int playerxpos, int playerypos);
  RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, Item carreditemi, Weapon carriedweaponi, int aggrorangei, float projectilespeedi, float projectilerangei);
  
private:
  float projectilespeed; //How fast the projectile fired by the enemy moves.
  float projectilerange; //How far the projectile travels / is active.
}

class MeleeMonster : public Monster{
public:
  void monsterattack(Character player);
  MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, Item carrieditemi, Weapon carriedweaponi, int aggrorangei, int attackrangei, int attackarci);

private:
  int attackrange; //Radius of the enemy's attack swing
  int attackarc; //How wide the swing is.

  /*Essentially, the way I thought of the monsters attack is as a semicircle with an arc and a radius. If the player is within that radius, they'll get hit. Should also hepl with graphics, depending on how we choose to represent an enemy's attack. */

}
