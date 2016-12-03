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
	extern std::vector<std::string> texturePaths;
	extern std::vector<sf::Texture> textures;
	void loadTextures();
    	extern int characterRotationOffset;
    	extern float blockDim;         // The dimension (length=width) of each block (tile)
    	extern int viewHeight;
    	extern float PI;
}

#endif
