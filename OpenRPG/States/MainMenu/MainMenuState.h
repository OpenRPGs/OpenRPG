#pragma once

#include "GUI/Button.h"

class MainMenuState : public State {
  private:
	//변수
	sf::Texture backgroundTexture;
	sf::Texture btnTexure;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//함수
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

  public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	//함수

	void updateInput(const float& dt);
	void updateButtons();
	void update();
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated();
	void onDeactivated();
	void onEnter() {}
	void onLeave() {}
};
