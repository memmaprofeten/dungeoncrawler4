#include "settings.hpp"

#define FLOAT_CORRECTION 0.001F     // The Epsilon value to be used to avoid floating point errors

namespace s {

	std::string mapPath = "../resources/rooms/";
	std::string texturePath = "../resources/img/";

	std::vector<std::string> texturePaths = {	// NB! Do not switch the order of these. Their indexes are being used.
			"character_32.png",				// 0
			"fireball_32.png",				// 1
			"floor_32_2.png",				// 2
			"hp_container1.png",			// 3
			"projectile_32.png",			// 4
			"shadowtest2.png",				// 5
			"wall_32.png",					// 6
			"doughnut_32.png",				// 7
			"sword1_32.png",				// 8
			"shadowtest1.png",				// 9
			"shadowtest2.png",				// 10
			"monstertest1_32.png",			// 11
			"bread1_32.png",				// 12
			"character2_32.png",			// 13
			"flail1_32.png",				// 14
			"gold1_32.png",					// 15
			"potion_blue1_32.png",			// 16
			"potion_red1_32.png",			// 17
			"reissumies_32.png",			// 18
			"spear1_32.png",				// 19
			"cursor1_33.png",				// 20
		};

	std::vector<sf::Texture> textures;
	void loadTextures(){
		for (auto &path : texturePaths){
			sf::Texture tex;
			tex.loadFromFile(texturePath + path);
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

	std::vector<std::string> soundfilepaths = {		// NB! Do not switch the order of these. Their indexes are being used.
				meleattacksoundstring,
				bowattacksoundstring,
				fireballattacksoundstring,
				levelupsoundstring,
				deathsoundstring,
				hitsoundstring,
				"../resources/sound/Ta_Da-SoundBible.wav",
				"../resources/sound/Monster_Gigante-Doberman-1334685792_1.wav",
				"../resources/sound/Monster_Gigante-Doberman-1334685792_2.wav",
			};
	std::vector<sf::SoundBuffer>soundbuffers;

	void loadsounds(){
		for (auto &it : soundfilepaths){
			sf::SoundBuffer buf;
			buf.loadFromFile(it);
			soundbuffers.push_back(buf);
		}
	}

	float floatCorrection = FLOAT_CORRECTION;
	float characterSpeed = 80.0f;
	int characterRotationOffset = 270;
	float blockDim = 10.0f;
	int viewHeight = 150;
	float relativeInventoryBackgroundWidth = 0.8f;
	int itemsPerRow = 12;
	float deathMessageDuration = 3.0f;
	float percentageOfGoldLostAtDeath = 0.8f;
	float relativeItemMargin = 0.01f;
	int standardEntrancePosX = 17;
	int standardEntrancePosY = 17;
	int standardEntranceWidth = 3;
	int startingRoomIndex = 4;
	int monstersPerRoom = 6;
	float projectileRadius = 0.6f * blockDim;

	void animation::set(sf::Vector2f p, sf::Vector2f dp, float r, float dr, int textureIndex, sf::Vector2f scale, sf::Vector2f origin, float dur) {
		rPos = pos = p; dPos = dp; rRot = rot = r; dRot = dr;
		duration = dur;
		updateTexture(textureIndex, scale, origin);
		accumulator = 0;
		active = false;
	}
	void animation::updateTexture(int textureIndex, sf::Vector2f scale, sf::Vector2f origin) {
		sprite.setTexture(s::textures[textureIndex]);
		sprite.setOrigin(origin);
		sprite.setScale(scale);
	}
	void animation::restart() {
		pos = rPos; rot = rRot;
		accumulator = 0;
		active = true;
	}
	void animation::draw(sf::RenderWindow& window, float elapsed) {
		if (active) {
			accumulator += elapsed;
			if (accumulator > duration) {
				restart();
				active = false;
			} else {
				pos += dPos * elapsed;
				rot += dRot * elapsed;
				sprite.setPosition(pos);
				sprite.setRotation(rot);
				window.draw(sprite);
			}
		}
	}

}
