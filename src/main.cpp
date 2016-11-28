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

int main()
{
    // Testing starts here

    Room testRoom("../resources/rooms/room2.txt");
    //testRoom.print();
    /*std::cout << testRoom.getTile(2, 2).toString() << std::endl;
    std::vector<sf::Vector2i> neighbours = testRoom.getNeighbours(0, 0, true, true, true);
    for (unsigned i = 0; i < neighbours.size(); ++i) {
        std::cout << "(" << neighbours[i].x << ", " << neighbours[i].y << ")" << std::endl;
    }*/

    // Testing ends here


   	sf::RenderWindow window(sf::VideoMode(800, 600), "The game!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(4.0f / 3.0f * s::viewHeight, s::viewHeight));

    Character character("Test man", true, 100.0f, sf::Vector2f(30.0f, 30.0f), s::characterTextureFile);
    character.setRoom(&testRoom);
    view.move(character.getPosition().x, character.getPosition().y);

    sf::Clock frameClock;
    float elapsed;
    float elapsedSinceLastShot = 1000.0f;
    std::vector<Projectile> projectiles;        // TODO: Replace with a more efficient solution
    std::vector<MeleeMonster> meleemonsters; //Also replace maybe
    std::vector<RangedMonster> rangedmonsters; //this too

    //CREATE TEST MONSTER. COMMENT OUT LATER
    meleemonsters.push_back(MeleeMonster("test", 1, 1, 1, 20.0, 20, 4, 1.0));
    meleemonsters.begin()->setxypos(150,50);
    rangedmonsters.push_back(RangedMonster("test2", 1, 1, 1, 10.0, 50, 100.0, 80.0, &projectiles, 1.0));
    rangedmonsters.begin()->setxypos(50,150);

    //std::cout << monsters.begin()->getname() << std::endl;

    // Mock parameters start here:
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
                    float newViewWidth = (float)event.size.width / (float)event.size.height * view.getSize().y;
                    view.setSize(newViewWidth, view.getSize().y);
                    break;
                }
                default:
                    break;
            }

        }

        sf::Vector2f cDir(0, 0);
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cDir.x += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cDir.x -= 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cDir.y += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cDir.y -= 1;
        character.move(cv::normalized(cDir), elapsed, view);

    	sf::Vector2f shapepos = character.getPosition();
    	sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    	float dx = shapepos.x - mousepos.x;
    	float dy = shapepos.y - mousepos.y;
    	float rotation = (atan2(dy,dx)) * 180 / PI;
    	character.setRotation(rotation);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (elapsedSinceLastShot < 0.0f || elapsedSinceLastShot > projectileCooldown) {
                elapsedSinceLastShot = 0.0f;
                Projectile projectile(true, 5, 2, 250.0f);
                projectile.setPosition(shapepos);
                projectile.setDirection(sf::Vector2f(mousepos) - shapepos);
                if (cv::norm(projectile.getVelocity()) == 0.0f) {      // If mousepos == shapepos, there is no valid direction. In this case, simply fire the projectile in a default direction (the direction of the x axis).
                    projectile.setDirection(sf::Vector2f(1, 0));
                }
                projectiles.push_back(projectile);
            }
        }

        window.clear();
        testRoom.draw(window, s::blockDim);

        for (auto& p : projectiles) {
            p.draw(window, elapsed, testRoom);
        }
    	for (auto& p : meleemonsters) {
    	  p.monsterai(character, window, elapsed);
    	}
    	for (auto& p : rangedmonsters){
    	  p.monsterai(character,window,elapsed);
    	}
        
        window.setView(view);
        character.draw(window);
        window.display();
    }

    return 0;
}
