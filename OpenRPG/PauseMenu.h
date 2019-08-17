#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

#include "Button.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;
	


public:

	PauseMenu(sf::RenderWindow& window,sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text, sf::Texture& btnTexure);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

#endif // !PAUSEMENU_H
