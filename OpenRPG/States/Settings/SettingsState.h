#pragma once

#include "States/State.h"
#include "GUI/Gui.h"

class SettingsState : public State {
private:
	GraphicsSettings& gfxSettings;
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
	SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys);
	virtual ~SettingsState();

	//접근자

	//업데이트함수
	void updateInput(const float& dt);
	void updateGui();
	void update();

	//랜더함수
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated() {}
	void onDeactivated() {}
	void onEnter() {}
	void onLeave() {}
};
