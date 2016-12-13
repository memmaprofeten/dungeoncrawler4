#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

namespace s {

	extern std::string mapPath;
	extern std::string texturePath;

	extern std::vector<std::string> texturePaths;
	extern std::vector<sf::Texture> textures;
	void loadTextures();

	extern float characterSpeed;
    extern std::string defaultProjectileTextureFile;
	extern int characterRotationOffset;
	extern float blockDim;         // The dimension (length=width) of each block (tile)
	extern int viewHeight;
	extern float relativeInventoryBackgroundWidth;
	extern int itemsPerRow;
	extern float relativeItemMargin;
	extern int standardEntrancePosX;		// The standard X coordinate of a horizontal room entrance
	extern int standardEntrancePosY;		// The standard Y coordinate of a vertical room entrance
	extern int standardEntranceWidth;		// The standard width of a room entrance (in blocks)
	extern int startingRoomIndex;
	extern int monstersPerRoom;

	extern std::string meleattacksoundstring;
	extern std::string bowattacksoundstring;
	extern std::string fireballattacksoundstring;
	extern std::string levelupsoundstring;
	extern std::string deathsoundstring;
	extern std::string musicstring;
	extern std::string hitsoundstring;
	extern std::vector<std::string> soundfilepaths;
	extern std::vector<sf::SoundBuffer> soundbuffers;
	void loadsounds();

	/* Represents a simple translation/rotation animation.
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
		void set(sf::Vector2f p, sf::Vector2f dp, float r, float dr, int textureIndex, sf::Vector2f scale, sf::Vector2f origin, float dur);
		void updateTexture(int textureIndex, sf::Vector2f scale, sf::Vector2f origin);
		void restart();
		void draw(sf::RenderWindow& window, float elapsed);
	};
}

#endif
