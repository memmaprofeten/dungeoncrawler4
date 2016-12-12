#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <locale>
#include "settings.hpp"
#include "map.hpp"
#include "room.hpp"
#include "character.hpp"
#include "projectile.hpp"
#include "convenience.hpp"
#include "monster.hpp"
#include "weapon.hpp"
#include "item.hpp"
#include "npc.hpp"

#define FPS_SAMPLE_COUNT 80
#define FLOAT_CORRECTION 0.001F     // The Epsilon value to be used to avoid floating point errors

void drawInventory(const sf::Window& window, const sf::RectangleShape& inventoryBackground, std::vector<Item*>& inventory);
void switchRoom(int neighbour, Map& map, Character& character);

int main()
{

    /* === FILES === */
    sf::Font standardFont;
    if (!standardFont.loadFromFile("../resources/fonts/Sansation-Regular.ttf")) {
        throw std::runtime_error("Could not load font.");
    }
    sf::Font sketchFont;
    if (!sketchFont.loadFromFile("../resources/fonts/FFF_Tusj.ttf")) {
        throw std::runtime_error("Could not load font.");
    }
    sf::Texture hpContainerTexture;
    if (!hpContainerTexture.loadFromFile("../resources/img/hp_container1.png")) {
        throw std::runtime_error("Could not load hp container texture.");
    }
    s::loadTextures();
    s::loadsounds();

    /* == MUSIC == */
    // Load and loop background music.
    sf::Music backgroundmusic;
    backgroundmusic.openFromFile(s::musicstring);
    backgroundmusic.setLoop(true);
    backgroundmusic.play();

    /* === WINDOW === */
   	sf::RenderWindow window(sf::VideoMode(800, 600), "Lost in pohjanmaa!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(4.0f / 3.0f * s::viewHeight, s::viewHeight));
    sf::View guiView(sf::Vector2f(window.getSize()) / 2.0f, sf::Vector2f(window.getSize()));

    /* === GAME VARIABLES === */
    Character character("Test man", true, s::characterSpeed, sf::Vector2f(30.0f, 30.0f), 13, 10);
    view.move(character.getPosition().x, character.getPosition().y);
    Map map(character);
    Room& room = map.getRoom();
    character.setRoom(&room);

    /* === TESTING === */
    RangedWeapon fireball_weapon("Fireball", 3, 0.8f * s::blockDim, 1);

    character.addItem(new Item("Doughnut", 2, 3, 7, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Bread", 2, 2, 12, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Cake", 2, 5, 7, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Gold", 1, 10, 15, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Trophy", 4, 0, 19, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Potion of wisdom", 2, 8, 16, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Potion of strength", 2, 6, 17, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Reissumies TM", 2, 12, 18, sf::Vector2f(0, 0),1));

    /* ADD STARTING WEAPONS FOR PLAYER */
    RangedWeapon* startingrangedweapon = new RangedWeapon("Novice's Bow", 3, 0.8f * s::blockDim, 4);
    MeleeWeapon* startingmeleeweapon = new MeleeWeapon("Novice's Sword", 3, 0.8f*s::blockDim, 1);
    Item* startingrangedweaponitem = new Item("Novice's Bow", startingrangedweapon, 1, 8,sf::Vector2f(0,0));
    Item* startingmeleeweaponitem = new Item("Novice's Sword", startingmeleeweapon, 1, 8,sf::Vector2f(0,0));
    character.addItem(startingrangedweaponitem);
    character.addItem(startingmeleeweaponitem);
    startingrangedweaponitem->dothing(character);
    startingmeleeweaponitem->dothing(character);

    /* === GUI === */
    sf::Vector2f healthBarMargin(15, 15);

    sf::RectangleShape healthBar(sf::Vector2f(300, 20));
    healthBar.setOrigin(healthBar.getSize() + sf::Vector2f(25, 4));
    healthBar.setFillColor(sf::Color(100, 20, 20));

    sf::RectangleShape healthBarBackground(sf::Vector2f(300, 20));
    healthBarBackground.setOrigin(healthBar.getSize() + sf::Vector2f(25, 4));
    healthBarBackground.setFillColor(sf::Color(0, 0, 0));

    sf::Sprite hpContainer;
    hpContainer.setTexture(hpContainerTexture);
    hpContainer.setOrigin(sf::Vector2f(350, 28));

    sf::Text fpsIndicator;
    fpsIndicator.setFont(standardFont);
    fpsIndicator.setCharacterSize(256);
    fpsIndicator.setScale(20.0f / 256.0f * sf::Vector2f(1, 1));
    fpsIndicator.setColor(sf::Color::Green);
    fpsIndicator.setPosition(sf::Vector2f(10, 10));

    sf::Text pausedIndicator;
    pausedIndicator.setString("GAME PAUSED");
    pausedIndicator.setFont(sketchFont);
    pausedIndicator.setCharacterSize(256);
    pausedIndicator.setScale(60.0f / 256.0f * sf::Vector2f(1, 1));
    pausedIndicator.setOrigin(sf::Vector2f(pausedIndicator.getLocalBounds().width / 2.0f, pausedIndicator.getLocalBounds().height / 2.0f));
    pausedIndicator.setColor(sf::Color::Green);

    sf::RectangleShape inventoryBackground;
    inventoryBackground.setFillColor(sf::Color(20, 10, 10, 200));

    sf::RectangleShape tooltipBackground;
    tooltipBackground.setFillColor(sf::Color(0, 0, 0, 220));

    sf::Text tooltip;
    tooltip.setPosition(sf::Vector2f(10, 10));
    tooltip.setFont(standardFont);
    tooltip.setCharacterSize(256);
    tooltip.setScale(20.0f / 256.0f * sf::Vector2f(1, 1));
    tooltip.setColor(sf::Color::Green);

    /* === FUNCTIONALITY === */
    bool mouseReleased = true;
    bool paused = false;
    bool pauseReleased = true;
    bool pauseReset = true;
    bool focused = true;
    bool inventory = false;
    bool tooltipShowing = true;
    sf::Clock frameClock;
    float elapsed;
    float elapsedSinceLastAttack = 1000.0f;
    float elapsedSinceLastShot = 1000.0f;
    float fpsSamples[FPS_SAMPLE_COUNT];
    float fpsValue = 0;
    int fpsIndex = 0;
    bool fpsIsCounting = false;
    for (auto i=0; i<FPS_SAMPLE_COUNT; ++i) fpsSamples[i] = 0;

    /* === CONTAINERS === */        // TODO: Move these out, e.g. into the Room class.
    //Monster test code. Comment out later.
    // Creates a few monsters, melee and ranged, then kills a melee monster and prints out the XP the player would gain.
    //CreateMonster(sf::Vector2f(75,75), &room, 1);
    //CreateMonster(sf::Vector2f(50,50), &room, 1);
    map.getRoom().addmonster( new MeleeMonster(sf::Vector2f(20,20), &(map.getRoom()), 1) );
    map.getRoom().addNpc(new Shopkeeper(0, sf::Vector2f(40,40)));


/*    meleemonsters.push_back(MeleeMonster("test", 1, 1, 1, 40.0, 20, 4, &room, 1.0));
    meleemonsters.begin()->setxypos(50,100);
    rangedmonsters.push_back(RangedMonster("test2", 1, 1, 1, 30.0, 50, 100.0, 80.0, &room, 1.0));
    rangedmonsters.begin()->setxypos(50,150);
*/

    // Mock parameters start here:
    //float meleeCooldown = 0.2f;             // In seconds
    //float projectileCooldown = 0.6f;        // In seconds
    // Mock parameters end here

    window.setView(view);
    /* === THE MAIN GAME LOOP === */
	while (window.isOpen())
	{

        /* === GENERAL EVENT HANDLING === */
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::LostFocus:
                    std::cout << "Lost focus" << std::endl;
                    focused = false;
                    break;
                case sf::Event::GainedFocus:
                    std::cout << "Gained focus" << std::endl;
                    focused = true;
                    break;
                case sf::Event::Resized:
                {
                    sf::Vector2f eventSize(event.size.width, event.size.height);
                    float newViewWidth = eventSize.x / eventSize.y * view.getSize().y;
                    view.setSize(newViewWidth, view.getSize().y);
                    // GUI:
                    guiView.setSize(eventSize);
                    guiView.setCenter(eventSize / 2.0f);
                    healthBar.setPosition(eventSize - healthBarMargin);
                    healthBarBackground.setPosition(eventSize - healthBarMargin);
                    hpContainer.setPosition(eventSize - healthBarMargin);
                    pausedIndicator.setPosition(sf::Vector2f(window.getSize()) / 2.0f);
                    // Inventory:
                    inventoryBackground.setSize(s::relativeInventoryBackgroundWidth * sf::Vector2f(window.getSize()));
                    inventoryBackground.setOrigin(sf::Vector2f(inventoryBackground.getLocalBounds().width / 2.0f, inventoryBackground.getLocalBounds().height / 2.0f));
                    inventoryBackground.setPosition(sf::Vector2f(window.getSize()) / 2.0f);
                    drawInventory(window, inventoryBackground, character.getInventory());
                    break;
                }
                default:
                    break;
            }
        }

        /* === GAMEPLAY LOOP === */
        if (!paused && focused) {
            elapsed = frameClock.restart().asSeconds();     // The time elapsed since the last frame
            elapsedSinceLastAttack += elapsed;
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
                fpsSs << int(round(float(FPS_SAMPLE_COUNT) / fpsValue)) << " fps";
                fpsIndicator.setString(fpsSs.str());
            } else {
                fpsSs << "Counting...";
                fpsIndicator.setString(fpsSs.str());
            }

            window.setView(view);



            /* === GENERAL EVENT HANDLING === */
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) if (pauseReleased) {
                paused = true;
                pauseReleased = false;
                pauseReset = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) if (pauseReleased) {
                paused = true;
                pauseReleased = false;
                pauseReset = false;
                inventory = true;
            }

            /* === EVENT HANDLING FOR MOVEMENT === */
            sf::Vector2f cDir(0, 0);
        	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cDir.x += 1;
        	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cDir.x -= 1;
        	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cDir.y += 1;
        	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cDir.y -= 1;
            sf::Vector2f cdPos = cv::normalized(cDir);
            sf::Vector2i offset = room.getOffsetDirection(character.getHypotheticalPosition(cdPos, elapsed));   // Check if the player has left the room
            if (offset.x > 0)       switchRoom(0, map, character);
            else if (offset.y > 0)  switchRoom(1, map, character);
            else if (offset.x < 0)  switchRoom(2, map, character);
            else if (offset.y < 0)  switchRoom(3, map, character);
            character.move(cdPos, elapsed);

            /* === EVENT HANDLING FOR TURNING === */
        	sf::Vector2f charpos = character.getPosition();
        	sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        	float dx = charpos.x - mousepos.x;
        	float dy = charpos.y - mousepos.y;
        	float rotation = (atan2(dy,dx)) * 180 / cv::PI;
        	character.setRotation(rotation);

            /* === EVENT HANDLING FOR ATTACKING === */
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {      // Melee attack
	      if (elapsedSinceLastAttack < 0.0f || elapsedSinceLastAttack > character.getmeleeweapon()->getcooldown()) {
                    elapsedSinceLastAttack = 0.0f;
                    room.performAttack(true, character.getPosition(), cv::normalized(mousepos - charpos), *character.getmeleeweapon());  // TODO. Replace with player's real weapon
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {     // Missile attack
	      if (elapsedSinceLastShot < 0.0f || elapsedSinceLastShot > character.getrangedweapon()->getcooldown()) {
                    elapsedSinceLastShot = 0.0f;
                    Projectile& projectile = character.getrangedweapon()->createProjectile(room);
                    projectile.setPosition(charpos);
                    // Calculate the velocity of the projectile based on the location of the aim (mouse click) and the player's momentum:
                    sf::Vector2f vel = cv::normalized(mousepos - charpos) * projectile.getSpeed() + cv::normalized(cDir) * s::characterSpeed;
                    projectile.setDirection(cv::normalized(vel));
                    if (cv::norm(projectile.getVelocity()) == 0.0f) {      // If mousepos == charpos, there is no valid direction. In this case, simply fire the projectile in a default direction (the direction of the x axis).
                        projectile.setDirection(sf::Vector2f(1, 0));
                    }
                }
            }

            healthBar.setSize(sf::Vector2f(std::max(0.0f, 300.0f * float(character.getHealth()) / float(character.getMaxHealth())), 20));

            /* === RENDERING === */

            window.clear();
            view.setCenter(character.getPosition());
            window.setView(view);
            room.draw(window);
/*
        	for (auto& p : meleemonsters) {
        	  p.monsterai(character, window, elapsed);
        	}
        	for (auto& p : rangedmonsters) {
        	  p.monsterai(character,window,elapsed);
        	}
*/
            map.getRoom().drawmonsters(elapsed);
            map.getRoom().drawnpcs(window);
            map.getRoom().drawitems(window);

            character.draw(window);

            room.drawProjectiles(window, elapsed);

            /* === GUI === */
            window.setView(guiView);
            window.draw(healthBarBackground);
            window.draw(healthBar);
            window.draw(hpContainer);
            window.draw(fpsIndicator);

            window.display();

        /* === PAUSED LOOP === */
        } else {

            tooltipShowing = false;

            /* === PAUSED EVENT HANDLING === */
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                if (pauseReleased) pauseReset = true;
                pauseReleased = false;
            } else {
                pauseReleased = true;
                if (pauseReset) {           // Continue game:
                    paused = false;
                    inventory = false;
                    frameClock.restart();   // The time elapsed since the last frame
                }
            }

            /* === PAUSED RENDERING === */
            if (paused || !focused) {               // Check if still paused
                window.clear();
                view.setCenter(character.getPosition());
                window.setView(view);
                room.draw(window);
                character.draw(window);
                window.setView(guiView);
                if (inventory) {
                    // Track mouse position:
                    sf::Vector2f mousepos = sf::Vector2f(sf::Mouse::getPosition(window));
                    sf::Vector2f globalOffset = sf::Vector2f(window.getSize()) * 0.5f * (1.0f - s::relativeInventoryBackgroundWidth);
                    float rawDim = float(window.getSize().x) * s::relativeInventoryBackgroundWidth / float(s::itemsPerRow); // The dimension of an item slot including its margins
                    float xir = (mousepos.x - globalOffset.x) / rawDim;
                    float yir = (mousepos.y - globalOffset.y) / rawDim;
                    int xi = int(floor(xir));       // The horizontal index of the current item in the inventory grid
                    int yi = int(floor(yir));       // The vertical index of the current item in the inventory grid
                    int itemIndex = yi * s::itemsPerRow + xi;       // The actual index in the character's inventory of the item being hovered over
                    float relativeItemMarginToItem = s::relativeItemMargin * (float)s::itemsPerRow / s::relativeInventoryBackgroundWidth;
                    if (xi >= 0 && xi < s::itemsPerRow &&
                        yi >= 0 && itemIndex < (int)character.getInventory().size() &&
                        xir - (int)xir >= relativeItemMarginToItem && xir - (int)xir <= 1.0f - relativeItemMarginToItem &&  // Check if the cursor is on top of a horizontal margin
                        yir - (int)yir >= relativeItemMarginToItem && yir - (int)yir <= 1.0f - relativeItemMarginToItem     // Check if the cursor is on top of a vertical margin
                    ) {
                        // Show tooltip:
                        std::stringstream tooltipSs;
                        tooltipSs << character.getInventory()[itemIndex]->getname();
                        tooltip.setString(tooltipSs.str());
                        tooltipShowing = true;
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (tooltipShowing && mouseReleased) {
                            std::cout << "Using " + character.getInventory()[itemIndex]->getname() << "." << std::endl;
                            bool couldConsume = character.consumeItem(itemIndex);
                            if (couldConsume) {
                                //testItemTextureVector.erase(testItemTextureVector.begin() + itemIndex);
                                //testItemSpriteVector.erase(testItemSpriteVector.begin() + itemIndex);
                                character.consumeItem(itemIndex);
                                drawInventory(window, inventoryBackground, character.getInventory());
                            }
                        }
                        mouseReleased = false;
                    } else {
                        mouseReleased = true;
                    }

                    window.draw(inventoryBackground);
                    //for (const auto& sprite : testItemSpriteVector) window.draw(sprite);
                    for (Item* itemPtr : character.getInventory()) window.draw(itemPtr->getInventorySprite());
                    if (tooltipShowing) window.draw(tooltip);
                }
                else window.draw(pausedIndicator);
                window.display();
            }
        }
    }

    return 0;
}

void drawInventory(const sf::Window& window, const sf::RectangleShape& inventoryBackground, std::vector<Item*>& inventory) {
    sf::Vector2f invDim = inventoryBackground.getSize();
    float invMargin = invDim.x * s::relativeItemMargin;
    float itemDim = (invDim.x - float(s::itemsPerRow) * 2.0f * invMargin) / float(s::itemsPerRow);
    for (int i=0; i<(int)inventory.size(); ++i) {
        Item* item = inventory[i];
        item->getInventorySprite().setScale(sf::Vector2f(itemDim / 32.0f, itemDim / 32.0f));
        item->getInventorySprite().setPosition(0.5f * (1.0f - s::relativeInventoryBackgroundWidth) * sf::Vector2f(window.getSize()) + sf::Vector2f((i % s::itemsPerRow) * (itemDim + 2.0f * invMargin) + invMargin, (i / s::itemsPerRow) * (itemDim + 2.0f * invMargin) + invMargin));
    }
}

/* Switches to the room that is the ith neighbour of the current room, where
 * i is defined by the 'neighbour' parameter.
 * The neighbour indices are defined in the following way:
 * 		- 0: east
 * 		- 1: south
 * 		- 2: west
 * 		- 3: north
 */
void switchRoom(int neighbour, Map& map, Character& character) {
    Room& newRoom = map.switchRoom(neighbour);
    character.setRoom(&newRoom);
    sf::Vector2f pos = character.getPosition();
    switch (neighbour) {
        case 0:
            pos.x = 0 + FLOAT_CORRECTION;
            break;
        case 1:
            pos.y = 0 + FLOAT_CORRECTION;
            break;
        case 2:
            pos.x = newRoom.getWidth() * s::blockDim - FLOAT_CORRECTION;
            break;
        case 3:
            pos.y = newRoom.getHeight() * s::blockDim - FLOAT_CORRECTION;
            break;
        default:
            pos.x = newRoom.getWidth() * s::blockDim / 2.0f;
            pos.y = newRoom.getHeight() * s::blockDim / 2.0f;
            break;
    }
    character.setPosition(pos);
}
