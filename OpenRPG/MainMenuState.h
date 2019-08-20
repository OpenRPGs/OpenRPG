﻿#pragma once

class Button;
class SoundComponent;

class MainMenuState :
	public State
{
private:
	//변수
	sf::Texture backgroundTexture;
	sf::Texture btnTexure;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button* > buttons;

	//함수
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initMusic();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//함수

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};

