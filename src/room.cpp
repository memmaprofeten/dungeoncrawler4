#include "room.hpp"
#include "settings.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include "settings.hpp"
#include "convenience.hpp"
#include "character.hpp"

Room::Room(std::string const file, Character* character) : character(character) {
	int x = 0;
	int y = 0;
	sf::Sprite dummy;
	//sf::Sprite* dymmu = dummy; //TODO: Fix this
	std::string line;
	std::ifstream mapFile (s::mapPath + file);
	if (mapFile.is_open()){
		getline(mapFile, line);
		std::istringstream iss(line);
		iss >> width >> height;
		room = std::vector<std::vector<Tile>>(width, std::vector<Tile>(height, Tile(0,sf::Vector2f(0,0), sf::Vector2i(0,0), &dummy)));
		while(getline(mapFile, line)){
			x=0;
			for(unsigned int i = 0; i < line.size(); i++){
				sf::Sprite* sprite = getSprite();
				getTile(x,y) = Tile((int)line[i]-48, sf::Vector2f(s::blockDim*x,s::blockDim*y), sf::Vector2i(x,y), sprite);
				x++;
			}
			y++;
		}
		mapFile.close();
	}
	 else {
		throw std::runtime_error(std::string("Could not find or open file '") + file + "'.");
	}
}

Room::~Room() {
	for (unsigned i=0; i<monsters.size(); ++i) {
		delete monsters[i];
		monsters.clear();
	}
}

int Room::getWidth() const {
	return width;
}

int Room::getHeight() const {
	return height;
}

bool Room::hasCoordinate(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return false;
    }
    return true;
}

bool Room::hasPosition(sf::Vector2f pos) {
	if (pos.x < 0.0f || pos.y < 0.0f || pos.x > width * s::blockDim || pos.y > height * s::blockDim) {
		return false;
	}
	return true;
}

sf::Vector2i Room::getOffsetDirection(sf::Vector2f pos) {
	sf::Vector2i res(0, 0);
	if (pos.x < 0.0f)						res = sf::Vector2i(res.x - 1, res.y);
	else if (pos.x > width * s::blockDim)	res = sf::Vector2i(res.x + 1, res.y);
	if (pos.y < 0.0f)						res = sf::Vector2i(res.x, res.y - 1);
	else if (pos.y > height * s::blockDim)	res = sf::Vector2i(res.x, res.y + 1);
	return res;
}

Tile& Room::getTile(int x, int y) {
    if (hasCoordinate(x, y)) {
        return room[x][y];
    }
    throw std::runtime_error(std::string("The coordinates (") + std::to_string(x) + ", " + std::to_string(y) + ") are out of bounds!");
}

Tile& Room::getTile(sf::Vector2f pos) {
	return getTile((int)pos.x / s::blockDim, (int)pos.y / s::blockDim);
}

std::vector<sf::Vector2i> Room::getNeighbours(int x, int y, bool includingSelf, bool includingDiagonals, bool includingOutsiders) {
    std::vector<sf::Vector2i> res;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if ((includingSelf || !(dx == 0 && dy == 0)) &&          // Check if this neighbour is the original coordinate
                (includingDiagonals || dx == 0 || dy == 0) &&       // Check if this neighbour is a diagonal neighbour
                (includingOutsiders || (dx >= 0 && dy >= 0 && dx < width && dy < height))   // Check if this neighbour is out of bounds
            ) {
                res.push_back(sf::Vector2i(x + dx, y + dy));
            }
        }
    }
    return res;
}

void Room::draw(sf::RenderWindow& window) {
/*	for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
			getTile(i, j).draw(window, blockDim);
        }
    }
*/
	for (auto sprite : sprites){
		window.draw(sprite);
	}
}

void Room::drawProjectiles(sf::RenderWindow& window, float elapsed) {
	for (int i=0; i<int(projectiles.size()); ++i) {
		Projectile& projectile = projectiles[i];
		if (projectile.isActive()) {					// Loop only through active projectiles
			projectile.draw(window, elapsed, this);			// Call their draw method which updates their position and draws them
			if(!projectile.isfiredbyplayer() && cv::distance(character->getPosition(), projectile.getPosition()) < float(projectile.getradius())) {	// Hit detection
				character->reducehealth(projectile.getdamage()); // character takes damage
				projectile.deactivate();
			}
			// TODO: Monster hit detection
			for (auto monster : monsters){
				if(monster->isactive()){
					if(projectile.isfiredbyplayer() && cv::distance(monster->getPosition(), projectile.getPosition()) < float(projectile.getradius())) {
						monster->reducehealth(projectile.getdamage());
						projectile.deactivate();
					}
				}
			}
			if (!projectile.isActive()) {
				freeProjectiles.push_back(i);				// If a projectile becomes inactive, mark it as free for overriding
			}
		}
	}
}

void Room::print() {
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            std::cout << getTile(i, j).toString() << " ";
        }
        std::cout << std::endl;
    }
}

sf::Sprite* Room::getSprite() {
	for (unsigned int i; i<sprites.size();i++){
		if(!spritesInUse[i]) {
			spritesInUse[i] = true;
			return &sprites[i];
		}
	}
	sf::Sprite sprite;
	sprites.push_back(sprite);
	spritesInUse.push_back(true);
	return &sprites.back();
}

/*std::vector<Projectile> Room::getProjectiles() {
	return projectiles;
}*/

Projectile& Room::createProjectile(bool shotbyplayer, int damagein, int radiusin, float speedin, int txtrIndex) {
	if (freeProjectiles.size() > 0) {
		int i = freeProjectiles.back();
		freeProjectiles.pop_back();
		projectiles[i].reset(shotbyplayer, damagein, radiusin, speedin, txtrIndex);
		return projectiles[i];
	} else {
		projectiles.push_back(Projectile(this, shotbyplayer, damagein, radiusin, speedin, txtrIndex));
		return projectiles.back();
	}
}

std::vector<Monster*>& Room::getmonsters(){
  return monsters;
}

std::vector<Item>& Room::getitems(){
  return itemstorage;
}

Character* Room::getcharacter(){
  return character;
}
