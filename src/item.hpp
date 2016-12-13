#ifndef ITEM_HH
#define ITEM_HH

#include <string>
#include <SFML/Graphics.hpp>

class Weapon;
class Character;

/**
 * Represents an item, such as a potion, a weapon or a piece of food.
 *
 * Items can be located in different places, such as dropped on the ground or
 * in someone's inventory.
 * The Item types are defined by an extendable integer variable, as follows:
 *          - 1: Gold, gives player points equal to value variable.
 *          - 2: Healing item, gives player value percentage of max health, up to maximum.
 *          - 3: Weapon. Calls function to give player random weapon (or weapon based on value) when player walks over.
 */
class Item {

public:

    /**
     * Draws the item
     */
    void draw(sf::RenderWindow& window, Character& player);

    /**
     * Returns the name of the item
     */
    std::string getname() const;

    /**
     * Returns the type of the item, represented by an integer as follows:
     *          1 - gold
     *          2 - consumable
     *          3 - weapon
     *          other - trinkets or otherwise functionless items
     */
    int gettype() const;

    /**
     * Returns the value of the item. The value is a general variable that can
     * be used by different item types as they need.
     */
    float getvalue() const;

    /**
     * Performs the action of this item, if it has one.
     */
    void dothing(Character& player);

    /**
     * Returns the position of this item. If the item is not currently on the
     * ground, the position has no relevance.
     */
    sf::Vector2f getpos() const;

    /**
     * Returns a reference to the item's drop sprite, i.e., the sprite that
     * should be drawn if the item is on the ground.
     */
    sf::Sprite& getDropSprite();

    /**
     * Returns a reference to the item's inventory sprite, i.e., the sprite that
     * should be drawn for an inventory.
     */
    sf::Sprite& getInventorySprite();

    /**
     * Standard Item constructor.
     * Constructs an item of given type based on the specific parameters.
     */
    Item(std::string namei, int typei, float valuei, int textureIndexi, sf::Vector2f posi, int leveli);

    /**
     * Weapon Item constructor.
     * Constructs a weapon item based on the specific parameters.
     */
    Item(std::string namei, Weapon* weaponi, int leveli, int textureIndexi, sf::Vector2f posi);

    /**
     * Random Item constructor.
     * Constructs a randomized item.
     */
    Item(sf::Vector2f positioni, int leveli);

    /**
     * Item destructor
     */
    ~Item();

    /**
     * Applies the effects of gold
     */
    void applyGoldEffects(Character& player);

    /**
     * Applies the effects of a consumable
     */
    void applyConsumableEffects(Character& player);

    /**
     * Applies the effects of a weapon
     */
    void applyWeaponEffects(Character& player);

private:
    std::string name;               // Name, used for message player gets when picking up item
    int textureIndex;               // The texture index of the item
    sf::Sprite inventorySprite;     // The sprite representing the inventory graphic of this item
    sf::Sprite dropSprite;          // The sprite representing the dropped graphic of this item
    sf::Vector2f pos;               // Item XY Position
    int type;                       // Type of item. Elaborated on above
    float value;                    // Used for consumeables for amount of whatever it does
    int level;                      // Used to save what level the item is. Used in generation functions
    Weapon* representedweapon;      // What weapon the item represents
    bool sellable;                  // Whether or not the item is sellable
    int baseprice;                  // Base price for sold item.
};

#endif
