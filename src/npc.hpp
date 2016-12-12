#ifndef NPC_HH
#define NPC_HH

#include <string>
#include <SFML/Graphics.hpp>

class Item;

class Npc{
public:
  Npc(int, sf::Vector2f);
  
  void setPosition(sf::Vector2f);
  
  void draw(sf::RenderWindow&);
  
  void setRotation(int);

private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f pos;
};

class Shopkeeper : public Npc {
public:
  Shopkeeper(int, sf::Vector2f);
private:
  std::vector<Item> inventory;
};

#endif
