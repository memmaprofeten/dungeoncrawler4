#include "settings.hpp"

namespace s {
	std::string characterTextureFile = "../resources/img/character_32.png";
	std::string fireballTextureFile = "../resources/img/fireball_32.png";
	std::string floor2TextureFile = "../resources/img/floor_32_2.png";
	std::string hpContainerTextureFile = "../resources/img/hp_container1.png";
	std::string projectileTextureFile = "../resources/img/projectile_32.png";
	std::string characterShadowFile = "../resources/img/shadowtest2.png";
	std::string wallTextureFile = "../resources/img/wall_32.png";
	std::vector<std::string> texturePaths = {	// NB! Do not switch the order of these. Their indexes are being used.
						characterTextureFile,	// 0
						fireballTextureFile,	// 1
						floor2TextureFile,		// 2
						hpContainerTextureFile,	// 3
						projectileTextureFile,	// 4
						characterShadowFile,	// 5
						wallTextureFile,		// 6
						"../resources/img/doughnut_32.png",	// 7
						"../resources/img/sword1_32.png",		// 8
					};
	std::vector<sf::Texture> textures;
	void loadTextures(){
		for (auto &i : texturePaths){
			sf::Texture tex;
			tex.loadFromFile(i);
			textures.push_back(tex);
		}
	}

  std::string meleattacksoundstring = "../resources/sound/52458__audione__sword-01.wav";
  std::string bowattacksoundstring = "../resources/sound/319550__debsound__cartoon-arrow-08.wav";
  std::string fireballattacksoundstring = "../resources/sound/220191__gameaudio__space-swoosh-brighter.wav";
  std::string levelupsoundstring = "../resources/sound/220184__gameaudio__win-spacey.wav";
  std::string deathsoundstring = "../resources/sound/81822__bennstir__trumpet3.wav";
  std::string musicstring = "../resources/sound/Tri-Tachyon_-_04_-_Hundred_Years_in_Helheim.wav";
  std::string hitsoundstring = "../resources/sound/215162__otisjames__thud.wav";
  //DO NOT REORDER
  std::vector<std::string> soundfilepaths = {meleattacksoundstring,
					     bowattacksoundstring,
					     fireballattacksoundstring,
					     levelupsoundstring,
					     deathsoundstring,
					     hitsoundstring};
  std::vector<sf::SoundBuffer>soundbuffers;
 
  void loadsounds(){
    for (auto &it : soundfilepaths){
      sf::SoundBuffer buf;
      buf.loadFromFile(it);
      soundbuffers.push_back(buf);
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
