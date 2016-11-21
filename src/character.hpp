#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
//#include "weapon.hpp"
#include "item.hpp"

/*Can it be made so that only one instance of character can
be created?*/
class Character {
public:
	/*Constructor taking name, type and level with default value 1
	This can be used to initiate higher level characters if we decide
	to implement a save feature */
	Character(const std::string& n, bool t, const std::string& txtr, int l = 1);


	std::string getName() const { return name; }

	std::string getTexture() const { return texture; }

	// moving function

	//attacking and getting attacked functions

	//item pickup

	sf::Sprite sprite;

private:
	std::string name; //Name of player. User input or based on class?
	bool type;
	std::string texture;
	int level; //Character level of player. Starts at 1
	//std::vector<Weapon> weapons; //List of weapons carried by player.
	std::vector<Item> items; //List of items carried by player.

	//Weapon equippedweapon; //currently equipped weapon.
	int maxhealth; //Player's maximum health.
	int health; //Player's current health.
	float movespeed; //Players movement speed.
	int xp; //Player's current experience amount.
	int xpfornextlevel; //amount required for player to level up.
};

#endif