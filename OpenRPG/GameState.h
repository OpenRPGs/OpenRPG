#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
class GameState :
	public State
{
private:
	Entity player;

	//함수
	void initKeybinds();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();

	//함수
	void endState();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
#endif
