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

	//임시 테스트용 드랍다운메뉴
	gui::DropDownList* ddl;

	std::map<std::string, gui::Button*> buttons;

	//초기화 함수
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();
	// void initMusic();

  public:
	SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~SettingsState();

	//접근자

	//업데이트함수
	void updateInput(const float& dt);
	void updateButtons();
	void update();

	//랜더함수
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
	void onEnter() {}
	void onLeave() {}
};
