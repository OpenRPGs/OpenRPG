#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
class GameState :
	public State
{
private:

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	//ÇÔ¼ö
	void endState();

	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};
#endif
