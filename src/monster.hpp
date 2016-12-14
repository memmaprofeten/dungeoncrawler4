#ifndef MONSTER_HH
#define MONSTER_HH

#include "projectile.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Character;
class Item;
class Room;

/**
 * An abstract class representing an enemy in the game.
 * A monster is restricted to a room and its purpose is to destroy the player.
 */
class Monster{
public:

    /**
     * The monster constructor
     */
    Monster();

    /**
     * The monster destructor
     */
    virtual ~Monster();

    /**
     * Returns the name of the monster
     */
    std::string getname() const;

    /**
     * Returns the current health of the monster
     */
    int gethealth() const;

    /**
     * Returns the amount of xp the monster gives upon death
     */
    int getxponkill() const;

    /**
     * Returns the monster's attack damage
     */
    int getattackdamage() const ;

    /**
     * Returns the monster's movement speed
     */
    float getmovespeed() const;

    /**
     * Returns the monster's aggression range (the distance at which it can
     * notice the player's presence)
     */
    float getaggrorange() const;

    /**
     * Returns the monster's current position
     */
    sf::Vector2f getPosition() const;

    /**
     * Sets the monster's position
     */
    void setPosition(sf::Vector2f newPos);

    /**
     * Move the monster by the given vector
     */
    void move(sf::Vector2f dPos);

    /**
     * Returns whether or not the monster is currently active
     */
    bool isactive() const;

    /**
     * Reduce monster health. To be called by whatever handles the monster
     * getting hit. Also checks if the monster has died and acts accordingly.
     */
    void reducehealth(int reducedby);

    /**
     * Returns whether or not the monster is currently in aggressive mode.
     */
    bool monsteraggrocheck(const Character& player) const;

    /**
     * Returns the current distance to the player.
     */
    float getdistancetoplayer(const Character& player) const ;

    /**
     * Calls the monster attack depending on subclass.
     */
    virtual void monsterattack(Character& player) =0;

    /**
     * Calls the monster AI depending on subclass.
     */
    virtual void monsterai(Character& player, float elapsed) =0;

    /**
     * Moves the monster in the given direction depending on the elapsed time.
     */
    void monstermove(sf::Vector2f direction, float elapsed);

    /**
     * Teleports the monster from their current position based on the vector given as an input.   
     */
     void teleport(sf::Vector2f dpos);
  
protected:
    std::string monstername;            // Enemy name.
    int health;                         // Enemy health.
    int xponkill;                       // Experience given to player when killed.
    int attackdamage;                   // Damage dealt on attack.
    float movespeed;                    // Movementspeed of enemy.
    float aggrorange;                   // AI Parameter. How close the player has to be for the AI to aggro.
    sf::Vector2f position;              // The monster's position
    Room* room;                         // Pointer to the room that the monster is currently in
    bool aggrostate;                    // If the monster is actively chasing/attacking the player.
    float attacktimer;                  // Amount of time inbetween attacks.
    float timebetweenattacks;           // The attack cooldown
    bool active;                        // Whether or not the monster is currently active
    sf::Sprite* sprite;                 // Pointer to sprite object
    int textureIndex;                   // The texture index of the monster
    sf::Sound sound;                    // The monster's sound object
};

/**
 * A subclass to Monster, RangedMonster represents a monster whose primary
 * attack is a ranged one. These monsters will attempt to destroy the player
 * from a distance.
 */
class RangedMonster : public Monster {
public:

    /**
     * RangedMonster general constructor
     * Constructs a specific ranged monster based on the given parameters.
     */
    RangedMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, float aggrorangei, float projectilespeedi, float attackrangei, Room* roomi, /*std::vector<Projectile>* projectiles*/ float timebetweenattacksi);

    /**
     * RangedMonster random constructor
     * Creates a random ranged monster.
     */
    RangedMonster(sf::Vector2f positioni, Room* roomi, int leveli);

    /**
     * The RangedMonster Destructor
     */
    ~RangedMonster();

    /**
     * Fires at the player if in range.
     */
    void monsterattack(Character& player);

    /**
     * Tries to find the player and advance towards them.
     */
    void monsterai(Character& player, float elapsed);

private:
    float projectilespeed;          // How fast the projectile fired by the enemy moves
    float attackrange;              // At what distance the enemy attacks
};

/**
 * A subclass to Monster, MeleeMonster represents a monster whose primary
 * attack is a melee one. These monsters will attempt to destroy the player
 * by charging them and bashing away.
 */
class MeleeMonster : public Monster{
public:

    /**
     * MeleeMonster general constructor
     * Constructs a specific melee monster based on the given parameters.
     */
    MeleeMonster(std::string namei, int healthi, int xponkilli, int attackdamagei, float movespeedi, float aggrorangei, int attackrangei, Room* roomi, float timebetweenattacksi);

    /**
     * MeleeMonster random constructor
     * Creates a random melee monster.
     */
    MeleeMonster(sf::Vector2f positioni, Room* roomi, int leveli);

    /**
     * The MeleeMonster Destructor
     */
    ~MeleeMonster();

    /**
     * Hits the player if in range.
     */
    void monsterattack(Character& player);

    /**
     * Tries to find the player and advance towards them.
     */
    void monsterai(Character& player, float elapsed);

private:
    int attackrange;                // Radius of the enemy's attack swing
};

#endif
