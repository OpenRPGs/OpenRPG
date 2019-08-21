#pragma once

#include "States/State.h"
#include "GUI/Gui.h"

class EditorState : public State {
  private:
	//변수
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;
	sf::Texture tx;

	//초기화함수
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initBackground();

  public:
	const StateFlow flow() {
		// 흐를 수 없음
		return StateFlow::FLOW_NONE;
	}

	EditorState() : State() {}

	//업데이트함수
	void updateInput(const float& dt);
	void updateButtons();
	void update();
	void renderButtons(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);

	// State 이벤트
	virtual void onEnter();
	virtual void onActivated() {}
	virtual void onDeactivated() {}
	virtual void onLeave();
};
