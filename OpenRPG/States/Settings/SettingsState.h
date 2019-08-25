#pragma once

#include "States/State.h"
#include "GUI/Gui.h"

class SettingsState : public State {
  private:
	g::safe<sf::Texture> backgroundTexture;
	g::safe<sf::Texture> btnTexturee;
	sf::RectangleShape background;

	g::safe<sf::Font> font;
	g::safe<sf::Texture> tx;

	g::safemap<gui::Button> buttons;
	g::safemap<gui::DropDownList> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	//초기화 함수
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGui();
	void initText();
	// void initMusic();

  public:
	const StateFlow flow() {
		// 흐를 수 없음
		return StateFlow::FLOW_NONE;
	}

	SettingsState();
	~SettingsState();

	//접근자

	//업데이트함수
	void updateInput(const float dt);
	void updateGui();
	void update();

	//랜더함수
	void renderGui(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
};
