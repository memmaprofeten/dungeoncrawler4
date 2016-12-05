#include "settings.hpp"

namespace s {
	std::string characterTextureFile = "../resources/img/character_32.png";
	std::string fireballTextureFile = "../resources/img/fireball_32.png";
	std::string floor2TextureFile = "../resources/img/floor_32_2.png";
	std::string hpContainerTextureFile = "../resources/img/hp_container1.png";
	std::string projectileTextureFile = "../resources/img/projectile_32.png";
	std::string characterShadowFile = "../resources/img/shadowtest2.png";
	std::string wallTextureFile = "../resources/img/wall_32.png";
	std::vector<std::string> texturePaths = {characterTextureFile,
						fireballTextureFile,
						floor2TextureFile,
						hpContainerTextureFile,
						projectileTextureFile,
						characterShadowFile,
						wallTextureFile};
	std::vector<sf::Texture> textures;
	void loadTextures(){
		for (auto &i : texturePaths){
			sf::Texture tex;
			tex.loadFromFile(i);
			textures.push_back(tex);
		}
	}
	float characterSpeed = 80.0f;
	int characterRotationOffset = 270;
	float blockDim = 10.0f;
	int viewHeight = 150;
	float PI = 3.14159265358979323846F;
}
