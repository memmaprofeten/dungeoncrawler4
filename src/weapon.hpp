#include <string>
#include <vector>
#include <iostream>

class Weapon {
public:
	Weapon(const bool t, const int d, int r) :
	type(t), damage(d), range(r) { }

	const bool getType() const { return type; }
	const int getDamage() const { return damage; }
	const int getRange() const { return range; }
	const int getProjectilespeed() const { return projectilespeed; }
	
	virtual void attack() {}

private:
	bool type; //True = Ranged, False = Melee.
	int damage;
	int range;
	float projectilespeed;
	//lifespan?(do people like this kind of feature?)
};


class RangedWeapon : public Weapon {
public:
	RangedWeapon() : Weapon(true, 0, 10) { }

	virtual void attack() { }
};


class MeleeWeapon : public Weapon {
public:
	MeleeWeapon() : Weapon(false, 0, 50) { }

	virtual void attack() { }
};
