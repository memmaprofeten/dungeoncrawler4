#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "weapon.hpp"
class Room;
class Weapon;
class Item;

/*Can it be made so that only one instance of character can
be created?*/
/* ^ Not really necessary in my opinion. Hypotetically, there might be situations where several character instances are needed. - JG */
class Character {
public:
	/*Constructor taking name, type and level with default value 1
	This can be used to initiate higher level characters if we decide
	to implement a save feature */
	Character(const std::string& n, bool t, float s, sf::Vector2f p, int textureIndex, int shadowIndex, int l = 1);

	~Character();

	std::string getName() const;

	sf::Vector2f getPosition() const;

	/* Forces the character's position to the given position, without taking
	 * any constraints into account.
	 */
	void setPosition(sf::Vector2f newPosition);

	void move(sf::Vector2f dir, float elapsed);

	sf::Vector2f getHypotheticalPosition(sf::Vector2f dir, float elapsed) const;

	int getRotation();

	void setRotation(int angle);

	Room* getRoom();

	void setRoom(Room* r);

	void draw(sf::RenderWindow& window);

	//attacking and getting attacked functions

	//item pickup

	std::vector<Item*>& getInventory();

	void addItem(Item* item);

	bool consumeItem(int i);

	int getHealth() const;

	int getMaxHealth() const;

	void reducehealth(int damage);

	void sethealth(int newhealth);

	void teleport (sf::Vector2f dpos);

	void givegold(int gold);

	int getgold() const;

	void givexp(int amount);

  int getlevel();

  void equipweapon(Weapon* newweapon);

  Weapon* getmeleeweapon() const;

  Weapon* getrangedweapon() const;

private:
  std::string name; 				//Name of player. User input or based on class?
  bool type;						// TODO: Is this supposed to define anything?
  int level;						//Character level of player. Starts at 1
  //std::vector<Weapon> weapons;	//List of weapons carried by player.
  std::vector<Item*> inventory;	//List of items carried by the player
  Weapon* equippedrangedweapon; 		//currently equipped weapon.
  Weapon* equippedmeleeweapon;
  int health;						//Player's current health.
  float speed;					//Players movement speed.
  int xp;							//Player's current experience amount.
  int xpfornextlevel;				//amount required for player to level up.

  int gold;						//Amount of gold player has.

  Room* room;
  sf::Vector2f pos;
  int rotation;

  sf::Texture texture;
  sf::Sprite sprite;
  sf::Texture shadowTexture;
  sf::Sprite shadowSprite;

  sf::Sound minorcharactersound;
  sf::Sound majorcharactersound;
};

#endif
