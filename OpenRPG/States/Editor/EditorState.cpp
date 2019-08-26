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
void EditorState::initVariables() {
	auto gridSize = Game::getGridSize();
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(gridSize), static_cast<int>(gridSize));
}

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
		250, 80, 1250, 80, tx, this->font, L"(에디터) 맵수정, 캐릭터배치 등등 ", 50,
		g::Color("#000"), g::Color("#969696fa"), g::Color("#14141432"), g::Color("#fff"),
		g::Color("#fff"), g::Color("#fff")));
}

void EditorState::initText() {
	this->cursorText.setFont(*this->font);
	this->cursorText.setCharacterSize(15);
	this->cursorText.setFillColor(sf::Color::Red);
	this->cursorText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 30));
}

void EditorState::initBackground() {}
#pragma endregion

void EditorState::initGui() {
	auto gridSize = Game::getGridSize();

	this->selectorRect.setSize(sf::Vector2f(gridSize, gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet().get());
	this->selectorRect.setTextureRect(this->textureRect);
}

void EditorState::initTileMap() {
	this->tileMap = g::safe<TileMap>(new TileMap(Game::getGridSize(), 10, 10));
}

EditorState::EditorState(State *parent) : State(parent) {
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}
EditorState::~EditorState() {}

void EditorState::updateInput(const float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}
void EditorState::updateEditorInput(const float dt) {
	//타일 맵 추가하기
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime()) {
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->getKeytime()) {
		if (this->textureRect.left < 300)
			this->textureRect.left += 100;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->getKeytime()) {
		if (this->textureRect.left > 0)
			this->textureRect.left -= 100;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->getKeytime()) {
		if (this->textureRect.top < 200)
			this->textureRect.top += 100;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->getKeytime()) {
		if (this->textureRect.top > 0)
			this->textureRect.top -= 100;
	}
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
	auto gridSize = Game::getGridSize();

	this->selectorRect.setTextureRect(this->textureRect);
	this->selectorRect.setPosition(
		this->mousePosGrid.x * gridSize, this->mousePosGrid.y * gridSize);

	this->cursorText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 30));
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << '\n'
	   << this->textureRect.left << " " << this->textureRect.top;
	cursorText.setString(ss.str());
}
void EditorState::update() {
	State::update();

	auto dt = Game::getInstance()->deltaTime();

	this->updateGui();
	this->updateEditorInput(dt);

	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	this->updateButtons();
}

void EditorState::renderGui(sf::RenderTexture *target) {
	target->draw(this->selectorRect);
	target->draw(this->cursorText);
}
void EditorState::renderButtons(sf::RenderTexture *target) {
	for (auto &it : this->buttons)
		it.second->render(target);
}
void EditorState::render(sf::RenderTexture *target) {
	State::render(target);

	this->tileMap->render(target);

	this->renderButtons(target);
	this->renderGui(target);
}
