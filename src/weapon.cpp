#include "weapon.hpp"
#include "projectile.hpp"
#include "room.hpp"
#include <string>
#include <iostream>

Weapon::Weapon(std::string n, bool t, int d, float r, int txtrIndex) :
        name(n), type(t), damage(d), radius(r), textureIndex(txtrIndex) { }

std::string Weapon::getName() const { return name; }

bool Weapon::getType() const { return type; }

int Weapon::getDamage() const { return damage; }

//int Weapon::getRange() const { return range; }

float Weapon::getRadius() const { return radius; }

int Weapon::getProjectilespeed() const { return projectilespeed; }

Projectile& Weapon::createProjectile(Room& room) {
    return room.createProjectile(true, damage, radius, 250.0f, textureIndex);
}

void Weapon::attack() {}



RangedWeapon::RangedWeapon(const std::string name, int damage, int radius, int txtrIndex) : Weapon(name, true, damage, radius, txtrIndex) { }

void RangedWeapon::attack() { }



MeleeWeapon::MeleeWeapon(const std::string name, int damage, int radius, int txtrIndex) : Weapon(name, false, damage, radius, txtrIndex) { }

void MeleeWeapon::attack() { }
