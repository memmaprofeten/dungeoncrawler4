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

void drawInventory(const sf::Window& window, const sf::RectangleShape& inventoryBackground, std::vector<Item*>& inventory);
void switchRoom(int neighbour, Map& map, Character& character);

int main()
{

    srand(time(0));     // Initialize the randomizer once, for the rest of the program to use

    /* === FILES === */
    s::loadTextures();
    s::loadsounds();
    sf::Font standardFont;
    if (!standardFont.loadFromFile("../resources/fonts/Sansation-Regular.ttf")) {
        throw std::runtime_error("Could not load font.");
    }
    sf::Font sketchFont;
    if (!sketchFont.loadFromFile("../resources/fonts/FFF_Tusj.ttf")) {
        throw std::runtime_error("Could not load font.");
    }
    sf::Texture cursorTexture = s::textures[20];
    sf::Texture hpContainerTexture;
    if (!hpContainerTexture.loadFromFile("../resources/img/hp_container1.png")) {
        throw std::runtime_error("Could not load hp container texture.");
    }

    /* == MUSIC == */
    // Load and loop background music.
    sf::Music backgroundmusic;
    backgroundmusic.openFromFile(s::musicstring);
    backgroundmusic.setLoop(true);
    backgroundmusic.setVolume(50);
    backgroundmusic.play();

    sf::Sound newsound;

    /* === WINDOW === */
    sf::Vector2i defaultWindowSize(800, 600);
   	sf::RenderWindow window(sf::VideoMode(defaultWindowSize.x, defaultWindowSize.y), "Lost in pohjanmaa!");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(4.0f / 3.0f * s::viewHeight, s::viewHeight));
    sf::View guiView(sf::Vector2f(window.getSize()) / 2.0f, sf::Vector2f(window.getSize()));

    /* === GAME VARIABLES === */
    Character character("Test man", true, s::characterSpeed, sf::Vector2f(30.0f, 30.0f), 13, 10);
    view.move(character.getPosition().x, character.getPosition().y);
    Map map(character);
    Room& room = map.getRoom();
    character.setRoom(&room);
    character.givegold(s::startingGold);

    /* === TESTING === */
    //RangedWeapon fireball_weapon("Fireball", 3, 0.8f * s::blockDim, 1);

    /* === INITIAL INVENTORY FILL === */
    character.addItem(new Item("Doughnut", 2, 3, 7, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Bread", 2, 2, 12, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Cake", 2, 5, 24, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Trophy", 4, 0, 19, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Potion of wisdom", 2, 8, 16, sf::Vector2f(0, 0),1));
    character.addItem(new Item("Potion of strength", 2, 6, 17, sf::Vector2f(0, 0),1));

    /* ADD STARTING WEAPONS FOR PLAYER */
    RangedWeapon* startingrangedweapon = new RangedWeapon("Novice's Bow", 3, 4);
    MeleeWeapon* startingmeleeweapon = new MeleeWeapon("Novice's Sword", 3, 0.0f, 2 * s::blockDim, 8);
    Item* startingrangedweaponitem = new Item("Novice's Bow", startingrangedweapon, 1, 23,sf::Vector2f(0,0));
    Item* startingmeleeweaponitem = new Item("Novice's Sword", startingmeleeweapon, 1, 8,sf::Vector2f(0,0));
    character.addItem(startingrangedweaponitem);
    character.addItem(startingmeleeweaponitem);
    startingrangedweaponitem->dothing(character);
    startingmeleeweaponitem->dothing(character);

    /* === GUI === */
    sf::Sprite cursor(cursorTexture);
    cursor.setOrigin(16, 16);

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

    sf::Text levelIndicator;
    levelIndicator.setFont(standardFont);
    levelIndicator.setCharacterSize(256);
    levelIndicator.setScale(30.0f / 256.0f * sf::Vector2f(1, 1));
    levelIndicator.setColor(sf::Color(0, 255, 255));

    sf::Text goldIndicator;
    goldIndicator.setFont(standardFont);
    goldIndicator.setCharacterSize(256);
    goldIndicator.setScale(30.0f / 256.0f * sf::Vector2f(1, 1));
    goldIndicator.setColor(sf::Color::Yellow);

    sf::Text mainTextIndicator;
    mainTextIndicator.setFont(sketchFont);
    mainTextIndicator.setCharacterSize(256);
    mainTextIndicator.setScale(60.0f / 256.0f * sf::Vector2f(1, 1));
    mainTextIndicator.setOrigin(sf::Vector2f(mainTextIndicator.getLocalBounds().width / 2.0f, mainTextIndicator.getLocalBounds().height / 2.0f));

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
    bool shopInventory = false;
    bool tooltipShowing = true;
    sf::Clock frameClock;
    float elapsed;
    float deathMessageCountdown = 0.0f;
    float elapsedSinceLastAttack = 1000.0f;
    float elapsedSinceLastShot = 1000.0f;
    float fpsSamples[FPS_SAMPLE_COUNT];
    float fpsValue = 0;
    int fpsIndex = 0;
    bool fpsIsCounting = false;
    for (auto i=0; i<FPS_SAMPLE_COUNT; ++i) fpsSamples[i] = 0;
    Npc* closestNpc; // Pointer to the last NPC the player has been in range to
    std::vector<Item*> renderInventory = character.getInventory(); // The inventory to pass when drawing inventory screen

    /* === CONTAINERS === */        // TODO: Move these out, e.g. into the Room class.
    //Monster test code. Comment out later.
    // Creates a few monsters, melee and ranged, then kills a melee monster and prints out the XP the player would gain.
    //CreateMonster(sf::Vector2f(75,75), &room, 1);
    //CreateMonster(sf::Vector2f(50,50), &room, 1);
    //map.getRoom().addmonster( new MeleeMonster(sf::Vector2f(20,20), &(map.getRoom()), 1) );
    map.getRoom().addNpc(new Shopkeeper(0, sf::Vector2f(40,70)));

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
                    focused = false;
                    break;
                case sf::Event::GainedFocus:
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
                    cursor.setScale(sf::Vector2f((float)eventSize.y / (float)defaultWindowSize.y, (float)eventSize.y / (float)defaultWindowSize.y));
                    healthBar.setPosition(eventSize - healthBarMargin);
                    healthBarBackground.setPosition(eventSize - healthBarMargin);
                    hpContainer.setPosition(eventSize - healthBarMargin);
                    mainTextIndicator.setPosition(sf::Vector2f(window.getSize()) / 2.0f);
                    levelIndicator.setPosition(sf::Vector2f(window.getSize()) - sf::Vector2f(100, 100));
                    goldIndicator.setPosition(sf::Vector2f(window.getSize()) - sf::Vector2f(240, 100));
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

            window.setMouseCursorVisible(false);
            elapsed = frameClock.restart().asSeconds();     // The time elapsed since the last frame
            deathMessageCountdown -= elapsed;
            elapsedSinceLastAttack += elapsed;
            elapsedSinceLastShot += elapsed;                // The time elapsed since player's last shot
            //sf::sleep(sf::seconds(0.05f));                // Uncomment this to simulate worse fps
            if (character.getHealth() <= 0) {
                deathMessageCountdown = s::deathMessageDuration;
                character.setLevel(std::max(1, character.getlevel() - 1));
                character.sethealth(character.getMaxHealth());
                character.givegold(int(round(s::percentageOfGoldLostAtDeath * (float)character.getgold())));
                switchRoom(-1, map, character);
            }

            /* === Level and gold indicators === */
            std::stringstream lvlSs;
            lvlSs << "Lvl " << character.getlevel();
            levelIndicator.setString(lvlSs.str());
            std::stringstream goldSs;
            goldSs << "Gold " << character.getgold();
            goldIndicator.setString(goldSs.str());

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

            /* === CURSOR === */
            sf::Vector2i windowMousePos = sf::Mouse::getPosition(window);
            cursor.setPosition(static_cast<sf::Vector2f>(windowMousePos));

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
                drawInventory(window, inventoryBackground, character.getInventory());
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
            sf::Vector2f mousepos = window.mapPixelToCoords(windowMousePos);
            float dx = charpos.x - mousepos.x;
            float dy = charpos.y - mousepos.y;
            float rotation = (atan2(dy,dx)) * 180 / cv::PI;
            character.setRotation(rotation);

            /* === EVENT HANDLING FOR ATTACKING === */
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {      // Melee attack
                if (elapsedSinceLastAttack < 0.0f || elapsedSinceLastAttack > character.getmeleeweapon()->getcooldown()) {
                    //Melee attack sound sf::Sound newsound;
                    newsound.setBuffer(s::soundbuffers[0]);
                    newsound.play();
                    character.initiateMeleeAttack();        // Enable the relevant animations
                    elapsedSinceLastAttack = 0.0f;
                    room.performAttack(true, character.getPosition(), cv::normalized(mousepos - charpos), *character.getmeleeweapon());  // TODO. Replace with player's real weapon
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {     // Missile attack
                if (elapsedSinceLastShot < 0.0f || elapsedSinceLastShot > character.getrangedweapon()->getcooldown()) {
                    //Sound for ranged attacks sf::Sound newsound;
                    switch(character.getrangedweapon()->gettextureindex()){
                        case 1:{
                            newsound.setBuffer(s::soundbuffers[2]);
                            break;
                        }
                        case 4:{
                            newsound.setBuffer(s::soundbuffers[1]);
                            break;
                        }
                    }
                    newsound.play();
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

            // Should we display NPC dialogs?
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || shopInventory) {
                for (Npc* npcPtr : map.getRoom().getNpcs()) {
                    if(npcPtr->isInRange()) {
                        paused = true;
                        pauseReleased = false;
                        pauseReset = false;
                        shopInventory = true;
                        closestNpc = npcPtr;
                        renderInventory = closestNpc->getInventory();
                        drawInventory(window, inventoryBackground, renderInventory);
                    }
                }
            }

            healthBar.setSize(sf::Vector2f(std::max(0.0f, 300.0f * float(character.getHealth()) / float(character.getMaxHealth())), 20));


            /* === RENDERING === */
            window.clear();
            view.setCenter(character.getPosition());
            window.setView(view);
            room.draw(window);
            map.getRoom().drawmonsters(elapsed);
            map.getRoom().drawnpcs(window);
            map.getRoom().drawitems(window);
            character.draw(window, elapsed);
            room.drawProjectiles(window, elapsed);

            /* === GUI === */
            window.setView(guiView);
            window.draw(healthBarBackground);
            window.draw(healthBar);
            window.draw(hpContainer);
            if (deathMessageCountdown > 0.0f) {
                mainTextIndicator.setString("YOU DIED!");
                mainTextIndicator.setOrigin(sf::Vector2f(mainTextIndicator.getLocalBounds().width / 2.0f, mainTextIndicator.getLocalBounds().height / 2.0f));
                mainTextIndicator.setColor(sf::Color(255, 0, 0));
                window.draw(mainTextIndicator);
            }
            window.draw(levelIndicator);
            window.draw(goldIndicator);
            window.draw(fpsIndicator);
            window.draw(cursor);

            window.display();

        /* === PAUSED LOOP === */
        } else {

            window.setMouseCursorVisible(true);

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
                    shopInventory = false;
                    frameClock.restart();   // The time elapsed since the last frame
                }
            }

            /* === PAUSED RENDERING === */
            if (paused || !focused) {               // Check if still paused
                window.clear();
                view.setCenter(character.getPosition());
                window.setView(view);
                room.draw(window);
                character.draw(window, elapsed);
                window.setView(guiView);
                if (inventory || shopInventory) {
                    // Display player's or NPC's inventory?
                    if(inventory)
                        renderInventory = character.getInventory();

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
                        yi >= 0 && itemIndex < (int)renderInventory.size() &&
                        xir - (int)xir >= relativeItemMarginToItem && xir - (int)xir <= 1.0f - relativeItemMarginToItem &&  // Check if the cursor is on top of a horizontal margin
                        yir - (int)yir >= relativeItemMarginToItem && yir - (int)yir <= 1.0f - relativeItemMarginToItem     // Check if the cursor is on top of a vertical margin
                    ) {
                        // Show tooltip:
                        std::stringstream tooltipSs;
                        tooltipSs << renderInventory[itemIndex]->getname();
                        tooltip.setString(tooltipSs.str());
                        tooltipShowing = true;
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (tooltipShowing && mouseReleased) {
                            if(inventory) {                         // Item action for player's inventory
                                std::cout << "Using " + renderInventory[itemIndex]->getname() << "." << std::endl;
                                bool couldConsume = character.consumeItem(itemIndex);
                                if (couldConsume) {
                                    character.consumeItem(itemIndex);
                                    drawInventory(window, inventoryBackground, renderInventory);
                                }
                            }
                            else if(shopInventory) {                // Item action for NPC's inventory
                                std::cout << "Bought " + renderInventory[itemIndex]->getname() << "." << std::endl;
                                character.getInventory().push_back(renderInventory[itemIndex]); // Add item to player's inventory...
                                closestNpc->removeFromInventory(itemIndex);                     // and remove it from NPC's inventory (buying an item)
                                paused = false;                                                 // Refresh inventory screen
                            }
                        }
                        mouseReleased = false;
                    } else {
                        mouseReleased = true;
                    }

                    window.draw(inventoryBackground);
                    for (Item* itemPtr : renderInventory) window.draw(itemPtr->getInventorySprite());
                    if (tooltipShowing) window.draw(tooltip);
                }
                else {
                    mainTextIndicator.setString("GAME PAUSED");
                    mainTextIndicator.setOrigin(sf::Vector2f(mainTextIndicator.getLocalBounds().width / 2.0f, mainTextIndicator.getLocalBounds().height / 2.0f));
                    mainTextIndicator.setColor(sf::Color(30, 200, 30));
                    window.draw(mainTextIndicator);
                }
                window.display();
            }
        }
    }

    return 0;
}

/**
 * Sets the given inventory ready for drawing
 */
void drawInventory(const sf::Window& window, const sf::RectangleShape& inventoryBackground, std::vector<Item*>& inventory) {
    sf::Vector2f invDim = inventoryBackground.getSize();
    float invMargin = invDim.x * s::relativeItemMargin;
    float itemDim = (invDim.x - float(s::itemsPerRow) * 2.0f * invMargin) / float(s::itemsPerRow);
    for (int i=0; i<(int)inventory.size(); ++i) {
        inventory[i]->getInventorySprite().setScale(sf::Vector2f(itemDim / 32.0f, itemDim / 32.0f));
        inventory[i]->getInventorySprite().setPosition(0.5f * (1.0f - s::relativeInventoryBackgroundWidth) * sf::Vector2f(window.getSize()) + sf::Vector2f((i % s::itemsPerRow) * (itemDim + 2.0f * invMargin) + invMargin, (i / s::itemsPerRow) * (itemDim + 2.0f * invMargin) + invMargin));
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
            pos.x = 0 + s::floatCorrection;
            break;
        case 1:
            pos.y = 0 + s::floatCorrection;
            break;
        case 2:
            pos.x = newRoom.getWidth() * s::blockDim - s::floatCorrection;
            break;
        case 3:
            pos.y = newRoom.getHeight() * s::blockDim - s::floatCorrection;
            break;
        default:
            pos.x = newRoom.getWidth() * s::blockDim / 2.0f;
            pos.y = newRoom.getHeight() * s::blockDim / 2.0f;
            break;
    }
    character.setPosition(pos);
}
