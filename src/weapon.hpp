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

protected:
  Weapon(int level, float seed);
  std::string name;
  int type; // 1 = melee, 2 = ranged.
  int damage;
  //int range;		// TODO: Readd this again if we think it's necessary
  float radius;
  int textureIndex;
  float projectilespeed;
  float cooldown;
  int levels;
  float seeds;
};


class RangedWeapon : public Weapon {
public:
  RangedWeapon(std::string name, int damage, int radius, int txtrIndex);//Specific constructor.
  RangedWeapon(int level, float seed);//Random weapon constructor.
  virtual void attack();
};


class MeleeWeapon : public Weapon {
public:
  MeleeWeapon(std::string name, int damage, int radius, int txtrIndex); //Specific weapon constructor.
  MeleeWeapon(int level, float seed); // Random weapon constructor.
	virtual void attack();
private:
  float minradius;
  float maxradius;
  float angle;
};

#endif
