#pragma once

#include "GUI/Gui.h"
#include "GUI/PauseMenu.h"
#include "../../Maps/TileMap.h"

class EditorState : public State {
  private:
	//변수
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;
	sf::Texture tx;
	PauseMenu* pmenu;

	TileMap map;

	//초기화함수
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initBackground();
	void initPauseMenu();

  public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//업데이트함수
	void updateInput(const float& dt);
	void updateButtons();
	void updatePauseMenuButtons();
	void update();
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	virtual void onActivated() {}
	virtual void onDeactivated() {}
	virtual void onEnter() {}
	virtual void onLeave() {}
};
