#include "projectile.hpp"
#include "convenience.hpp"
#include "tile.hpp"
#include "settings.hpp"
#include <cmath>
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
    rotation = (atan2(dir.y,dir.x)) * 180 / s::PI;
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
    // TODO: Check if projectile has hit a target or a wall
    // TODO: Check if projectile has reached out of bounds (and destroy, or hide for reuse)
	    	pos += speed * elapsed * dir;
	if(!currentRoom.hasCoordinate((int)pos.x/s::blockDim,(int)pos.y/s::blockDim)){
		this->setSpeed(0.0f);
		return;
	}
   	else if(!currentRoom.getTile((int)pos.x/s::blockDim,(int)pos.y/s::blockDim).isPenetrable()){
		this->setSpeed(0.0f);
		if(!firedbyplayer){	
			return;
		}
	 }	
		sprite.setTexture(texture);
		sprite.setPosition(pos.x, pos.y);
		sprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
		sprite.setOrigin(16.0f,16.0f);
		sprite.setRotation(rotation+90);
		window.draw(sprite);
/*
	    	sf::Texture arrow;
	    	tile.setOrigin(1.0f, 1.0f);
	    	tile.setPosition(pos.x, pos.y);
		tile.setFillColor(sf::Color::Red);
	    	window.draw(tile);
*/
}

Projectile::Projectile(bool shotbyplayer, int damagein, int radiusin, float speedin, std::string textureFile){
  firedbyplayer = shotbyplayer;
  pos = sf::Vector2f(0, 0);
  dir = sf::Vector2f(0, 0);
  speed = speedin;
  damage = damagein;
  radius = radiusin;
  if(!texture.loadFromFile(textureFile)){
	throw std::runtime_error("Could not find projectile texture");
}
 
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
