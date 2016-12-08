#include "projectile.hpp"
#include "convenience.hpp"
#include "tile.hpp"
#include "settings.hpp"
#include "room.hpp"
#include <cmath>
#include <iostream>

bool Projectile::isfiredbyplayer() { return firedbyplayer; }

bool Projectile::isActive() { return active; }

void Projectile::reset(bool shotbyplayer, int damagein, int radiusin, float speedin, int txtrIndex) {
    firedbyplayer = shotbyplayer;
    active = true;
    pos = sf::Vector2f(0, 0);
    dir = sf::Vector2f(0, 0);
    speed = speedin;
    damage = damagein;
    radius = radiusin;
    rotation = 0;
    textureIndex = txtrIndex;
    sprite.setTexture(s::textures[textureIndex]);
    sprite.setScale(sf::Vector2f(s::blockDim / 32.0f, s::blockDim / 32.0f));
    sprite.setOrigin(16.0f,16.0f);
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
    rotation = (atan2(dir.y,dir.x)) * 180 / cv::PI;
}

float Projectile::getSpeed() const { return speed; }

void Projectile::setSpeed(float newSpeed) {
  speed = newSpeed;
}

int Projectile::getdamage() const {
  return damage;
}

int Projectile::getradius() const {
  return radius;
}

void Projectile::deactivate() {
  active = false;
}

void Projectile::draw(sf::RenderWindow& window, float elapsed) {
    if (active) {
        /*
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
        */

        if (!room->hasPosition(pos)) {
            active = false;
        } else {
            pos += speed * elapsed * dir;
        	//sprite.setTexture(texture);        // TODO: Figure this out (why doesn't it work to do this just once?)
        	sprite.setPosition(pos.x, pos.y);
        	sprite.setRotation(rotation+90);
        	window.draw(sprite);
            // TODO: If the projectile is to be removed (e.g. has hit a soft target), call 'active = false;'.
        }

        /*below not used, ugly shit
        	    	sf::Texture arrow;
        	    	tile.setOrigin(1.0f, 1.0f);
        	    	tile.setPosition(pos.x, pos.y);
        		tile.setFillColor(sf::Color::Red);
        	    	window.draw(tile);
        */
    }
}

Projectile::Projectile(Room* currentRoom, bool shotbyplayer, int damagein, int radiusin, float speedin, int txtrIndex) : room(currentRoom) {
    reset(shotbyplayer, damagein, radiusin, speedin, txtrIndex);
}
