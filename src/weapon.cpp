
#include "weapon.hpp"
#include "projectile.hpp"
#include "room.hpp"
#include <string>
#include <iostream>
#include <cmath>

Weapon::~Weapon(){}

RangedWeapon::~RangedWeapon(){}

MeleeWeapon::~MeleeWeapon(){}

Weapon::Weapon(std::string n, int t, int d, int txtrIndex) :
        name(n), type(t), damage(d), textureIndex(txtrIndex) { }

Weapon::Weapon(int level, float seed){
    levels = level;
    seeds = seed;
}

std::string Weapon::getName() const { return name; }

int Weapon::getType() const { return type; }

int Weapon::getDamage() const { return damage; }

float Weapon::getMinRadius() const { return -1.0f; }

float Weapon::getMaxRadius() const { return -1.0f; }

int Weapon::getProjectilespeed() const { return projectilespeed; }

Projectile& Weapon::createProjectile(Room& room) {
    return room.createProjectile(true, damage, s::projectileRadius, 250.0f, textureIndex);
}

int Weapon::gettextureindex() const{
    return textureIndex;
}

void Weapon::attack() {}

float Weapon::getcooldown() const{
    return cooldown;
}


RangedWeapon::RangedWeapon(const std::string name, int damage, int txtrIndex) : Weapon(name, 2, damage, txtrIndex) { cooldown = 0.8f; }

RangedWeapon::RangedWeapon(int level, float seed) : Weapon (level, seed){
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

    //Speed of projectile vs. damage, faster projectiles should hurt more:
    int fast = ((rand()%100)+1);    // How fast the projectile is.
    int heavy = 100-fast;           // How much damage the projectile should do.

    damage = rand() % 3 + 1 + int(float(heavy) / 100.0f * 2.0f * (float)level);
    projectilespeed = 150.0f + float(fast);
    cooldown = 0.5f + (float(heavy)/100);
}

void RangedWeapon::attack() { }

MeleeWeapon::MeleeWeapon(const std::string name, int damage, float minR, float maxR, int txtrIndex) : Weapon(name, 1, damage, txtrIndex) {
    cooldown = 0.8f;
    minradius = minR;
    maxradius = maxR;
    angle = 120.0f;
}

MeleeWeapon::MeleeWeapon(int level, float seed) : Weapon(level, seed){
    type = 1;
    int type = rand()%4+1;
    int nameaccent = rand()%5+1;
    int fast = ((rand()%100)+1);
    int heavy = 100 - fast;

    switch (type){
        case 1:{ //Sword
            cooldown = 0.4f + (float(heavy)/100) ;
            damage = rand() % 3 + 1 + int(float(heavy) / 100.0f * 2.0f * (float)level);
            minradius = 0;
            maxradius = 25.0f;
            angle = 120.0f;
            textureIndex = 8;

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
        case 2:{ //Dagger
            cooldown = 0.3f + (float(heavy)/100);
            damage = rand() % 2 + 1 + int(float(heavy) / 100.0f * 2.0f * (float)level);
            minradius = 0;
            maxradius = 15.0f;
            angle = 90.0f;
            textureIndex = 8;

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

        case 3:{ //Polearm
            cooldown = 0.5f + (float(heavy)/100);
            damage = rand() % 5 + 1 + int(float(heavy) / 100.0f * 2.0f * (float)level);
            minradius = 10.0f;
            maxradius = 50.0f;
            angle = 60.0f;
            textureIndex = 19;

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
        case 4:{ //Flails/maces/etc
            cooldown = 0.6f + (float(heavy)/100);
            damage = rand() % 3 + 1 + int(float(heavy) / 100.0f * 2.0f * (float)level);
            minradius = 0;
            maxradius = 25.0f;
            angle = 360.0f;
            textureIndex = 14;

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

    projectilespeed = 0;
}

void MeleeWeapon::attack() { }

float MeleeWeapon::getMinRadius() const { return minradius; }

float MeleeWeapon::getMaxRadius() const { return maxradius; }
