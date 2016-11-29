#ifndef WEAPON_HH
#define WEAPON_HH
#include <string>
#include <vector>
#include <iostream>
#include "projectile.hpp"

class Weapon {
public:
	Weapon(const std::string n, const bool t, const int d, int r, std::string tx="../resources/img/projectile_32.png") :
	name(n), type(t), damage(d), range(r), textureFile(tx) { }

	std::string getName() const { return name; }
	bool getType() const { return type; }
	int getDamage() const { return damage; }
	int getRange() const { return range; }
	int getProjectilespeed() const { return projectilespeed; }
	
	Projectile createProjectile() {
		Projectile p(true, damage, range, 250.0f, textureFile);
		return p;
	}
	
	virtual void attack() {}

private:
	std::string name;
	bool type; //True = Ranged, False = Melee.
	int damage;
	int range;
	float projectilespeed;
	std::string textureFile;
	//lifespan?(do people like this kind of feature?)
};


class RangedWeapon : public Weapon {
public:
	RangedWeapon(const std::string name, int damage, int range, const std::string textureFile) : Weapon(name, true, damage, range, textureFile) { }

	virtual void attack() { }
};


class MeleeWeapon : public Weapon {
public:
	MeleeWeapon(const std::string name, int damage, int range, const std::string textureFile) : Weapon(name, false, damage, range, textureFile) { }

	virtual void attack() { }
};

#endif
