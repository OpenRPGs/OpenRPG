#pragma once

#include "State.h"

class Button;

class SettingsState :
	public State
{
private:
	sf::Texture backgroundTexture;
	sf::Texture btnTexure;
	sf::RectangleShape background;
	sf::Font font;
	sf::Texture	tx;

	std::map<std::string, Button* > buttons;

	//초기화 함수
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	//void initMusic();

public:
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	//접근자

	//업데이트함수
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);

	//랜더함수
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

