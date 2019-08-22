#pragma once

#include "States/State.h"
#include "GUI/Gui.h"
#include "Maps/TileMap.h"

class EditorState : public State {
  private:
	g::safe<sf::Font> font;
	g::safe<sf::Texture> tx;
	g::safemap<gui::Button> buttons;

	g::safe<TileMap> tileMap;

	sf::RectangleShape selectorRect;

	//초기화함수
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
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

	//업데이트함수
	void updateInput(const float dt);
	void updateButtons();
	void updateGui();
	void update();

	//랜더함수
	void renderButtons(sf::RenderTarget* target);
	void renderGui(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};
