#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"

class GameState :
	public State
{
private:
	sf::Font font;
	PauseMenu* pmenu;
	sf::Texture btnTexure;

	Player* player;
	sf::Texture texture;

	//함수
	void initButtons();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//함수
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};
#endif
