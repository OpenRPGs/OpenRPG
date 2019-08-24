#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "States/State.h"
#include "Managers/StateManager.h"

#include "EditorState.h"
#include "States/Game/PauseMenu/PauseMenuState.h"
#include "States/MainMenu/MainMenuState.h"

// Initaillizer functions
#pragma region Initializers
void EditorState::initVariables() {}

void EditorState::initFonts() {
	this->font = g::safe<sf::Font>(new sf::Font());
	if (!this->font->loadFromFile("Fonts/R2.ttc")) {
		throw "메인메뉴 폰트로딩 실패";
	}
}

void EditorState::initKeybinds() {
	auto supportedKeys = Game::getInstance()->getSupportedKeys();

	std::ifstream ifs("Config/editor_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = supportedKeys->at(key2);
	}
	ifs.close();
}

void EditorState::initButtons() {
	this->tx = g::safe<sf::Texture>(new sf::Texture());
	if (!this->tx->loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "btn";

	this->buttons["EXIT_STATE"] = g::safe<gui::Button>(new gui::Button(
		250, 100, 1250, 80, tx, this->font, L"(에디터) 맵수정, 캐릭터배치 등등 ", 50,
		g::Color("#000"), g::Color("#969696fa"), g::Color("#14141432"), g::Color("#fff"),
		g::Color("#fff"), g::Color("#fff")));
}

void EditorState::initBackground() {}
#pragma endregion

void EditorState::initGui() {
	this->selectorRect.setSize(sf::Vector2f(Game::getGridSize(), Game::getGridSize()));

	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initTileMap() {
	this->tileMap = g::safe<TileMap>(new TileMap(Game::getGridSize(), 10, 10));
}

EditorState::EditorState(State *parent) : State(parent) {
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initGui();
	this->initTileMap();
}
EditorState::~EditorState() {}

void EditorState::updateInput(const float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons() {
	//모든 버튼들의 상태를 기능에맞게 업데이트해줌
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressed()) {
		StateManager::getInstance()->GoTo(SafeState(MainMenuState));
		return;
	}
}

void EditorState::updateGui() {
	this->selectorRect.setPosition(this->mousePosView);
}

void EditorState::update() {
	State::update();

	auto dt = Game::getInstance()->deltaTime();

	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	this->updateButtons();
}

void EditorState::renderGui(sf::RenderTarget *target) {
	target->draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget *target) {
	State::render(target);

	if (!target)
		target = Game::getWindow().get();
	this->tileMap->render(target);

	this->renderButtons(target);
	this->renderGui(target);

	//삭제예정. 디버깅용.
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 15));
	mouseText.setFont(*this->font);
	mouseText.setCharacterSize(15);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	this->renderButtons(target);
	target->draw(mouseText);
}

void EditorState::renderButtons(sf::RenderTarget *target) {
	for (auto &it : this->buttons)
		it.second->render(target);
}
