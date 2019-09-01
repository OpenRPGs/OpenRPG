﻿#pragma once

#include "Entities/Player.h"
#include "GUI/PauseMenu.h"

#include "../../Maps/TileMap.h"

class GameState : public State {
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

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
	void initDeferredRender();
	void initVariable();
	void initBackground();
	void initButtons();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initPauseMenu();
	void initTileMap();
	void initView();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//함수
	void updateView(const float& dt);
	void updatePauseMenuButtons();
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseButtons();
	void updateTileMap(const float& dt);
	void updateFadeIn(float time);
	void update();
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
	void onEnter() {}
	void onLeave() {}
};
