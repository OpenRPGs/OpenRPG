#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
class MainMenuState :
	public State
{
private:
	Entity player;
	//변수
	sf::RectangleShape background;

	//함수
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
