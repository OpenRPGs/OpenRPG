#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "States/State.h"
#include "EditorState.h"
#include "States/MainMenu/MainMenuState.h"

// Initaillizer functions
#pragma region Initializers
void EditorState::initVariables() {}

void EditorState::initFonts() {
	if (!this->font.loadFromFile("Fonts/R2.ttc")) {
		throw("메인메뉴 폰트로딩 실패");
	}
}

void EditorState::initKeybinds() {
	auto supportedKeys = Game::getInstance()->getSupportedKeys();

	std::ifstream ifs("Config/editor_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		int key_value = 0;
		while (ifs >> key >> key2) {
			this->keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void EditorState::initButtons() {
	if (!tx.loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "btn";

	this->buttons["EXIT_STATE"] = new gui::Button(
		250, 100, 1250, 270, &tx, &this->font, L"(에디터) 맵수정, 캐릭터배치 등등 ", 50,
		sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255));
}

void EditorState::initBackground() {}
#pragma endregion

void EditorState::onEnter() {
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

void EditorState::onLeave() {
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void EditorState::updateInput(const float &dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons() {
	//모든 버튼들의 상태를 기능에맞게 업데이트해줌
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressed()) {
		StateManager::getInstance()->GoTo(new MainMenuState(), [](State *state) { delete state; });
		return;
	}
}

void EditorState::update() {
	State::update();

	auto dt = Game::getInstance()->frameTime();

	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void EditorState::render(sf::RenderTarget *target) {
	State::render(target);

	if (!target)
		target = Game::getInstance()->getWindow();

	//삭제예정. 디버깅용.
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 15));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(15);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	this->renderButtons(target);
	target->draw(mouseText);
}

void EditorState::renderButtons(sf::RenderTarget *target) {
	for (auto &it : this->buttons) {
		it.second->render(target);
	}
}
