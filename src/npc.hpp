#ifndef NPC_HH
#define NPC_HH

#include <string>
#include <SFML/Graphics.hpp>

class Item;

class Npc{
public:
  Npc();

private:
  
};

class Shopkeeper : public Npc {
public:
  Shopkeeper();
private:
  std::vector<Item> inventory;
};

#endif
