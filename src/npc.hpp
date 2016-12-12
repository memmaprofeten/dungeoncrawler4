#ifndef NPC_HH
#define NPC_HH

#include <string>
#include <SFML/Graphics.hpp>

class Item;
class Character;

enum NpcType {
    NPC,
    SHOPKEEPER
};

class Npc{
public:
    Npc(int, sf::Vector2f);

    void setPosition(sf::Vector2f);

    void draw(sf::RenderWindow&, Character&);

    void setRotation(int);

    bool isInRange() const;

    std::vector<Item*>& getInventory();

    NpcType type;

protected:
    std::vector<Item*> inventory;

private:
    bool inRange;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f pos;
};


class Shopkeeper : public Npc {
public:
    Shopkeeper(int, sf::Vector2f);

private:

};

#endif
