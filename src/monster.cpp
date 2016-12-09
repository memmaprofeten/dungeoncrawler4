#include <math.h>
#include <string.h>
#include <vector>
#include "monster.hpp"
#include "convenience.hpp"
#include "settings.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "item.hpp"
#include "room.hpp"
#include "item.hpp"
#include <stdlib.h>
#include <time.h>

/*
Basic functions. There's probably some brainfarting going on since I have the memory of a goldfish.

Todo: Aggrocheck. General AI including pathfinding. Collision for movement. Attack functions

Collision requires some way to tie xy position to specific tile on map.
Pathfinding requires some shenaniganry and/or googling the algorithms.
Aggrocheck requires way to get position of player. **DONE**
General AI requires above things to be complete. **DONE**
Ranged monster attack requires code for projectiles, which has yet to be implemented. **DONE**
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

float Monster::getaggrorange(){
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

bool Monster::isactive() const{
  return active;
}

/*
Basically iterates x and y positions based on movespeed in directions given by inputs.Takes in a normalized vector based on player's position relative to monster.
Does not handle collision, as I have no idea how.
*/
void Monster::monstermove(sf::Vector2f direction, float elapsed){
  changexypos(direction.x*movespeed*elapsed, direction.y*movespeed*elapsed);
}

//Reduces health by given amount. Then checks if health is below 0. If it is, it searches the vectors containing the monster for itself, erases itself, and then returns the amount of experience the player gains.
void Monster::reducehealth(int reducedby){
  health -= reducedby;
  if(health <= 0){
    //Sets monster as inactive.
    active = false;
    //Drops item
    CreateItem(room->getitems(), position);
    //Awards player XP
    room->getcharacter()->givexp(xponkill);

    /*
    for(auto iter=monsters->begin(); iter != monsters->end(); iter++){
      //if (monstername == iter->getname()){
      if (this == &(*iter)){ //Yes, this works.
	//std::cout << "DING DING DING"<<std::endl;
	monsters->erase(iter);
	return temp;
      }
      }  */

  }
}

// Constructors for melee and ranged monster classes.
RangedMonster::RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, float aggrorangei, float projectilespeedi, float attackrangei, Room* roomi, /*std::vector<Projectile>* projectilesi*/ float timebetweenattacksi){
  monstername = namei;
  health = healthi;
  xponkill = xponkilli;
  attackdamage = attackdamagei;
  movespeed = movespeedi;
  aggrorange = aggrorangei;
  projectilespeed = projectilespeedi;
  attackrange = attackrangei;
  aggrostate = false;
  room = roomi;
  //projectiles = projectilesi;
  timebetweenattacks = timebetweenattacksi;
  attacktimer = 0.0;
  active = true;
}

RangedMonster::~RangedMonster() {}

MeleeMonster::MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, float aggrorangei, int attackrangei, Room* roomi, float timebetweenattacksi){
  monstername = namei;
  health = healthi;
  xponkill = xponkilli;
  attackdamage = attackdamagei;
  movespeed = movespeedi;
  aggrorange = aggrorangei;
  attackrange = attackrangei;
  aggrostate = false;
  room = roomi;
  timebetweenattacks = timebetweenattacksi;
  attacktimer = 0.0;
  active = true;
}

MeleeMonster::~MeleeMonster() {}

/*
Functions for attacking. Melee monster attacks check if the player is within range of the enemy. If they are, it reduces player damage based on its attackdamage variable.

Ranged enemies will, if the player is within their attack range, fire a projectile at them. Not entirely sure how to handle said projectile.

Potential issues: Will attack every time function is called. Requires whatever AI function is calling it to limit how often the monster can attack.
*/

float Monster::getdistancetoplayer(Character player){
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
void RangedMonster::monsterattack(Character& player){
  if (getdistancetoplayer(player) < attackrange){
    Projectile& projectile = room->createProjectile(false, 2, 0.8f * s::blockDim, projectilespeed, 4);
    projectile.setPosition(position);
    projectile.setDirection(cv::normalized(player.getPosition() - position));
 }
}

//Melee monster attack.
//If player is within range, deals damage to player equal to attack damgae.
void MeleeMonster::monsterattack(Character& player){
  if (getdistancetoplayer(player) <= attackrange){
    player.reducehealth(attackdamage);
    player.teleport(cv::normalized(player.getPosition() - position) * 2.0f);
    //std::cout << "Damage dealt: " << attackdamage << std::endl;
    //std::cout << "Playerhealth: " <<  player.getHealth()<<std::endl;
  }
}

/*
Code for the AI of the monsters. Essentially. It first checks if the player is within aggrorange. If it is, it flips the aggrostate to true.
Then, the monster will move towards the player.
After that, it attacks the player if it is within range.
*/


void RangedMonster::monsterai(Character& player, sf::RenderWindow& window, float elapsed){
  sf::Vector2f direction;
  if (!active) {
	return;
  }

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

//Attacks player if in range, then for timer.
    attacktimer += elapsed;
    if (getdistancetoplayer(player)<attackrange && attacktimer >= timebetweenattacks){
      attacktimer = 0.0;
      monsterattack(player);
    }
  }
  draw(window);
}

void MeleeMonster::monsterai(Character& player, sf::RenderWindow& window, float elapsed){
  sf::Vector2f direction;
  if(!active){
	return;
  }
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
    attacktimer += elapsed;
    if (getdistancetoplayer(player)<attackrange && attacktimer >= timebetweenattacks){
      attacktimer = 0.0;
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

//Creates a random monster at position determined by the position input.
void CreateMonster(sf::Vector2f positioni, Room* roomi, int leveli){
  int type;
  std::string name;

  srand(time(NULL));

  // Randomly select type. 1: Melee, 2: Ranged
  type = (rand() % 2) + 1;

  switch(type){
  case 1:{
    name = "ChopChop the Monstorous";

    //Name, health, xp on kill, attack damage, movespeed, aggrorange, attack range, room pointer, time between attacks.
    MeleeMonster newmonster1 = MeleeMonster(name, (rand() % 4)+leveli, leveli + 2, (rand()%3)+leveli, ((rand()%2)+1)*100.0f, 200.0f, (rand()%5)+10, roomi, 0.8f);

    newmonster1.setxypos(positioni.x, positioni.y);
    roomi->getmonsters().push_back(&newmonster1);
    break;
  }
  case 2:{
    name = "PewPew the Dastardly";

    //Name, health, xp on kill, attack damage, movespeed, aggrorange, projectilespeed, attack range, room pointer, time between attacks.
    RangedMonster newmonster2 = RangedMonster(name, (rand() % 3) + leveli, leveli + 2, (rand() % 3) + leveli, ((rand() % 2) + 1)*100.0f, 200.0f, ((rand() % 3) + 1)*90.0f,((rand() % 5)+10)*50, roomi, 0.8f);

    newmonster2.setxypos(positioni.x, positioni.y);
    roomi->getmonsters().push_back(&newmonster2);
    break;
  }
  }
}
