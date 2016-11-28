#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <SFML/Graphics.hpp>
#include "room.hpp"
/*Base class, for projectile attacks fired by player or by enemies.
*/

class Projectile {
public:
/*
Has:
Constructor (xspeed and yspeed. How much the position is iterated per tick/loop/etc. Damage dealt by projectile. Projectile hitradius.)
Functions to access said values.
Function to iterate per tick that moves projectile, then checks for collision.
Function that can be called by player or monster attack that creates the projectile.
*/
  bool isfiredbyplayer();

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
   * Sets the projectile's speed.
   */
  void setSpeed(float newSpeed);

  int getdamage();

  int getradius();

  /**
   * Performs necessary calculations, such as computing its new position, and
   * draws itself.
   * The method takes as input a reference to the window to which it needs to
   * draw itself and a float defining the time elapsed since the last frame.
   */
  void draw(sf::RenderWindow& window, float elapsed, Room& currentRoom);

  Projectile(bool shotbyplayer, int damagein, int radiusin, float speed);

private:
  bool firedbyplayer; //Player projectiles damage enemies and vice versa.
  sf::Vector2f pos;     // The projectile's position in world space
  sf::Vector2f dir;     // The 2D direction in which the projectile is moving
  float speed;          // The absolute speed that the projectile has
  int damage; //Damage dealt by projectile.
  int radius; //Radius of projectile for drawing / hit detection.
};

//void createprojectile(bool isfiredbyplayer, int xpos, int ypos,  int xspeed, int yspeed, int damage, int radius);

#endif
