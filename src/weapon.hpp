#ifndef WEAPON_HH
#define WEAPON_HH
#include <string>
#include <vector>

class Room;
class Projectile;

class Weapon {
public:
	Weapon(std::string n, bool t, int d, float r, int txtrIndex);

	std::string getName() const;
	bool getType() const;
	int getDamage() const;
	//int getRange() const;
	float getRadius() const;
	int getProjectilespeed() const;

	Projectile& createProjectile(Room& room);

	virtual void attack();

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
	RangedWeapon(std::string name, int damage, int radius, int txtrIndex);

	virtual void attack();
};


class MeleeWeapon : public Weapon {
public:
	MeleeWeapon(std::string name, int damage, int radius, int txtrIndex);

	virtual void attack();
};

#endif
