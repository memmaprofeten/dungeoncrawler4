#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <stdexcept>
#include "room.hpp"
#include "character.hpp"
#include "convenience.hpp"

#define PI 3.14159265358979323846F
// TODO: Move some of these out to configuration files:
#define characterTextureFile "../resources/img/character_128.png"
#define characterRotationOffset 270

int main()
{
    // Testing starts here

    Room testRoom("../resources/rooms/room.txt");
    testRoom.print();
    /*std::cout << testRoom.getTile(2, 2).toString() << std::endl;
    std::vector<sf::Vector2i> neighbours = testRoom.getNeighbours(0, 0, true, true, true);
    for (unsigned i = 0; i < neighbours.size(); ++i) {
        std::cout << "(" << neighbours[i].x << ", " << neighbours[i].y << ")" << std::endl;
    }*/

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


    sf::Clock frameClock;
    float elapsed;
    bool keyIsPressed_W = false;
    bool keyIsPressed_A = false;
    bool keyIsPressed_S = false;
    bool keyIsPressed_D = false;

    // Mock parameters start here:
    float characterSpeed = 100.0f;
    // Mock parameters end here

    // The main game loop:
	while (window.isOpen())
	{
        elapsed = frameClock.restart().asSeconds();     // The time elapsed since the last frame.
        //sf::sleep(sf::seconds(0.05f));                // Uncomment this to simulate worse fps.
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
        float characterDistance = elapsed * characterSpeed;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            keyIsPressed_D = true;
    		//character.sprite.move(characterDistance, 0);
    	}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            keyIsPressed_A = true;
    		//character.sprite.move(-characterDistance, 0);
    	}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            keyIsPressed_S = true;
    		//character.sprite.move(0, characterDistance);
    	}
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            keyIsPressed_W = true;
    		//character.sprite.move(0, -characterDistance);
    	}
        sf::Vector2f dpos(0, 0);
        if (keyIsPressed_W) dpos.y -= 1;
        if (keyIsPressed_A) dpos.x -= 1;
        if (keyIsPressed_S) dpos.y += 1;
        if (keyIsPressed_D) dpos.x += 1;
        character.sprite.move(dpos.x * characterDistance, dpos.y * characterDistance);  // TODO: Normalize
        keyIsPressed_W = keyIsPressed_A = keyIsPressed_S = keyIsPressed_D = false;

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
