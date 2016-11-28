#include "monster.hpp"
#include <math.h>
#include <string.h>
#include "convenience.hpp"

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
/*
Weapon Monster::getcarriedweapon(){
  return carriedweapon;
}

Item Monster::getcarrieditem(){
  return carrieditem;
}
*/
int Monster::getaggrorange(){
  return aggrorange;
}

sf::Vector2f Monster::getPosition(){
  return position;
}

//Set x and y coordinates of monster.
void Monster::setxypos(int x, int y){
  position.x = x;
  position.y = y;
}

//Change x and y coordinates by input amount. Direction handled by negative input value.
void Monster::changexypos(float xchange, float ychange){
  position.x += xchange;
  position.y += ychange;
}

/*
xdir, 1 if moving right, -1 if moving left. 
ydir, 1 if moving up, -1 if moving down. 
0 for either if not moving along that axis. 
Basically iterates x and y positions based on movespeed in directions given by inputs. 
Should enable movement in 8 directions.
Does not handle collision, as I have no idea how.
*/ 
void Monster::monstermove(sf::Vector2f direction, float elapsed){
  changexypos(direction.x*movespeed*elapsed, direction.y*movespeed*elapsed);
}

//Reduces health by given amount. Then returns health so function that calls it can check if the monster died.
int Monster::reducehealth(int reducedby){
  health -= reducedby;
  return health;
}

// Constructors for melee and ranged monster classes.
RangedMonster::RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, int aggrorangei, float projectilespeedi, float attackrangei){
  monstername = namei;
  health = healthi;
  xponkill = xponkilli;
  attackdamage = attackdamagei;
  movespeed = movespeedi;
  //carrieditem = carrieditemi;
  //carriedweapon = carriedweaponi;
  aggrorange = aggrorangei;
  projectilespeed = projectilespeedi;
  attackrange = attackrangei;
  aggrostate = false;
}

MeleeMonster::MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, int aggrorangei, int attackrangei){
  monstername = namei;
  health = healthi;
  xponkill = xponkilli;
  attackdamage = attackdamagei;
  movespeed = movespeedi;
  //carrieditem = carrieditemi;
  //carriedweapon = carriedweaponi;
  aggrorange = aggrorangei;
  attackrange = attackrangei;
  aggrostate = false;
}

/*
Functions for attacking. Melee monster attacks check if the player is within range of the enemy. If they are, it reduces player damage based on its attackdamage variable. 

Ranged enemies will, if the player is within their attack range, fire a projectile at them. Not entirely sure how to handle said projectile.

Potential issues: Will attack every time function is called. Requires whatever AI function is calling it to limit how often the monster can attack.
*/

int Monster::getdistancetoplayer(Character player){
  return sqrt(pow((position.x - player.getPosition().x),2) + pow((position.y- player.getPosition().y),2));
}

//Returns true if player is within rangedefined by aggrorange variable. 
//Will be done once the player character class is more defined.

bool Monster::monsteraggrocheck(Character player){
  if (getdistancetoplayer(player) < aggrorange){
  return true;
 }
 else {
  return false;
 }
}
//Ranged monster attack.
void RangedMonster::monsterattack(Character player){
  if (getdistancetoplayer(player) < attackrange){
    //createprojectile(false, xpos, ypos, *projectilespeed x*, *projectile speed y*, attackdamage, 10);
    std::cout<<"boo"<<std::endl;
 }
}

//Melee monster attack.
//If player is within range, deals damage to player equal to attack damgae.
void MeleeMonster::monsterattack(Character player){
  if (getdistancetoplayer(player) <= attackrange){
    player.reducehealth(attackdamage);
    //std::cout << "ding" <<std::endl;
  }
}

/*
Code for the AI of the monsters. Essentially. It first checks if the player is within aggrorange. If it is, it flips the aggrostate to true. 
Then, the monster will move towards the player.
After that, it attacks the player if it is within range.
*/


void RangedMonster::monsterai(Character player, sf::RenderWindow& window, float elapsed){
  sf::Vector2f direction;

  if (monsteraggrocheck(player)){
    aggrostate = true;
  }
  
  if(aggrostate) {

//Determines direction. Will be replaced by pathfinding later.
    direction.x = player.getPosition().x - position.x;
    direction.y = player.getPosition().y - position.y;
    direction = cv::normalized(direction);

//Moves enemy in chosen direction.
    monstermove(direction, elapsed);

//Attacks player if in range.
    if (getdistancetoplayer(player)<attackrange){
      monsterattack(player);
    }
  }

  draw(window);
}

void MeleeMonster::monsterai(Character player, sf::RenderWindow& window, float elapsed){
  sf::Vector2f direction;
  
  if (monsteraggrocheck(player)){
    aggrostate = true;
  }

  if(aggrostate){
//Determines direction. Will be replaced by pathfinding later.
    direction.x = player.getPosition().x - position.x;
    direction.y = player.getPosition().y - position.y;
    direction = cv::normalized(direction);

//Moves enemy in chosen direction.
    monstermove(direction, elapsed);    

//Attacks player if in range.
    if (getdistancetoplayer(player)<attackrange){
      monsterattack(player);
    }
  }

  draw(window);
}

void Monster::draw(sf::RenderWindow& window){
  sf::CircleShape tile(3.0f);
  tile.setOrigin(1.5f, 1.5f);
  tile.setPosition(position.x, position.y);
  tile.setFillColor(sf::Color::Blue);
  window.draw(tile);
}
