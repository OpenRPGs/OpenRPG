#pragma once

#include "States/State.h"
#include "Entities/Player.h"

class GameState : public State {
  private:
	sf::Font font;
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
	const StateFlow flow() {
		// 흐를 수 없음
		return StateFlow::FLOW_NONE;
	}

	GameState();
	~GameState();

	//함수
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void updatePauseButtons();
	void update();
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
};
