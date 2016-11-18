#include <SFML/Graphics.hpp>
#include <cmath>
int main()
{
   	sf::RenderWindow window(sf::VideoMode(800, 600), "The game!");
    	sf::CircleShape shape(20,3);
	shape.setOrigin(20,20);
    	shape.setFillColor(sf::Color::Red);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		shape.move(1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		shape.move(-1,0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		shape.move(0,1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		shape.move(0,-1);
	}
	sf::Vector2f shapepos = shape.getPosition();
	sf::Vector2i mousepos = sf::Mouse::getPosition(window);
	//sf::Vector2f enemypos = enemy.getPosition();
	float dx = shapepos.x - mousepos.x;
	float dy = shapepos.y - mousepos.y;
	float rotation = (atan2(dy,dx)) * 180 / PI;
	shape.setRotation(rotation+30);
    }

    return 0;
}
