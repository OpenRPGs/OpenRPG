#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState :
	public State
{
private:
	//변수
	sf::RectangleShape background;
	sf::Font font;

	Button* gamestate_btn;


	//함수
	void initFonts();
	void initKeybinds();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	//함수
	void endState();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
#endif
