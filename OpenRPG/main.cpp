#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/Graphics.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenRGP Game!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

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
		window.display();
	}

	return 0;
}