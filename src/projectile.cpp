#include <projectile.hpp>

// Basic functions to retrieve values from the projectile and the consturctor.
const bool Projectile::isfiredbyplayer(){
  return firedbyplayer;
}

const int Projectile::returnxpos(){
  return xpos;
}

const int Projectile::returnypos(){
  return ypos;
}

const int Projectile::returndamage(){
  return damage;
}

const int Projectile::returnradius(){
  return radius;
}

void Projectile::Projectile(bool shotbyplayer, int xposin, int yposin, int xspeedin, int yspeedin, int damagein, int radiusin){
  firedbyplayer = shotbyplayer;
  xpos = xposin;
  ypos = yposin;
  xspeed = xspeedin;
  yspeed = yspeedin;
  damage = damgein;
  radius = radiusin;
}

/*
Function that is called to iterate the 
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
