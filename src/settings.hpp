#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace s {

	extern std::string characterTextureFile;
	extern std::string fireballTextureFile;
	extern std::string floor2TextureFile;
	extern std::string hpContainerTextureFile;
	extern std::string projectileTextureFile;
	extern std::string characterShadowFile;
	extern std::string wallTextureFile;
	extern std::string doughnutTextureFile;
	extern std::string shadowtest1TextureFile;
	extern std::string shadowtest2TextureFile;
	extern std::string sword1TextureFile;
	extern std::string monstertest1TextureFile;
	extern std::vector<std::string> texturePaths;
	extern std::vector<sf::Texture> textures;
	void loadTextures();

	extern std::string mapPath;

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
}

#endif
