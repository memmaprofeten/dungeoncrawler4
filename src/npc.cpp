#include "npc.hpp"
#include "item.hpp"

Npc::Npc() {}

Shopkeeper::Shopkeeper() : Npc() {
  inventory.push_back(Item("Doughnut", 4, 3, "../resources/img/doughnut_32.png", sf::Vector2f(0, 0)));
  inventory.push_back(Item("Ice cream", 4, 2, "../resources/img/sword1_32.png", sf::Vector2f(0, 0)));
  inventory.push_back(Item("Cake", 4, 5, "../resources/img/sword1_32.png", sf::Vector2f(0, 0)));
  
}
