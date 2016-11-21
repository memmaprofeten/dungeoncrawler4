#include "projectile.hpp"
// Basic functions to retrieve values from the projectile and the consturctor.
bool Projectile::isfiredbyplayer(){
  return firedbyplayer;
}

int Projectile::getxpos(){
  return xpos;
}

int Projectile::getypos(){
  return ypos;
}

int Projectile::getdamage(){
  return damage;
}

int Projectile::getradius(){
  return radius;
}

Projectile::Projectile(bool shotbyplayer, int xposin, int yposin, int xspeedin, int yspeedin, int damagein, int radiusin){
  firedbyplayer = shotbyplayer;
  xpos = xposin;
  ypos = yposin;
  xspeed = xspeedin;
  yspeed = yspeedin;
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
