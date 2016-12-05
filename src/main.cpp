#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <locale>
#include "settings.hpp"
#include "room.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "convenience.hpp"
#include "monster.hpp"
#include "weapon.hpp"
#include "item.hpp"

#define PI 3.14159265358979323846F
#define FPS_SAMPLE_COUNT 80

int main()
{

    /* === FILES === */
    sf::Font standardFont;
    if (!standardFont.loadFromFile("../resources/fonts/Sansation-Regular.ttf")) {
        throw std::runtime_error("Could not load font.");
    }
    sf::Texture hpContainerTexture;
    if (!hpContainerTexture.loadFromFile("../resources/img/hp_container1.png")) {
        throw std::runtime_error("Could not load hp container texture.");
    }
    s::loadTextures();

    /* === WINDOW === */
   	sf::RenderWindow window(sf::VideoMode(800, 600), "Lost in pohjanmaa!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(4.0f / 3.0f * s::viewHeight, s::viewHeight));
    sf::View guiView(sf::Vector2f(window.getSize()) / 2.0f, sf::Vector2f(window.getSize()));

    /* === CHARACTER === */
    Character character("Test man", true, s::characterSpeed, sf::Vector2f(30.0f, 30.0f), s::characterTextureFile, s::characterShadowFile);
    view.move(character.getPosition().x, character.getPosition().y);

    /* === TESTING === */
    Room testRoom("../resources/rooms/room_large.txt", &character);
    character.setRoom(&testRoom);
    RangedWeapon fireball_weapon("Fireball", 3, 0.8f * s::blockDim, 1);

    /* === GUI === */
    sf::Vector2f healthBarMargin(15, 15);

    sf::RectangleShape healthBar(sf::Vector2f(300, 20));
    healthBar.setOrigin(healthBar.getSize() + sf::Vector2f(25, 4));
    healthBar.setFillColor(sf::Color(100, 20, 20));
    healthBar.setPosition(sf::Vector2f(window.getSize()) - healthBarMargin);

    sf::RectangleShape healthBarBackground(sf::Vector2f(300, 20));
    healthBarBackground.setOrigin(healthBar.getSize() + sf::Vector2f(25, 4));
    healthBarBackground.setFillColor(sf::Color(0, 0, 0));
    healthBarBackground.setPosition(sf::Vector2f(window.getSize()) - healthBarMargin);

    sf::Sprite hpContainer;
    hpContainer.setTexture(hpContainerTexture);
    hpContainer.setOrigin(sf::Vector2f(350, 28));
    hpContainer.setPosition(sf::Vector2f(window.getSize()) - healthBarMargin);

    sf::Text fpsIndicator;
    fpsIndicator.setFont(standardFont);
    fpsIndicator.setCharacterSize(256);
    fpsIndicator.scale(20.0f / 256.0f * sf::Vector2f(1, 1));
    fpsIndicator.setColor(sf::Color::Green);
    fpsIndicator.setPosition(sf::Vector2f(10, 10));

    /* === FUNCTIONALITY === */
    sf::Clock frameClock;
    float elapsed;
    float elapsedSinceLastShot = 1000.0f;
    float fpsSamples[FPS_SAMPLE_COUNT];
    float fpsValue = 0;
    int fpsIndex = 0;
    bool fpsIsCounting = false;
    for (auto i=0; i<FPS_SAMPLE_COUNT; ++i) fpsSamples[i] = 0;

    /* === CONTAINERS === */        // TODO: Move these out, e.g. into the Room class.
    std::vector<MeleeMonster> meleemonsters;
    std::vector<RangedMonster> rangedmonsters;

    //Monster test code. Comment out later.
    // Creates a few monsters, melee and ranged, then kills a melee monster and prints out the XP the player would gain.
    meleemonsters.push_back(MeleeMonster("test", 1, 1, 1, 40.0, 20, 4, &testRoom, 1.0));
    meleemonsters.begin()->setxypos(50,100);
    rangedmonsters.push_back(RangedMonster("test2", 1, 1, 1, 30.0, 50, 100.0, 80.0, &testRoom, 1.0));
    rangedmonsters.begin()->setxypos(50,150);

    // Mock parameters start here:
    float projectileCooldown = 0.3f;        // In seconds
    // Mock parameters end here

    window.setView(view);
    /* === THE MAIN GAME LOOP === */
	while (window.isOpen())
	{
        elapsed = frameClock.restart().asSeconds();     // The time elapsed since the last frame
        elapsedSinceLastShot += elapsed;                // The time elapsed since player's last shot
        //sf::sleep(sf::seconds(0.05f));                // Uncomment this to simulate worse fps

        /* === FPS COUNTER === */
        fpsValue -= fpsSamples[fpsIndex];
        fpsValue += elapsed;
        fpsSamples[fpsIndex] = elapsed;
        fpsIndex = (fpsIndex + 1) % FPS_SAMPLE_COUNT;
        if (fpsIndex == 0) fpsIsCounting = true;
        std::stringstream fpsSs;
        if (fpsIsCounting) {
            fpsSs << int(round(FPS_SAMPLE_COUNT / fpsValue)) << " fps";
            fpsIndicator.setString(fpsSs.str());
        } else {
            fpsSs << "Counting...";
            fpsIndicator.setString(fpsSs.str());
        }

        window.setView(view);

        /* === GENERAL EVENT HANDLING === */
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                {
                    sf::Vector2f eventSize(event.size.width, event.size.height);
                    float newViewWidth = eventSize.x / eventSize.y * view.getSize().y;
                    view.setSize(newViewWidth, view.getSize().y);
                    guiView.setSize(eventSize);
                    guiView.setCenter(eventSize / 2.0f);
                    healthBar.setPosition(eventSize - healthBarMargin);
                    healthBarBackground.setPosition(eventSize - healthBarMargin);
                    hpContainer.setPosition(eventSize - healthBarMargin);
                    break;
                }
                default:
                    break;
            }

        }

        /* === EVENT HANDLING FOR MOVEMENT === */
        sf::Vector2f cDir(0, 0);
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cDir.x += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cDir.x -= 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cDir.y += 1;
    	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cDir.y -= 1;
        character.move(cv::normalized(cDir), elapsed);

        /* === EVENT HANDLING FOR TURNING === */
    	sf::Vector2f shapepos = character.getPosition();
    	sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    	float dx = shapepos.x - mousepos.x;
    	float dy = shapepos.y - mousepos.y;
    	float rotation = (atan2(dy,dx)) * 180 / PI;
    	character.setRotation(rotation);

        /* === EVENT HANDLING FOR SHOOTING === */
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (elapsedSinceLastShot < 0.0f || elapsedSinceLastShot > projectileCooldown) {
                elapsedSinceLastShot = 0.0f;
                Projectile& projectile = fireball_weapon.createProjectile(testRoom);
                projectile.setPosition(shapepos);
                // Calculate the velocity of the projectile based on the location of the aim (mouse click) and the player's momentum:
                sf::Vector2f vel = cv::normalized(sf::Vector2f(mousepos) - shapepos) * projectile.getSpeed() + cv::normalized(cDir) * s::characterSpeed;
                projectile.setDirection(cv::normalized(vel));
                if (cv::norm(projectile.getVelocity()) == 0.0f) {      // If mousepos == shapepos, there is no valid direction. In this case, simply fire the projectile in a default direction (the direction of the x axis).
                    projectile.setDirection(sf::Vector2f(1, 0));
                }
            }
        }

        healthBar.setSize(sf::Vector2f(std::max(0.0f, 300.0f * float(character.getHealth()) / float(character.getMaxHealth())), 20));

        /* === RENDERING === */

        window.clear();
        view.setCenter(character.getPosition());
        window.setView(view);
        testRoom.draw(window);

        testRoom.drawProjectiles(window, elapsed);
    	for (auto& p : meleemonsters) {
    	  p.monsterai(character, window, elapsed);
    	}
    	for (auto& p : rangedmonsters) {
    	  p.monsterai(character,window,elapsed);
    	}

        character.draw(window);

        /* === GUI === */
        window.setView(guiView);
        window.draw(healthBarBackground);
        window.draw(healthBar);
        window.draw(hpContainer);
        window.draw(fpsIndicator);

        window.display();
    }

    return 0;
}
