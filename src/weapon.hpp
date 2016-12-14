#ifndef WEAPON_HH
#define WEAPON_HH
#include <string>
#include <vector>

class Room;
class Projectile;

/**
 * The general Weapon class, representing a weapon in the game.
 * This class can have several child classes for polymorphic behaviour.
 * Additionally, the main weapon type is defined by an integer as follows:
 *          - 1: Melee
 *          - 2: Ranged
 */
class Weapon {
public:

    /**
     * The general Weapon constructor
     * Constructs a specific weapon based on the given parameters.
     */
    Weapon(std::string n, int t, int d, int txtrIndex);

    /**
     * The Weapon destructor.
     */
    virtual ~Weapon();

    /**
     * Returns the name of the weapon
     */
    std::string getName() const;

    /**
     * Returns the type of the weapon, as an integer as follows:
     *          - 1: Melee
     *          - 2: Ranged
     */
    int getType() const;

    /**
     * Returns the damage of the weapon
     */
    int getDamage() const;

    /**
     * Returns the minimum radius of the weapon (e.g. the radius of the circle
     * within which the weapon is ineffective), if it is relevant. If it is not,
     * e.g. for range-only weapons, returns a negative number.
     */
    virtual float getMinRadius() const;

    /**
     * Returns the maximum radius of the weapon (e.g. the radius of the circle
     * within which the weapon is effective, as long as it is outside the circle
     * defined by minRadius), if it is relevant. If it is not, e.g. for
     * range-only weapons, returns a negative number.
     */
    virtual float getMaxRadius() const;

    /**
     * Returns the projectile speed of projectiles fired by this weapon.
     */
    int getProjectilespeed() const;

    /**
     * Creates a projectile in the given room as fired by this weapon, and
     * returns a reference to it.
     */
    Projectile& createProjectile(Room& room);

    /**
     * Returns the cooldown of this weapon.
     */
    float getcooldown() const;

    /**
     * Returns the texture index of this weapon.
     */
    int gettextureindex() const;

    /**
     * Returns the texture index of this weapon's projectile.
     */
    int getprojectiletextureindex() const;

    /**
     * Performs an attack.
     */
    virtual void attack();

protected:

    /**
     * A partial constructor to be called by child constructors.
     */
    Weapon(int level, float seed);

    std::string name;                       // The name of the weapon
    int type;                               // The (main) type of weapon (1 for melee, 2 for ranged)
    int damage;                             // The weapon damage
    int textureIndex;                       // The texture index of the weapon
    int projectileTextureIndex;             // The texture index of the projectiles fired by this weapon (to be disregarded if this weapon does not create projectiles)
    float projectilespeed;                  // The speed of projectiles fired by the weapon
    float cooldown;                         // The weapon cooldown
    int levels;                             // The player's level when the weapon was generated (for progress-based random generation purposes)
    float seeds;                            // The random seed of the weapon generation. NB! Not currently in use.
};

/**
 * The RangedWeapon class represents a ranged weapon, such as a bow or a magic
 * staff, whose primary attack is launching projectiles.
 */
class RangedWeapon : public Weapon {
public:

    /**
     * The general RangedWeapon constructor
     * Constructs a specific ranged weapon based on the given parameters.
     */
    RangedWeapon(std::string name, int damage, int txtrIndex, int projectileTxtrIndex);

    /**
     * The randomized RangedWeapon constructor
     * Constructs a random ranged weapon based on the player's level.
     */
    RangedWeapon(int level, float seed);

    /**
     * The RangedWeapon destructor
     */
    ~RangedWeapon();

    /**
     * Performs an attack.
     */
    virtual void attack();

};

/**
 * The MeleeWeapon class represents a close combat weapon, such as a sword or
 * a spear, whose primary attack is direct melee strikes.
 */
class MeleeWeapon : public Weapon {
public:

    /**
     * The general MeleeWeapon constructor
     * Constructs a specific melee weapon based on the given parameters.
     */
    MeleeWeapon(std::string name, int damage, float minR, float maxR, int txtrIndex);

    /**
     * The randomized MeleeWeapon constructor
     * Constructs a random melee weapon based on the player's level.
     */
    MeleeWeapon(int level, float seed);

    /**
     * The MeleeWeapon destructor
     */
    ~MeleeWeapon();

    /**
     * Performs an attack.
     */
    virtual void attack();

    /**
     * Returns the minimum radius of the weapon (e.g. the radius of the circle
     * within which the weapon is ineffective).
     */
    virtual float getMinRadius() const override;

    /**
     * Returns the maximum radius of the weapon (e.g. the radius of the circle
     * within which the weapon is effective, as long as it is outside the circle
     * defined by minRadius).
     */
    virtual float getMaxRadius() const override;

private:
    float minradius;                // The minimum radius of effective attack
    float maxradius;                // The maximum radius of effective attack
    float angle;                    // The angle of effective attack
};

#endif
