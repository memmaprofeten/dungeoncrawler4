#ifndef WEAPON_HH
#define WEAPON_HH
#include <string>
#include <vector>

class Room;
class Projectile;

class Weapon {
public:
    Weapon(std::string n, int t, int d, float r, int txtrIndex);      // type 1: Melee, type 2: Ranged
    std::string getName() const;
    int getType() const;
    int getDamage() const;
    //int getRange() const;
    float getRadius() const;  // TODO: Is this one being used? Remove if it is not.
    virtual float getMinRadius() const;
    virtual float getMaxRadius() const;
    int getProjectilespeed() const;
    Projectile& createProjectile(Room& room);
    float getcooldown() const;
    int gettextureindex() const;
    virtual void attack();
    virtual ~Weapon(); // LIKELY TO CAUSE NEW AND EXCITING ISSUES. DANGERZONE.
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

    ~RangedWeapon();
};


class MeleeWeapon : public Weapon {
public:
    MeleeWeapon(std::string name, int damage, int radius, int txtrIndex); //Specific weapon constructor.
    MeleeWeapon(int level, float seed); // Random weapon constructor.
    virtual void attack();

    virtual float getMinRadius() const override;
    virtual float getMaxRadius() const override;

    ~MeleeWeapon();
private:
    float minradius;
    float maxradius;
    float angle;
};

#endif
