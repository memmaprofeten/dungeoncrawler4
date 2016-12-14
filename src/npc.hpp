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
    /**
    * Constructor taking the texture index (int) and position on the map.
    * A NPC has a constant position unless moved using setPosition() or setRotation()
    */
    Npc(int, sf::Vector2f);

    /**
    * Sets the position of the NPC, if it needs to be moved to a different location
    * than specified in the constrictor
    */
    void setPosition(sf::Vector2f);

    /**
    * Draw the NPC on screen
    */
    void draw(sf::RenderWindow&, Character&);

    /**
    * Sets the rotation of the NPC
    */
    void setRotation(int);

    /**
    * Tells if the NPC is in close proximity of the player
    * The proximity is calculated every time draw() is called.
    */
    bool isInRange() const;

    /**
    * Returns a reference to the character's inventory.
    */
    std::vector<Item*>& getInventory();

    /**
     * Remove the item with index i from character's inventory
     */
    void removeFromInventory(int i);

    /**
    * Enumerator for storing the NPC type (e.g. NPC or SHOPKEEPER)
    */
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
