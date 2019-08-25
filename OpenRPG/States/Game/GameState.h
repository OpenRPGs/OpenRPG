#pragma once

#include "States/State.h"
#include "Entities/Player.h"

#include "Maps/TileMap.h"

class GameState : public State {
  private:
	g::safe<sf::Font> font;
	g::safe<sf::Texture> btnTexture;

	g::safe<sf::Texture> texture;
	g::safe<Player> player;

	g::safe<TileMap> tileMap;

	//함수
	void initButtons();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initFonts();
	void initTileMap();

  public:
	const StateFlow flow() {
		// 흐를 수 없음
		return StateFlow::FLOW_NONE;
	}

	GameState();
	~GameState();
	void onActivated() {}
	void onDeactivated() {}

	//함수
	void updatePauseButtons();
	void updatePlayerInput(const float dt);
	void updateInput(const float dt);
	void update();

	void render(sf::RenderTexture* target);
};
