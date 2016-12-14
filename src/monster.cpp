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
#include <math.h>
#include <string.h>
#include <vector>

Monster::Monster() {}
Monster::~Monster() {}

std::string Monster::getname() const {
    return monstername;
}
int Monster::gethealth() const {
    return health;
}

int Monster::getxponkill() const {
    return xponkill;
}

int Monster::getattackdamage() const {
    return attackdamage;
}

float Monster::getmovespeed() const {
    return movespeed;
}

float Monster::getaggrorange() const {
    return aggrorange;
}

sf::Vector2f Monster::getPosition() const {
    return position;
}

void Monster::setPosition(sf::Vector2f newPos){
    position = newPos;
}

void Monster::move(sf::Vector2f dPos){
    position += dPos;
}

bool Monster::isactive() const{
    return active;
}

void Monster::monstermove(sf::Vector2f direction, float elapsed){
  	sf::Vector2f dpos = elapsed * movespeed * direction;
    if (room == NULL) {
        throw std::runtime_error("Monster has no room assigned!");
    }
    if (room->hasPosition(position + dpos)) {        // Make sure the monster is not moving out of bounds (monsters can't follow the player into new rooms)
        sf::Vector2f dposHor = sf::Vector2f(dpos.x, 0);
        sf::Vector2f dposVer = sf::Vector2f(0, dpos.y);
        Tile& horTile = room->getTile(position + dposHor);
        Tile& verTile = room->getTile(position + dposVer);
        if (horTile.isPenetrable()) {
            position += dposHor;
        }
        if (verTile.isPenetrable()) {
            position += dposVer;
        }
        sprite->setPosition(position);
	float rotation = (atan2(direction.y,direction.x)) * 180 / cv::PI;
	sprite->setRotation(s::monsterRotationOffset + rotation);
    }

}

void Monster::reducehealth(int reducedby){
    health -= reducedby;
    if (reducedby > 0) {
        sound.setBuffer(s::soundbuffers[7 + rand() % 2]);
        sound.play();
    }
    if(health <= 0){
        active = false;     // Sets monster as inactive
        room->additem(new Item(position, room->getcharacter()->getlevel()));    // Drops item:
        room->getcharacter()->givexp(xponkill);     // Awards player XP
        room->deactivateSprite(sprite);
    }
}

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
    timebetweenattacks = timebetweenattacksi;
    attacktimer = 0.0;
    active = true;
    textureIndex = 22;
    sprite = room->getSprite();
    sprite->setOrigin(16.0f,16.0f);
    sprite->setTexture(s::textures[textureIndex]);
    sprite->setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
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
    textureIndex = 21;
    sprite = room->getSprite();
    sprite->setOrigin(16.0f,16.0f);
    sprite->setTexture(s::textures[textureIndex]);
    sprite->setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
}

MeleeMonster::~MeleeMonster() {}

bool Monster::monsteraggrocheck(const Character& player) const {
    if (getdistancetoplayer(player) < aggrorange) {
        return true;
    } else {
        return false;
    }
}

float Monster::getdistancetoplayer(const Character& player) const {
    return cv::distance(player.getPosition(), position);
}

void RangedMonster::monsterattack(Character& player){
    if (getdistancetoplayer(player) < attackrange){
        Projectile& projectile = room->createProjectile(false, attackdamage, 0.8f * s::blockDim, projectilespeed, 4);
        projectile.setPosition(position);
        projectile.setDirection(cv::normalized(player.getPosition() - position));
    }
}

void MeleeMonster::monsterattack(Character& player){
    if (getdistancetoplayer(player) <= attackrange){
        player.reducehealth(attackdamage);
        player.teleport(cv::normalized(player.getPosition() - position) * 2.0f);
    }
}

void RangedMonster::monsterai(Character& player, float elapsed){
    /* Code for the AI of the monsters. Essentially. It first checks if the player is within aggrorange. If it is, it flips the aggrostate to true.
    Then, the monster will move towards the player.
    After that, it attacks the player if it is within range. */
    sf::Vector2f direction;
    if (!active) {
        return;
    }

    if (monsteraggrocheck(player)){
        aggrostate = true;
    }

    if(aggrostate) {

        //Determines direction. Will be replaced by pathfinding later:
        direction = player.getPosition() - position;
        direction = cv::normalized(direction);

        //Moves enemy in chosen direction:
	if (getdistancetoplayer(player) >= 12){
	  monstermove(direction, elapsed);
	}
        //Attacks player if in range, then for timer:
        attacktimer += elapsed;
        if (getdistancetoplayer(player)<attackrange && attacktimer >= timebetweenattacks){
            attacktimer = 0.0;
            monsterattack(player);
        }
    }
}

void MeleeMonster::monsterai(Character& player, float elapsed){
    sf::Vector2f direction;
    if(!active){
        return;
    }
    if (monsteraggrocheck(player)){
        aggrostate = true;
    }

    if(aggrostate){
        //Determines direction. Could be replaced by pathfinding later:
        direction = player.getPosition() - position;
        direction = cv::normalized(direction);

        //Moves enemy in chosen direction:
	if (getdistancetoplayer(player) >=8){
	  monstermove(direction, elapsed);
	}

        //Attacks player if in range:
        attacktimer += elapsed;
        if (getdistancetoplayer(player)<attackrange && attacktimer >= timebetweenattacks){
            attacktimer = 0.0;
            monsterattack(player);
        }
    }

}

RangedMonster::RangedMonster(sf::Vector2f positioni, Room* roomi, int leveli){
    monstername = "PewPew the Dastardly";
	health = (rand() % 3) + leveli;
	xponkill = leveli + 3;
	attackdamage =  (rand() % 3) + leveli/2;
	movespeed = ((rand()%2)+1)*35.0f;
	aggrorange = 200.0f;
	projectilespeed = ((rand() % 3) + 1)*90.0f;
	attackrange = ((rand() % 5)+10)*50;
	room = roomi;
	timebetweenattacks = 0.8f;
	position = positioni;
	active = true;
	attacktimer = 0;
	textureIndex = 22;
	sprite = room->getSprite();
	sprite->setOrigin(16.0f,16.0f);
	sprite->setTexture(s::textures[textureIndex]);
	sprite->setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
}

MeleeMonster::MeleeMonster(sf::Vector2f positioni, Room* roomi, int leveli){
    monstername = "ChopChop the Dangerous";
	health = (rand() % 4)+leveli;
	xponkill = leveli + 2;
	attackdamage = (rand()%2)+leveli/2;
	movespeed = ((rand()%2)+1)*20.0f;
	aggrorange = 200.0f;
	attackrange = (rand()%5)+10;
	room = roomi;
	timebetweenattacks = 0.8f;
	position = positioni;
	active = true;
	attacktimer = 0;
	textureIndex = 21;
	sprite = room->getSprite();
	sprite->setOrigin(16.0f,16.0f);
	sprite->setTexture(s::textures[textureIndex]);
	sprite->setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
}

void Monster::teleport(sf::Vector2f dpos){
  if (room == NULL){
    throw std::runtime_error("Monster has no room assigned!");
  }
  
  if(room->hasPosition(position+dpos)){
    sf::Vector2f dposhor = sf::Vector2f(dpos.x, 0);
    sf::Vector2f dposver = sf::Vector2f(0, dpos.y);

    Tile& horTile = room->getTile(position + dposhor);
    Tile& verTile = room->getTile(position + dposver);

    if (horTile.isPenetrable()){
      position += dposhor;
      sprite->move(dpos.x,0);
    }
    if (verTile.isPenetrable()){
      position += dposver;
      sprite->move(0,dpos.y);
    }
  }
}
