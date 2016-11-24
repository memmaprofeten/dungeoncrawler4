#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <stdexcept>
#include "room.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "convenience.hpp"

#define PI 3.14159265358979323846F
// TODO: Move some of these out to configuration files:
#define characterTextureFile "../resources/img/character_128.png"
#define characterRotationOffset 270

int main()
{
    // Testing starts here

    Room testRoom("../resources/rooms/room.txt");
    //testRoom.print();
    /*std::cout << testRoom.getTile(2, 2).toString() << std::endl;
    std::vector<sf::Vector2i> neighbours = testRoom.getNeighbours(0, 0, true, true, true);
    for (unsigned i = 0; i < neighbours.size(); ++i) {
        std::cout << "(" << neighbours[i].x << ", " << neighbours[i].y << ")" << std::endl;
    }*/

    // Testing ends here


   	sf::RenderWindow window(sf::VideoMode(800, 600), "The game!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(200, 150));

    Character character("Test man", true, characterTextureFile);
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile(character.getTexture())) {
        throw std::runtime_error("Could not load character picture.");
    }
    character.sprite.setTexture(characterTexture);
    character.sprite.setRotation(270);
	character.sprite.setOrigin(16,16);

	sf::CircleShape enemy(20.f);
	enemy.setFillColor(sf::Color::Green);

    //Projectile testProjectile(false, 5, 2, 250.0f);
    //testProjectile.setPosition(sf::Vector2f(100, 100));
    //testProjectile.setDirection(cv::normalized(sf::Vector2f(1, 1)));

    sf::Clock frameClock;
    float elapsed;
    float elapsedSinceLastShot = 1000.0f;
    std::vector<Projectile> projectiles;        // TODO: Replace with a more efficient solution

    // Mock parameters start here:
    float characterSpeed = 100.0f;
    float projectileCooldown = 0.3f;        // In seconds
    // Mock parameters end here

    // The main game loop:
	while (window.isOpen())
	{
        elapsed = frameClock.restart().asSeconds();     // The time elapsed since the last frame
        elapsedSinceLastShot += elapsed;                // The time elapsed since player's last shot
        //sf::sleep(sf::seconds(0.05f));                // Uncomment this to simulate worse fps

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        testRoom.draw(window, 10.0f);
        window.draw(character.sprite);
    	window.draw(enemy);
        for (auto& p : projectiles) {
            p.draw(window, elapsed);
        }
        window.display();

        sf::Vector2f dpos(0, 0);
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dpos.x += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dpos.x -= 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dpos.y += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dpos.y -= 1;
        dpos = elapsed * characterSpeed * cv::normalized(dpos);
        character.sprite.move(dpos.x, dpos.y);
        view.move(dpos.x, dpos.y);

    	sf::Vector2f shapepos = character.sprite.getPosition();
    	sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    	//sf::Vector2f enemypos = enemy.getPosition();
    	float dx = shapepos.x - mousepos.x;
    	float dy = shapepos.y - mousepos.y;
    	float rotation = (atan2(dy,dx)) * 180 / PI;
    	character.sprite.setRotation(rotation+characterRotationOffset);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (elapsedSinceLastShot < 0.0f || elapsedSinceLastShot > projectileCooldown) {
                elapsedSinceLastShot = 0.0f;
                Projectile projectile(false, 5, 2, 250.0f);
                projectile.setPosition(shapepos);
                projectile.setDirection(sf::Vector2f(mousepos) - shapepos);
                projectiles.push_back(projectile);
            }
        }

        window.setView(view);
    }

    return 0;
}
