#pragma once

#include "States/State.h"
#include "GUI/Gui.h"

class MainMenuState : public State {
  private:
	//변수
	sf::Texture* backgroundTexture;
	sf::Texture* btnTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//함수
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initSounds();

  public:
	const StateFlow flow() {
		// 흐를 수 없음
		return StateFlow::FLOW_NONE;
	}

	MainMenuState() : State() {}

	//함수
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget* target);

	void update();
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onEnter();
	void onActivated() {}
	void onDeactivated() {}
	void onLeave();
};
