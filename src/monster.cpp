#include <monster.hpp>
#include <weapon.hpp>
#include <item.hpp>
/*
Basic functions. There's probably some brainfarting going on since I have the memory of a goldfish.

Todo: Aggrocheck. General AI including pathfinding. Collision for movement. Attack functions 

Collision requires some way to tie xy position to specific tile on map.
Pathfinding requires some shenaniganry and/or googling the algorithms.
Aggrocheck requires way to get position of player.
General AI requires above things to be complete.

Ranged monster attack requires code for projectiles, which has yet to be implemented.
 */
const std::string returnname(){
  return name;
}
const int Monster::returnhealth(){
  return health;
}

const int Monster::returnxponkill(){
  return xponkill;
}

const int Monster::returnattackdamage(){
  return attackdamage;
}

const float Monster::returnmovespeed(){
  return movespeed;
}

const Weapon Monster::returncarriedweapon(){
  return carriedweapon;
}

const Item Monster::returncarrieditem(){
  return carrieditem;
}

const int Monster::returnaggrorange(){
  return aggrorange;
}

const int Monster::returnxpos(){
  return xpos;
}

const int Monster::returnypos(){
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
  changexypos(std::floor(xdir*movespeed), std::floor(ydir*movespeed));
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
RangedMonster::RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, Item carreditemi, Weapon carriedweaponi, int aggrorangei, float projectilespeedi, float projectilerangei){
  name = namei
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
  name = namei
  health = healthi;
  xponkill = xponkilli;
  attackdamage = attackdamagei;
  movespeed = movespeedi;
  carrieditem = carrieditemi;
  carriedweapon = carriedweaponi;
  aggrorange = aggrorangei;
  attackrange = attackrangei;
  attackarc = attackarci
}

/*
Functions for attacking. Melee monster attacks check if the player is within range of the enemy. If they are, it reduces player damage based on its attackdamage variable. 

Ranged enemies will, if the player is within their attack range, fire a projectile at them. Not entirely sure how to handle said projectile.

Potential issues: Will attack every time function is called. Requires whatever AI function is calling it to limit how often the monster can attack.
*/
/*
void Rangedmonster::monsterattack(int playerxpos, int playerypos){
}

void MeleeMonster::monsterattack(Character player){
}
*/
