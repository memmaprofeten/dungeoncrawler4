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
  int getxpos();
  int getypos();
  int getdamage();
  int getradius();
  void projectiletick();
  Projectile(bool shotbyplayer, int xposin, int yposin, int xspeedin, int yspeedin, int damagein, int radiusin);
  
private:
  bool firedbyplayer; //Player projectiles damage enemies and vice versa.
  int xpos; //position on x axis
  int ypos; // position on y axis
  int xspeed; //How much the projectile moves per tick on the x axis.
  int yspeed; //How much the projectile moves per tick on the y axis.
  int damage; //Damage dealt by projectile.
  int radius; //Radius of projectile for drawing / hit detection.
};

//void createprojectile(bool isfiredbyplayer, int xpos, int ypos,  int xspeed, int yspeed, int damage, int radius);
