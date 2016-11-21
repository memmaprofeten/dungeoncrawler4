#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <stdexcept>
#include "room.hpp"
#include "character.hpp"

#define PI 3.14159265
// TODO: Move some of these out to configuration files:
#define characterTextureFile "../resources/character_128.png"
#define characterRotationOffset 270

int main()
{
    // Testing starts here
    const std::string testFile = "test";
    Room testRoom(testFile);
    testRoom.print();
    std::cout << testRoom.getTile(2, 2).toString() << std::endl;
    std::vector<sf::Vector2i> neighbours = testRoom.getNeighbours(0, 0, true, true, true);
    for (unsigned i = 0; i < neighbours.size(); ++i) {
        std::cout << "(" << neighbours[i].x << ", " << neighbours[i].y << ")" << std::endl;
    }

    // Testing ends here


   	sf::RenderWindow window(sf::VideoMode(800, 600), "The game!");

    Character character("Test man", true, characterTextureFile);
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile(character.getTexture())) {
        throw std::runtime_error("Could not load character picture.");
    }
    character.sprite.setTexture(characterTexture);
    character.sprite.setRotation(270);
	character.sprite.setOrigin(20,20);

	sf::CircleShape enemy(20.f);
	enemy.setFillColor(sf::Color::Green);
	while (window.isOpen())
	{
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(character.sprite);
    	window.draw(enemy);
            window.display();
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    		character.sprite.move(1,0);
    	}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    		character.sprite.move(-1,0);
    	}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    		character.sprite.move(0,1);
    	}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    		character.sprite.move(0,-1);
    	}
    	sf::Vector2f shapepos = character.sprite.getPosition();
    	sf::Vector2i mousepos = sf::Mouse::getPosition(window);
    	//sf::Vector2f enemypos = enemy.getPosition();
    	float dx = shapepos.x - mousepos.x;
    	float dy = shapepos.y - mousepos.y;
    	float rotation = (atan2(dy,dx)) * 180 / PI;
    	character.sprite.setRotation(rotation+characterRotationOffset);
    }

    return 0;
}
