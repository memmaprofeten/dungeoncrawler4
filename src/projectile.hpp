#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <SFML/Graphics.hpp>
#include "settings.hpp"

class Room;

/**
 * A class representing a projectile fired by the player or by an enemy.
 */
class Projectile {
public:

    /**
     * Whether not this projectile was fired by a player.
     */
    bool isfiredbyplayer();

    /**
     * Whether or not this projectile is currently active.
     */
    bool isActive();

    /**
     * Overwrites the projectile with new information for reuse.
     */
    void reset(bool shotbyplayer, int damagein, int radiusin, float speedin, int txtrIndex);

    /**
    * Returns the current position of the projectile in worldspace.
    */
    sf::Vector2f getPosition();

    /**
    * Sets the projectile's position in worldspace to the position given as
    * parameter.
    */
    void setPosition(sf::Vector2f position);

    /**
    * Returns the current velocity of the projectile.
    */
    sf::Vector2f getVelocity();

    /**
    * Sets the projectile's velocity direction to the direction given as
    * parameter. The direction is defined as a 2D unit vector, so the given
    * vector will be normalized.
    */
    void setDirection(sf::Vector2f direction);

    /**
     * Returns the nominal speed of the projectile.
     */
    float getSpeed() const;

    /**
    * Sets the projectile's speed.
    */
    void setSpeed(float newSpeed);

    /**
     * Returns the damage value of this projectile.
     */
    int getdamage() const;

    /**
     * Returns the nominal attack radius of this projectile.
     */
    int getradius() const;

    /* Called to deactivate projectile, eg when it has hit a soft target */
    void deactivate();

    /**
    * Performs necessary calculations, such as computing its new position, and
    * draws itself.
    * The method takes as input a reference to the window to which it needs to
    * draw itself and a float defining the time elapsed since the last frame.
    */
    void draw(sf::RenderWindow& window, float elapsed);

    /**
     * Constructor of the projectile.
     * NB! To add a projectile to a room, do not call this constructor explicitly!
     * Use the Room class interface instead.
     */
    Projectile(Room* currentRoom, bool shotbyplayer, int damagein, int radiusin, float speed, int txtrIndex);

private:
    Room* room;                 // A pointer to the room that this projectile is currently in
    bool firedbyplayer;         // Player projectiles damage enemies and vice versa
    bool active;                // Whether or not this projectile is "active" (i.e. exists) and should be drawn. NB! An arrow stuck in a wall is also considered "active".
    sf::Vector2f pos;           // The projectile's position in world space
    sf::Vector2f dir;           // The 2D direction in which the projectile is moving
    float speed;                // The absolute speed that the projectile has
    int damage;                 // Damage dealt by projectile
    int radius;                 // Radius of projectile for drawing / hit detection
    float rotation;             // Rotation, connected to the direction
    int textureIndex;           // The texture index of this projectile
    sf::Texture texture;        // The texture of this projectile
    sf::Sprite sprite;          // The sprite of this projectile
};

#endif
