#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

namespace s {

	extern std::string mapPath;								// The path string of the room directory
	extern std::string texturePath;							// The path string of the texture directory

	extern std::vector<std::string> texturePaths;			// A vector containing paths to all texture files
	extern std::vector<sf::Texture> textures;				// A vector containing the already loaded textures, with indices matching those of texturePaths
	void loadTextures();									// Loads all the textures from file

	extern float floatCorrection;							// The Epsilon value to be used to avoid floating point errors
	extern float characterSpeed;							// The base speed of the character, in points per second
    extern std::string defaultProjectileTextureFile;		// The path of the default projectile texture file
	extern int characterRotationOffset;						// The base offset of the character rotation ("rest rotation")
	extern float blockDim;         							// The dimension (length=width) of each block (tile)
	extern int viewHeight;									// The height of the view, in points
	extern float relativeInventoryBackgroundWidth;			// The ratio between the inventory width and the window width
	extern int itemsPerRow;									// The number of items per inventory row
	extern float deathMessageDuration;						// The duration (in seconds) that the death message should be displayed
	extern float percentageOfGoldLostAtDeath;				// The percentage ([0:1]) of gold that the player loses when they die
	extern float relativeItemMargin;						// The ratio between the distance between items in the inventory and the width of an item in the inventory
	extern int standardEntrancePosX;						// The standard X coordinate of a horizontal room entrance
	extern int standardEntrancePosY;						// The standard Y coordinate of a vertical room entrance
	extern int standardEntranceWidth;						// The standard width of a room entrance (in blocks)
	extern int startingRoomIndex;							// The index of the room in which the player starts
	extern int monstersPerRoom;								// The base amount of monsters per room
	extern float projectileRadius;							// The base hit radius of projectiles

	extern std::string meleattacksoundstring;
	extern std::string bowattacksoundstring;
	extern std::string fireballattacksoundstring;
	extern std::string levelupsoundstring;
	extern std::string deathsoundstring;
	extern std::string musicstring;
	extern std::string hitsoundstring;
	extern std::vector<std::string> soundfilepaths;			// A vector containing paths to all sound files
	extern std::vector<sf::SoundBuffer> soundbuffers;		// A vector containing the already loaded sound buffers, with indices matching those of soundfilepaths
	void loadsounds();										// Loads all the sounds from file

	/**
	*  Represents a simple translation/rotation animation.
	*/
	struct animation {
		sf::Vector2f rPos;		// The rest position of the animation
		sf::Vector2f pos;		// The current position of the animation
		sf::Vector2f dPos;		// The relative translation
		float rRot;				// The rest rotation of the animation
		float rot;				// The current roation of the animation
		float dRot;				// The relative rotation
		float duration;			// The duration of the rotation
		float accumulator;		// An accumulator keeping track of the lifetime of the current animation round
		bool active;			// A flag indicating whether or not this animation is currently in progress.
		sf::Sprite sprite;		// The sprite of the animation

		/**
		 * Initializes the animation objects with the given parameters
		 */
		void set(sf::Vector2f p, sf::Vector2f dp, float r, float dr, int textureIndex, sf::Vector2f scale, sf::Vector2f origin, float dur);

		/**
		 * Changes the texture of the animation object, as well as the related
		 * parameters.
		 */
		void updateTexture(int textureIndex, sf::Vector2f scale, sf::Vector2f origin);

		/**
		 * Restarts the animation.
		 */
		void restart();

		/**
		 * Draws the current state of the animation.
		 */
		void draw(sf::RenderWindow& window, float elapsed);
	};
}

#endif
