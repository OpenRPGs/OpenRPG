#pragma once

#include "States/State.h"
#include "GUI/Gui.h"

class MainMenuState : public State {
  private:
	//변수
	g::safe<sf::Texture> backgroundTexture;
	g::safe<sf::Texture> btnTexture;
	g::safe<sf::Font> font;
	sf::RectangleShape background;

	g::safemap<gui::Button> buttons;

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

	MainMenuState();
	~MainMenuState();
	void onActivated() {}
	void onDeactivated() {}

	//함수
	void updateInput(const float dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget* target);

	void update();
	void render(sf::RenderTarget* target = NULL);
};
