#ifndef WEAPON_HH
#define WEAPON_HH
#include <string>
#include <vector>
#include <iostream>

class Weapon {
public:
	Weapon(const std::string n, const bool t, const int d, int r) :
	name(n), type(t), damage(d), range(r) { }
	
	const std::string getName() { return name; }
	const bool getType() const { return type; }
	const int getDamage() const { return damage; }
	const int getRange() const { return range; }
	const int getProjectilespeed() const { return projectilespeed; }
	
	virtual void attack() {}

private:
	std::string name;
	bool type; //True = Ranged, False = Melee.
	int damage;
	int range;
	float projectilespeed;
	//lifespan?(do people like this kind of feature?)
};


class RangedWeapon : public Weapon {
public:
	RangedWeapon(const std::string name) : Weapon(name, true, 0, 10) { }

	virtual void attack() { }
};


class MeleeWeapon : public Weapon {
public:
	MeleeWeapon(const std::string name) : Weapon(name, false, 0, 50) { }

	virtual void attack() { }
};

#endif