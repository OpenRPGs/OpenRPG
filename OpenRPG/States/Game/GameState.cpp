#include "stdafx.h"

#include "Game/Game.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "GUI/Gui.h"

#include "States/State.h"
#include "GameState.h"
#include "PauseMenu/PauseMenuState.h"

#pragma region Initializers
void GameState::initButtons() {
	if (!btnTexure.loadFromFile("Resources/image/Buttons/btn1.png")) {
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
}

void GameState::initKeybinds() {
	auto supportedKeys = Game::getInstance()->getSupportedKeys();

	std::ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		int key_value = 0;
		while (ifs >> key >> key2) {
			this->keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();

	this->keybinds["CLOSE"] = supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = supportedKeys->at("S");
}

void GameState::initTextures() {
	auto texture = this->textures["PLAYER_SHEET"] = new sf::Texture();
	if (texture == NULL ||
		!texture->loadFromFile("Resources/image/Sprites/Player/PLAYER_SHEET.png"))
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("Fonts/R2.ttc")) {
		throw "메인메뉴 폰트로딩 실패";
	}
}

void GameState::initPlayers() {
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}
#pragma endregion

void GameState::onEnter() {
	this->initButtons();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPlayers();
}

void GameState::onLeave() {
	delete this->player;
}

void GameState::updateInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) &&
		this->getKeytime()) {

		StateManager::getInstance()->Push(new PauseMenuState(this));
	}
}

// Update functions

void GameState::updatePauseButtons() {}

void GameState::updatePlayerInput(const float& dt) {
	auto window = Game::getInstance()->getWindow();
	if (window->hasFocus()) {
		//사용자 입력 업데이트
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
			this->player->move(-2.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
			this->player->move(2.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
			this->player->move(0.f, -2.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
			this->player->move(0.f, 2.f, dt);
	}
}

void GameState::update() {
	State::update();

	auto dt = Game::getInstance()->frameTime();
	if (Game::getInstance()->getFocused()) {
		this->updateInput(dt);
		this->updatePlayerInput(dt);
		this->player->update(dt);
	}
}

void GameState::render(sf::RenderTarget* target) {
	State::render(target);

	if (!target)
		target = Game::getInstance()->getWindow();

	this->player->render(*target);
}
