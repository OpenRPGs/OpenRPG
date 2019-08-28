#pragma once

#include "Entities/Player.h"
#include "GUI/PauseMenu.h"

#include "../../Maps/TileMap.h"

class GameState : public State {
private:
	int window_focus;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	bool fadInFlag;
	float backGroundColor;

	sf::Font font;
	PauseMenu* pmenu;
	sf::Texture btnTexure;

	Player* player;
	sf::Texture texture;

	TileMap* tileMap;

	//함수
	void initVariable();
	void initBackground();
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
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseButtons();
	void updateFadeIn(const float& dt);
	void update();
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
	void onEnter() {}
	void onLeave() {}
};
