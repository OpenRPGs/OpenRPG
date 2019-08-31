﻿#pragma once

#include "GUI/Gui.h"
#include "GUI/PauseMenu.h"
#include "../../Maps/TileMap.h"

class EditorState : public State {
  private:
	//변수
	sf::Font font;
	sf::Text cursorText;
	std::map<std::string, gui::Button*> buttons;
	sf::Texture tx;
	PauseMenu* pmenu;

	sf::View mainView;
	float cameraSpeed;

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	bool collision;
	short type;

	//초기화함수
	void initVariables();
	void initView();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initText();
	void initBackground();
	void initPauseMenu();
	void initGui();
	void initTileMap();

  public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//업데이트함수
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui();
	void updatePauseMenuButtons();
	void update();

	//랜더함수
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	virtual void onActivated() {}
	virtual void onDeactivated() {}
	virtual void onEnter() {}
	virtual void onLeave() {}
};
