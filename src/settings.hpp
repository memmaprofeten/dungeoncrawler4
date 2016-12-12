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
}

#endif
