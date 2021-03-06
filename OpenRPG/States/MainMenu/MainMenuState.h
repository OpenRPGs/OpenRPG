﻿#pragma once

#include "GUI/Gui.h"

class MainMenuState : public State {
private:
	//변수
	bool fadeOutFlag;
	float backGroundColor;
	sf::Texture backgroundTexture;
	sf::Texture btnTexure;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	//함수
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(StateData* state_Data);
	virtual ~MainMenuState();

	//함수

	void updateInput(const float& dt);
	void updateButtons();
	void updateFadeout(const float dt);
	void updateFadeIn(const float dt);
	void update();
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	void onActivated();
	void onDeactivated();
	void onEnter() {}
	void onLeave() {}
};
