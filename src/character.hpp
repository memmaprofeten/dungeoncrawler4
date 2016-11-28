#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "room.hpp"
//#include "weapon.hpp"
#include "item.hpp"

/*Can it be made so that only one instance of character can
be created?*/
class Character {
public:
	/*Constructor taking name, type and level with default value 1
	This can be used to initiate higher level characters if we decide
	to implement a save feature */
	Character(const std::string& n, bool t, float s, const std::string& txtrPath, int l = 1);

	std::string getName() const;

	sf::Vector2f getPosition() const;

	void move(sf::Vector2f dir, float elapsed, sf::View& view);

	int getRotation();

	void setRotation(int angle);

	Room* getRoom();

	void setRoom(Room* r);

	void draw(sf::RenderWindow& window);

	//attacking and getting attacked functions

	//item pickup

  void reducehealth(int damage);


private:
	std::string name; //Name of player. User input or based on class?
	bool type;
	int level; //Character level of player. Starts at 1
	//std::vector<Weapon> weapons; //List of weapons carried by player.
	std::vector<Item> items; //List of items carried by player.
	//Weapon equippedweapon; //currently equipped weapon.
	int maxhealth; //Player's maximum health.
	int health; //Player's current health.
	float speed; //Players movement speed.
	int xp; //Player's current experience amount.
	int xpfornextlevel; //amount required for player to level up.

	Room* room;
	sf::Vector2f pos;
	int rotation;

	std::string texturePath;
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif
