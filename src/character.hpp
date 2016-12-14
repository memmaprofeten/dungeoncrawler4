#ifndef CHARACTER_HH
#define CHARACTER_HH

#include "settings.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Room;
class Weapon;
class Item;

/**
 * Represents the character, controlled by the player.
 */
class Character {
public:

	/**
	 * Constructor taking name, type and level with default value 1.
	 * This can be used to initiate higher level characters for the purposes of
	 * e.g. a save feature.
	 */
	Character(const std::string& n, bool t, float s, sf::Vector2f p, int textureIndex, int shadowIndex, int l = 1);

	/**
	 * The character destructor.
	 */
	~Character();

	/**
	 * Returns the name of the character.
	 */
	std::string getName() const;

	/**
	 * Returns the position (in terms of point coordinates in the current room)
	 * of the character.
	 */
	sf::Vector2f getPosition() const;

	/**
	 * Sets the character's position to the given position, without taking any
	 * constraints into account.
	 * NB! If you wish to move tha character only if possible, use the
	 * 'teleport' function instead.
	 */
	void setPosition(sf::Vector2f newPosition);

	/**
	 * Moves the character in the given direction, according to the given
	 * elapsed time since the last frame.
	 */
	void move(sf::Vector2f dir, float elapsed);

	/**
	 * Returns the position that the character would be in if it moved in
	 * direction 'dir' during time 'elapsed', assuming no obstacles.
	 */
	sf::Vector2f getHypotheticalPosition(sf::Vector2f dir, float elapsed) const;

	/**
	 * Returns the character's current rotation, in degrees.
	 */
	int getRotation();

	/**
	 * Sets the character's rotation to 'angle' degrees.
	 */
	void setRotation(int angle);

	/**
	 * Returns a pointer to the room currently inhabited by the character.
	 */
	Room* getRoom();

	/**
	 * Sets the character's room to the given room.
	 */
	void setRoom(Room* r);

	/**
	 * Draws the character.
	 */
	void draw(sf::RenderWindow& window, float elapsed);

	/**
	 * Registers that the character is now initiating a melee attack, for
	 * visualisation purposes.
	 */
	void initiateMeleeAttack();

	/**
	 * Retunrs a reference to the character's inventory.
	 */
	std::vector<Item*>& getInventory();

	/**
	 * Adds an item to the character's inventory.
	 */
	void addItem(Item* item);

	/**
	 * Attempts to consume an item. If it could be consumed, returns true,
	 * otherwise, returns false.
	 */
	bool consumeItem(int i);

	/**
	 * Returns the character's current health.
	 */
	int getHealth() const;

	/**
	 * Returns the character's current max health.
	 */
	int getMaxHealth() const;

	/**
	 * Reduces the character's health by 'damage', and checks if the character
	 * has died.
	 */
	void reducehealth(int damage);

	/**
	 * Sets the character's health to the given new health.
	 */
	void sethealth(int newhealth);

	/**
	 * Teleports the character by the given direction (componentwise), if
	 * possible.
	 */
	void teleport (sf::Vector2f dpos);

	/**
	 * Adds the given amount of gold to the character.
	 */
	void givegold(int gold);

	/**
	 * Returns the character's current amount of gold.
	 */
	int getgold() const;

	/**
	 * Adds the given amount of xp to the character and checks for a levelup.
	 */
	void givexp(int amount);

	/**
	 * Returns the character's current level.
	 */
	int getlevel() const;

	/**
	 * Sets the player's level to the given value and zeros the offset xp.
	 */
	 void setLevel(int newLevel);

	/**
 	 * Equips the given weapon.
	 */
	void equipweapon(Weapon* newweapon);

	/**
	 * Returns a pointer to the character's current melee weapon.
	 */
	Weapon* getmeleeweapon() const;

	/**
	 * Returns a pointer to the character's current ranged weapon.
	 */
	Weapon* getrangedweapon() const;

private:
	std::string name; 					// Name of player. User input or based on class?
	bool type;							// TODO: Is this supposed to define anything?
	int level;							// Character level of player. Starts at 1
	std::vector<Item*> inventory;		// List of items carried by the player
	Weapon* equippedmeleeweapon;		// The currently equipped melee weapon
	Weapon* equippedrangedweapon; 		// The currently equipped rangedweapon
	int health;							// Player's current health
	float speed;						// Players movement speed
	int xp;								// Player's current experience amount
	int xpfornextlevel;					// amount required for player to level up

	int gold;							// The amount of gold the character has

	Room* room;							// A pointer to the room currently inhabited by the character
	sf::Vector2f pos;					// The character's current position in the room
	int rotation;						// The character's current rotation, in degrees

	sf::Texture texture;				// The character's texture
	sf::Sprite sprite;					// The character's sprite
	sf::Texture shadowTexture;			// The character's shadow texture
	sf::Sprite shadowSprite;			// The character's shadow sprite
	s::animation weaponAnim;			// The character's weapon animation

	sf::Sound minorcharactersound;		// The character's sound object for minor sounds
	sf::Sound majorcharactersound;		// The character's sound object for major sounds
};

#endif
