#include "settings.hpp"

namespace s {
	std::string characterTextureFile = "../resources/img/character_32.png";
	std::string fireballTextureFile = "../resources/img/fireball_32.png";
	std::string floor2TextureFile = "../resources/img/floor_32_2.png";
	std::string hpContainerTextureFile = "../resources/img/hp_container1.png";
	std::string projectileTextureFile = "../resources/img/projectile_32.png";
	std::string characterShadowFile = "../resources/img/shadowtest2.png";
	std::string wallTextureFile = "../resources/img/wall_32.png";
	std::string doughnutTextureFile = "../resources/img/doughnut_32.png";
	std::string shadowtest1TextureFile = "../resources/img/shadowtest1.png"; 
	std::string shadowtest2TextureFile = "../resources/img/shadowtest2.png"; 
	std::string sword1TextureFile = "../resources/img/sword1_32.png"; 
	std::string monstertest1TextureFile = "../resources/img/monstertest1_32.png"; 
	std::vector<std::string> texturePaths = {characterTextureFile,		// NB! Do not switch the order of these. Their indexes are being used.
						fireballTextureFile,
						floor2TextureFile,
						hpContainerTextureFile,
						projectileTextureFile,
						characterShadowFile,
						wallTextureFile,
						doughnutTextureFile,
						shadowtest1TextureFile,
						shadowtest2TextureFile,
						sword1TextureFile,
						monstertest1TextureFile};
	std::vector<sf::Texture> textures;
	void loadTextures(){
		for (auto &i : texturePaths){
			sf::Texture tex;
			tex.loadFromFile(i);
			textures.push_back(tex);
		}
	}

	std::string mapPath = "../resources/rooms/";

	float characterSpeed = 80.0f;
	int characterRotationOffset = 270;
	float blockDim = 10.0f;
	int viewHeight = 150;
	float relativeInventoryBackgroundWidth = 0.8f;
	int itemsPerRow = 8;
	float relativeItemMargin = 0.01f;
	int standardEntrancePosX = 17;
	int standardEntrancePosY = 17;
	int standardEntranceWidth = 3;
	int startingRoomIndex = 4;
	int monstersPerRoom = 20;
}
