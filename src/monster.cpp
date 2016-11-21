#include "monster.hpp"
#include <math.h>
#include <string.h>

/*
Basic functions. There's probably some brainfarting going on since I have the memory of a goldfish.

Todo: Aggrocheck. General AI including pathfinding. Collision for movement. Attack functions 

Collision requires some way to tie xy position to specific tile on map.
Pathfinding requires some shenaniganry and/or googling the algorithms.
Aggrocheck requires way to get position of player.
General AI requires above things to be complete.

Ranged monster attack requires code for projectiles, which has yet to be implemented.
 */
std::string Monster::getname(){
  return monstername;
}
int Monster::gethealth(){
  return health;
}

int Monster::getxponkill(){
  return xponkill;
}

int Monster::getattackdamage(){
  return attackdamage;
}

float Monster::getmovespeed(){
  return movespeed;
}

Weapon Monster::getcarriedweapon(){
  return carriedweapon;
}

Item Monster::getcarrieditem(){
  return carrieditem;
}

int Monster::getaggrorange(){
  return aggrorange;
}

int Monster::getxpos(){
  return xpos;
}

int Monster::getypos(){
  return ypos;
}

//Set x and y coordinates of monster.
void Monster::setxypos(int x, int y){
  xpos = x;
  ypos = y;
}

//Change x and y coordinates by input amount. Direction handled by negative input value.
void Monster::changexypos(int xchange, int ychange){
  xpos += xchange;
  ypos += ychange;
}

/*
xdir, 1 if moving right, -1 if moving left. 
ydir, 1 if moving up, -1 if moving down. 
0 for either if not moving along that axis. 
Basically iterates x and y positions based on movespeed in directions given by inputs. 
Should enable movement in 8 directions.
Does not handle collision, as I have no idea how.
*/ 
void Monster::monstermove(int xdir, int ydir){
  changexypos(floor(xdir*movespeed), floor(ydir*movespeed));
}

//Returns true if player is within range of monster defined by aggrorange variable. Will be done once the player character class is more defined.
/*
bool Monster::monsteraggrocheck(Character player){
}
*/

//Reduces health by given amount. Then returns health so function that calls it can check if the monster died.
int Monster::reducehealth(int reducedby){
  health -= reducedby;
  return health;
}

// Constructors for melee and ranged monster classes.
RangedMonster::RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, Item carrieditemi, Weapon carriedweaponi, int aggrorangei, float projectilespeedi, float projectilerangei){
  monstername = namei;
  health = healthi;
  xponkill = xponkilli;
  attackdamage = attackdamagei;
  movespeed = movespeedi;
  carrieditem = carrieditemi;
  carriedweapon = carriedweaponi;
  aggrorange = aggrorangei;
  projectilespeed = projectilespeedi;
  projectilerange = projectilerangei;
}

MeleeMonster::MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, Item carrieditemi, Weapon carriedweaponi, int aggrorangei, int attackrangei, int attackarci){
  monstername = namei;
  health = healthi;
  xponkill = xponkilli;
  attackdamage = attackdamagei;
  movespeed = movespeedi;
  carrieditem = carrieditemi;
  carriedweapon = carriedweaponi;
  aggrorange = aggrorangei;
  attackrange = attackrangei;
  attackarc = attackarci;
}

/*
Functions for attacking. Melee monster attacks check if the player is within range of the enemy. If they are, it reduces player damage based on its attackdamage variable. 

Ranged enemies will, if the player is within their attack range, fire a projectile at them. Not entirely sure how to handle said projectile.

Potential issues: Will attack every time function is called. Requires whatever AI function is calling it to limit how often the monster can attack.
*/
/*
void Rangedmonster::monsterattack(Character player){
}

void MeleeMonster::monsterattack(Character player){
}
*/
