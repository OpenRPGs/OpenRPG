#pragma once

#include "States/State.h"
#include "Entities/Player.h"

#include "GUI/Gui.h"

class PauseMenuState : public State {
  private:
	State* parent;

	sf::Font font;
	sf::Texture btnTexture;

	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Text menuText;

	std::map<std::string, gui::Button*> buttons;

	//함수
	void initBackground();
	void initContainer();
	void initText();
	void initButtons();
	void initKeybinds();

  public:
	const StateFlow flow() {
		// 렌더링은 될 수 있음
		return StateFlow::FLOW_RENDER;
	}

	PauseMenuState(State* parent);
	~PauseMenuState();

	//함수
	void updatePlayerInput(const float& dt);
	void updateInput(const float& dt);
	void update();
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
};
