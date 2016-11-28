#include "projectile.hpp"
#include "convenience.hpp"
#include "tile.hpp"
// Basic functions to retrieve values from the projectile and the consturctor.
bool Projectile::isfiredbyplayer(){
  return firedbyplayer;
}

sf::Vector2f Projectile::getPosition() {
  return pos;
}

void Projectile::setPosition(sf::Vector2f position) {
  pos = position;
}

sf::Vector2f Projectile::getVelocity() {
  return dir * speed;
}

void Projectile::setDirection(sf::Vector2f direction) {
    dir = cv::normalized(direction);
}

void Projectile::setSpeed(float newSpeed) {
  speed = newSpeed;
}

int Projectile::getdamage(){
  return damage;
}

int Projectile::getradius(){
  return radius;
}

void Projectile::draw(sf::RenderWindow& window, float elapsed, Room& currentRoom) {
    }// TODO: Check if projectile has hit a target or a wall
    // TODO: Check if projectile has reached out of bounds (and destroy, or hide for reuse)
   	if(!currentRoom.getTile((int)this->getPosition().x/10,(int)this->getPosition().y/10).isPenetrable()){
		this->setSpeed(0.0f);
		return;
	    	pos += speed * elapsed * dir;
	    	sf::CircleShape tile(2.0f);
	    	tile.setOrigin(1.0f, 1.0f);
	    	tile.setPosition(pos.x, pos.y);
		tile.setFillColor(sf::Color::Red);
	    	window.draw(tile);
	}
}

Projectile::Projectile(bool shotbyplayer, int damagein, int radiusin, float speedin){
  firedbyplayer = shotbyplayer;
  pos = sf::Vector2f(0, 0);
  dir = sf::Vector2f(0, 0);
  speed = speedin;
  damage = damagein;
  radius = radiusin;
}

/*
Function that is called to iterate the projectile each tick/loop.
Changes xy positions based on the appropriate speeds.
Then checks if a player / enemy / wall is within hit radius.
If one is, it deals damage (to a player/enemy) and then deletes the projectile.
In case of colliding with a wall, the projectile is just removed.
 */
/*
Projectile::projectiletick(){

}
*/
/*
Function to create a new projectile (fired by player or enemy)
Calls constructor, then saves projectile in a list or somesuch.
That somesuch can be iterated through, calling projectiletick for each projectile for each loop/tick.

*/

/*
void createprojectile(bool isfiredbyplayer, int xpos, int ypos,  int xspeed, int yspeed, int damage, int radius){

}
*/
