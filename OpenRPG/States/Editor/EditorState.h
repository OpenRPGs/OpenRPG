#pragma once

#include "States/State.h"
#include "GUI/Gui.h"
#include "Maps/TileMap.h"

class EditorState : public State {
  private:
	//변수
	sf::Font font;
	sf::Text cursorText;
	std::map<std::string, gui::Button*> buttons;
	sf::Texture tx;
	PauseMenu* pmenu;

	g::safe<TileMap> tileMap;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	//초기화함수
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initText();
	void initBackground();
	void initGui();
	void initTileMap();

  public:
	const StateFlow flow() {
		// 흐를 수 없음
		return StateFlow::FLOW_NONE;
	}

	EditorState(State* parent);
	~EditorState();
	virtual void onActivated() {}
	virtual void onDeactivated() {}

	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui();
	void update();

	//랜더함수
	void renderButtons(sf::RenderTarget* target);
	void renderGui(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};
