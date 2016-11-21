#include <SFML/Graphics.hpp>
#include <cmath>
#include "room.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

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
    	//sf::CircleShape shape(20,3);
        sf::Texture texture;
        if (!texture.loadFromFile("../resources/character_128.png")) {
            throw std::runtime_error("Could not load character picture.");
        }
        sf::Sprite shape;
        shape.setTexture(texture);
        shape.setRotation(270);
	shape.setOrigin(20,20);
    	//shape.setFillColor(sf::Color::Red);
	const float PI = 3.14159265;

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
        window.draw(shape);
	window.draw(enemy);
        window.display();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		shape.move(1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		shape.move(-1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		shape.move(0,1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		shape.move(0,-1);
	}
	sf::Vector2f shapepos = shape.getPosition();
	sf::Vector2i mousepos = sf::Mouse::getPosition(window);
	//sf::Vector2f enemypos = enemy.getPosition();
	float dx = shapepos.x - mousepos.x;
	float dy = shapepos.y - mousepos.y;
	float rotation = (atan2(dy,dx)) * 180 / PI;
	shape.setRotation(rotation+characterRotationOffset);
    }

    return 0;
}
