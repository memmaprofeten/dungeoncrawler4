
#include "weapon.hpp"
#include "projectile.hpp"
#include "room.hpp"
#include <string>
#include <iostream>
#include <cmath>

Weapon::~Weapon(){}
RangedWeapon::~RangedWeapon(){}
MeleeWeapon::~MeleeWeapon(){}

Weapon::Weapon(std::string n, int t, int d, float r, int txtrIndex) :
        name(n), type(t), damage(d), radius(r), textureIndex(txtrIndex) { }

Weapon::Weapon(int level, float seed){
  levels = level;
  seeds = seed;}

std::string Weapon::getName() const { return name; }

int Weapon::getType() const { return type; }

int Weapon::getDamage() const { return damage; }

//int Weapon::getRange() const { return range; }

float Weapon::getRadius() const { return radius; }

int Weapon::getProjectilespeed() const { return projectilespeed; }

Projectile& Weapon::createProjectile(Room& room) {
    return room.createProjectile(true, damage, radius, 250.0f, textureIndex);
}

int Weapon::gettextureindex() const{
  return textureIndex;
}

void Weapon::attack() {}

float Weapon::getcooldown() const{
  return cooldown;
}


RangedWeapon::RangedWeapon(const std::string name, int damage, int radius, int txtrIndex) : Weapon(name, 2, damage, radius, txtrIndex) { cooldown = 0.8f; }

RangedWeapon::RangedWeapon(int level, float seed) : Weapon (level, seed){
  srand(int(seed));
  type = 2;

  int generalname =(( rand()%2)+1);
  int nameaccent = ((rand()%5)+1);
  switch (generalname){
  case 1:{
    textureIndex = 1;
    switch(nameaccent){
    case 1:{
      name = "Ebonchill";
      break;
    }
    case 2:{
      name = "Dragonwrath";
      break;
    }
    case 3:{
      name = "Scepter of the Crystal Maiden";
      break;
    }
    case 4:{
      name = "Scythe of Elune";
      break;
    }
    case 5:{
      name = "Wand of the Burning Brand";
      break;
    }
    }
    break;
  }
  case 2:{
    textureIndex = 4;
    switch (nameaccent){
    case 1:{
      name = "Thori'dal";
      break;
    }
    case 2:{
      name = "Netherstrand Longbow";
      break;
    }
    case 3:{
      name = "Compound Bow of Swift Flight";
      break;
    }
    case 4:{
      name = "Crossbow of Kings";
      break;
    }
    case 5:{
      name = "Hunter's Compound Bow";
      break;
    }
    }
    break;
  }
  }

  //Speed of projectile vs. damage, faster projectiles should hurt more.
  int fast = ((rand()%100)+1); //How fast the projectile is.
  int heavy = 100-fast; //How much damage t he projectile should do.

  damage = ceil((rand()%4) + ((float(heavy)/100)*2*level));
  projectilespeed = float(150 + float(fast));
  cooldown = 0.5f + (float(heavy)/100);
  radius = 7.0f + 5.0f*(float(heavy)/100);
}


void RangedWeapon::attack() { }


MeleeWeapon::MeleeWeapon(const std::string name, int damage, int radius, int txtrIndex) : Weapon(name, 1, damage, radius, txtrIndex) {
  cooldown = 0.8f;
  minradius = 0;
  maxradius = 20.0f;
  angle = 120.0f;
}

MeleeWeapon::MeleeWeapon(int level, float seed) : Weapon(level, seed){
  srand(int(seed));
  type = 1;

  int type = rand()%4+1;
  int nameaccent = rand()%5+1;

  int fast = ((rand()%100)+1);
  int heavy = 100 - fast;

  switch (type){
  case 1:{ //Sword
    cooldown = 0.4f + (float(heavy)/100) ;
    damage = ceil((rand()%4) + ((float(heavy)/100)*2*level));
    minradius = 0;
    maxradius = 25.0f;
    angle = 120.0f;

    switch(nameaccent){
    case 1:{
      name = "Vorpal Blade";
      break;
    }
    case 2:{
      name = "Frostmourne";
      break;
    }
    case 3:{
      name = "Shall'ator";
      break;
    }
    case 4:{
      name = "Foecleaver";
      break;
    }
    case 5:{
      name = "Jade Tiger";
      break;
    }
    }

    break;
  }
  case 2:{//Dagger
    cooldown = 0.3f + (float(heavy)/100);
    damage = ceil((rand()%3) + ((float(heavy)/100)*2*level));
    minradius = 0;
    maxradius = 15.0f;
    angle = 90.0f;

    switch(nameaccent){
    case 1:{
      name = "Thunderfury, Blessed Blade of the Windseeker";
      break;
    }
    case 2:{
      name = "Warglaive of Azzinoth";
      break;
    }
    case 3:{
      name = "Anguish";
      break;
    }
    case 4:{
      name = "Fang of the Devourer";
      break;
    }
    case 5:{
      name = "Sapphire Combat Knife";
      break;
    }
    }

    break;
  }

  case 3:{//Polearm
    cooldown = 0.5f + (float(heavy)/100);
    damage = ceil((rand()%5) + ((float(heavy)/100)*2*level));
    minradius = 10.0f;
    maxradius = 50.0f;
    angle = 60.0f;

    switch(nameaccent){
    case 1:{
      name = "Talonwrath";
      break;
    }
    case 2:{
      name = "The Wanderer's Companion";
      break;
    }
    case 3:{
      name = "Warspear of the Elder Forest";
      break;
    }
    case 4:{
      name = "Glaive-Fauchard-Bardiche-Voulge";
      break;
    }
    case 5:{
      name = "Staff of the Monkey King";
      break;
    }
    }
    break;
  }
  case 4:{//Flails/maces/etc
    cooldown = 0.6f + (float(heavy)/100);
    damage = ceil((rand()%3) + ((float(heavy)/100)*2*level));
    minradius = 0;
    maxradius = 25.0f;
    angle = 360.0f;

    switch(nameaccent){
    case 1:{
      name = "Sulfuras";
      break;
    }
    case 2:{
      name = "Golden Scourge";
      break;
    }
    case 3:{
      name = "The Silver Hand";
      break;
    }
    case 4:{
      name = "Scale of the Earthwarden";
      break;
    }
    case 5:{
      name = "Scepter of Sargeras";
      break;
    }
    }
    break;
  }
  }

  textureIndex = 1;
  radius = 0;
  projectilespeed = 0;
}

void MeleeWeapon::attack() { }
