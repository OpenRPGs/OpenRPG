#pragma once

#include "States/State.h"
#include "Entities/Player.h"

#include "GUI/Gui.h"

class PauseMenuState : public State {
  private:
	g::safe<sf::Font> font;
	g::safe<sf::Texture> btnTexture;

	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Text menuText;

	g::safemap<gui::Button> buttons;

	//함수
	void initTexture();
	void initFont();
	void initContainer();
	void initText();
	void initButtons();
	void initKeybinds();

  public:
	const StateFlow flow() {
		// 렌더링은 될 수 있음
		return StateFlow::FLOW_RENDER;
	}

	PauseMenuState();
	~PauseMenuState();

	//함수
	void updatePlayerInput(const float dt) {}
	void updateInput(const float dt);
	void update();
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
};
