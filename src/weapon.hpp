#ifndef WEAPON_HH
#define WEAPON_HH
#include <string>
#include <vector>
#include <iostream>
#include "projectile.hpp"

class Weapon {
public:
	Weapon(const std::string n, const bool t, const int d, float r, int txtrIndex) :
			name(n), type(t), damage(d), radius(r), textureIndex(txtrIndex) { }

	std::string getName() const { return name; }
	bool getType() const { return type; }
	int getDamage() const { return damage; }
	//int getRange() const { return range; }
	float getRadius() const { return radius; }
	int getProjectilespeed() const { return projectilespeed; }

	Projectile& createProjectile(Room& room) {
		return room.createProjectile(true, damage, radius, 250.0f, textureIndex);
	}

	virtual void attack() {}

private:
	std::string name;
	bool type; //True = Ranged, False = Melee.
	int damage;
	//int range;		// TODO: Readd this again if we think it's necessary
	float radius;
	float projectilespeed;
	int textureIndex;
};


class RangedWeapon : public Weapon {
public:
	RangedWeapon(const std::string name, int damage, int radius, int txtrIndex) : Weapon(name, true, damage, radius, txtrIndex) { }

	virtual void attack() { }
};


class MeleeWeapon : public Weapon {
public:
	MeleeWeapon(const std::string name, int damage, int radius, int txtrIndex) : Weapon(name, false, damage, radius, txtrIndex) { }

	virtual void attack() { }
};

#endif
