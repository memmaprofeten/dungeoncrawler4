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
        if (!room->hasPosition(pos)) {
            speed = 0.0f;
            active = false;
        } else if(!room->getTile(pos).isPenetrable()) {
    		speed = 0.0f;
    		active = firedbyplayer;
    	 }
        if (active) {
            pos += speed * elapsed * dir;
        	sprite.setPosition(pos.x, pos.y);
        	sprite.setRotation(rotation+90);
        	window.draw(sprite);
        }
    }
}

Projectile::Projectile(Room* currentRoom, bool shotbyplayer, int damagein, int radiusin, float speedin, int txtrIndex) : room(currentRoom) {
    reset(shotbyplayer, damagein, radiusin, speedin, txtrIndex);
}
