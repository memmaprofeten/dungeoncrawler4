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

  const bool returntype();
  const int returnhealth();
  const int returnxponkill();
  const int returnattackdamage();
  const int returnattackrange();
  const float returnprojectilespeed();
  const float returnmovespeed();
  const Weapon returncarriedweapon();
  const Item returncarrieditem();
  const int returnaggrorange();
 
private:
  bool type; //True = Ranged, False = Melee. Mahdollisesti toteutetaan käyttämällä eri luokkia?
  int health; //Enemy health.
  int xponkill; //Experience given to player when killed.
  int attackdamage; //Damage dealt on attack.
  int attackrange; //Attack range for melee enemies.
  float projectilespeed; //Speed of projectile for ranged enemies.
  float movespeed; //Movementspeed of enemy.
  Item carrieditem; //Item to be carried. Dropped on death.
  Weapon carriedweapon; //Weapon carried. Dropped on death.
  int aggrorange; //AI Parameter. How close the player will have to be for the monster to move towards them.
/*
type
health
level
weapon
item (to be picked up by character after death
isAlive)
*/};
