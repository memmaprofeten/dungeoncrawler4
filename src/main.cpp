#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <stdexcept>
#include "settings.hpp"
#include "room.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "convenience.hpp"
#include "monster.hpp"
#define PI 3.14159265358979323846F
// TODO: Move some of these out to configuration files:
//#define characterTextureFile "../resources/img/character_32.png"

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
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(4.0f / 3.0f * s::viewHeight, s::viewHeight));

    Character character("Test man", true, s::characterTextureFile);

	//sf::CircleShape enemy(20.f);
	//enemy.setFillColor(sf::Color::Green);

    sf::Clock frameClock;
    float elapsed;
    float elapsedSinceLastShot = 1000.0f;
    std::vector<Projectile> projectiles;        // TODO: Replace with a more efficient solution
    std::vector<MeleeMonster> meleemonsters; //Also replace maybe

    //CREATE TEST MONSTER. COMMENT OUT LATER
    meleemonsters.push_back(MeleeMonster("test", 1, 1, 1, 5, 20, 1));
    meleemonsters.begin()->setxypos(50,50);
    //std::cout << monsters.begin()->getname() << std::endl;

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
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                {
                    //std::cout << "Resized! " << event.size.width << ", " << event.size.height;
                    float newViewWidth = (float)event.size.width / (float)event.size.height * view.getSize().y;
                    view.setSize(newViewWidth, view.getSize().y);
                    //std::cout << " | " << newViewWidth << ", " << view.getSize().y << std::endl;
                    break;
                }
                default:
                    break;
            }

        }

        window.clear();
        testRoom.draw(window, s::blockDim);
    	//window.draw(enemy);
        for (auto& p : projectiles) {
            p.draw(window, elapsed);
        }
	for (auto& p : meleemonsters) {
	  p.monsterai(character, window, elapsed);
	}

        sf::Vector2f dpos(0, 0);
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dpos.x += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dpos.x -= 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dpos.y += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dpos.y -= 1;
        dpos = elapsed * characterSpeed * cv::normalized(dpos);
        //character.sprite.move(dpos.x, dpos.y);
        character.move(dpos);
        view.move(dpos.x, dpos.y);

    	sf::Vector2f shapepos = character.sprite.getPosition();
    	sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    	//sf::Vector2f enemypos = enemy.getPosition();
    	float dx = shapepos.x - mousepos.x;
    	float dy = shapepos.y - mousepos.y;
    	float rotation = (atan2(dy,dx)) * 180 / PI;
    	character.sprite.setRotation(rotation + s::characterRotationOffset);
        character.draw(window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (elapsedSinceLastShot < 0.0f || elapsedSinceLastShot > projectileCooldown) {
                elapsedSinceLastShot = 0.0f;
                Projectile projectile(false, 5, 2, 250.0f);
                projectile.setPosition(shapepos);
                projectile.setDirection(sf::Vector2f(mousepos) - shapepos);
                if (cv::norm(projectile.getVelocity()) == 0.0f) {      // If mousepos == shapepos, there is no valid direction. In this case, simply fire the projectile in a default direction (the direction of the x axis).
                    projectile.setDirection(sf::Vector2f(1, 0));
                }
                projectiles.push_back(projectile);
            }
        }

        window.setView(view);
        window.display();
    }

    return 0;
}
