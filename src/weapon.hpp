#ifndef WEAPON_HH
#define WEAPON_HH
#include <string>
#include <vector>
#include <iostream>
#include "projectile.hpp"

class Weapon {
public:
	Weapon(const std::string n, const bool t, const int d, int r, int txtrIndex) :
			name(n), type(t), damage(d), range(r), textureIndex(txtrIndex) { }

	std::string getName() const { return name; }
	bool getType() const { return type; }
	int getDamage() const { return damage; }
	int getRange() const { return range; }
	int getProjectilespeed() const { return projectilespeed; }

	Projectile& createProjectile(Room& room) {
		return room.createProjectile(true, damage, range, 250.0f, textureIndex);
	}

	virtual void attack() {}

private:
	std::string name;
	bool type; //True = Ranged, False = Melee.
	int damage;
	int range;
	float projectilespeed;
	int textureIndex;
	//NB! lifespan?(do people like this kind of feature?)		// Not in my opinion, but I don't know :) - Jon
};


class RangedWeapon : public Weapon {
public:
	RangedWeapon(const std::string name, int damage, int range, int txtrIndex) : Weapon(name, true, damage, range, txtrIndex) { }

	virtual void attack() { }
};


class MeleeWeapon : public Weapon {
public:
	MeleeWeapon(const std::string name, int damage, int range, int txtrIndex) : Weapon(name, false, damage, range, txtrIndex) { }

	virtual void attack() { }
};

#endif
