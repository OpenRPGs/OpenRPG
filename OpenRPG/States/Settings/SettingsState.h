#pragma once

#include "States/State.h"
#include "GUI/Gui.h"

class SettingsState : public State {
  private:
	sf::Texture backgroundTexture;
	sf::Texture btnTexure;
	sf::RectangleShape background;
	sf::Font font;
	sf::Texture tx;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownLists;

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
	void updateInput(const float& dt);
	void updateGui();
	void update();

	//랜더함수
	void renderGui(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
};
