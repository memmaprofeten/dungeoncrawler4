#ifndef ITEM_HH
#define ITEM_HH

#include <string>
#include <SFML/Graphics.hpp>

class Character;

/*examples of item types:
-gold
-potions
-other rewards
-food
*/
class Item {
public:
  void draw(sf::RenderWindow& window, Character& player);
  std::string getname() const;
  int gettype() const;
  float getvalue() const;
  void dothing(Character& player); //Does a thing.
  bool isactive() const;
  sf::Vector2f getpos() const;
  Item(std::string namei, int typei, float valuei, std::string texturefilei, sf::Vector2f posi);

  //Functions for the switch cases.
  void dogoldthingy(Character& player);
  void dohealythingy(Character& player);
  void doweaponthingy(Character& player);
       /*
constructor

some kind of draw function*/
private:
/*
type, uses switch in order to have to track multiple types of item in play.
1: Gold, gives player points equal to value variable.
2: Healing item, gives player value percentage of max health, up to maximum.
3: Weapon. Calls function to give player random weapon (or weapon based on value) when player walks over.
*/
  std::string name;//Name, used for message player gets when picking up item.
  int type; //Variable used for switch.
  float value;//Value, used by function called when player walks over item.
  std::string texturefile; //Filepath for texture to be drawn on ground.
  sf::Vector2f pos; //Item XY Positiony
  bool active; //To track if the item is active.
};

void CreateItem(std::vector<Item>& itemstorage, sf::Vector2f position); //Funtion to create item. Called when player kills monster.

#endif
