#pragma once

#include "Entities/Player.h"
#include "GUI/PauseMenu.h"

#include "../../Maps/TileMap.h"

class GameState : public State {
  private:
	int window_focus;

	sf::Font font;
	PauseMenu* pmenu;
	sf::Texture btnTexure;

	Player* player;
	sf::Texture texture;

	TileMap* tileMap;

	//함수
	void initButtons();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();
	void initTileMap();

  public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//함수
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseButtons();
	void update();
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
	void onEnter() {}
	void onLeave() {}
};
