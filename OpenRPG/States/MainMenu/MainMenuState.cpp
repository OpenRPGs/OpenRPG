﻿#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "Components/SoundComponent.h"
#include "States/State.h"
#include "States/MainMenu/MainMenuState.h"
#include "States/Game/GameState.h"
#include "States/Editor/EditorState.h"
#include "States/Settings/SettingsState.h"

#include "Managers/SoundManager.h"
#include "Managers/StateManager.h"

#pragma region Initializers
void MainMenuState::initVariables() {}

void MainMenuState::initBackground() {
	auto window = Game::getWindow();

	this->backgroundTexture = g::safe<sf::Texture>(new sf::Texture());
	if (this->backgroundTexture == NULL ||
		!this->backgroundTexture->loadFromFile("Resources/image/Backgrounds/bg3.png"))
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(this->backgroundTexture.get());
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
}

void MainMenuState::initFonts() {
	this->font = g::safe<sf::Font>(new sf::Font());
	if (!this->font->loadFromFile("Fonts/R2.ttc"))
		throw "메인메뉴 폰트로딩 실패";
}

void MainMenuState::initKeybinds() {
	auto supportedKeys = Game::getInstance()->getSupportedKeys();

	std::ifstream ifs("Config/mainmenuestate_keybinds.ini");
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

void MainMenuState::initButtons() {
	this->btnTexture = g::safe<sf::Texture>(new sf::Texture());
	if (!btnTexture->loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->buttons["GAME_STATE"] = g::safe<gui::Button>(new gui::Button(
		1500, 500, 250, 80, this->btnTexture, this->font, L"새 게임", 40, g::Color("#000"),
		g::Color("#969696fa"), g::Color("#14141432"), g::Color("#fff"), g::Color("#fff"),
		g::Color("#fff")));

	this->buttons["SETTING_STATE"] = g::safe<gui::Button>(new gui::Button(
		1500, 600, 250, 80, this->btnTexture, this->font, L"게임 설정", 40, g::Color("#000"),
		g::Color("#969696fa"), g::Color("#14141432"), g::Color("#fff"), g::Color("#fff"),
		g::Color("#fff")));

	this->buttons["EDITOR_STATE"] = g::safe<gui::Button>(new gui::Button(
		1500, 700, 250, 80, this->btnTexture, this->font, L"에디터", 40, g::Color("#000"),
		g::Color("#969696fa"), g::Color("#14141432"), g::Color("#fff"), g::Color("#fff"),
		g::Color("#fff")));

	this->buttons["EXIT_STATE"] = g::safe<gui::Button>(new gui::Button(
		1500, 900, 250, 80, this->btnTexture, this->font, L"종 료", 40, g::Color("#000"),
		g::Color("#969696fa"), g::Color("#14141432"), g::Color("#fff"), g::Color("#fff"),
		g::Color("#fff")));
}

void MainMenuState::initSounds() {
	auto sound = this->res.Sounds["BACKGROUND_MUSIC"] = g::safe<sf::SoundBuffer>(new sf::SoundBuffer());
	if (!sound->loadFromFile("Resources/sound/bgm.wav"))
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BGM";
}
#pragma endregion

MainMenuState::MainMenuState() : State() {
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initSounds();

	// 메인 화면이 생성될 때 BGM 재생
	auto sm = SoundManager::getInstance();
	sm->LoadBGM(this->res.Sounds["BACKGROUND_MUSIC"]);
	sm->getBGM()->setLoop(true)->play();
}

MainMenuState::~MainMenuState() {
	// 메인 화면이 제거될 때 BGM 중지
	SoundManager::getInstance()->getBGM()->stop();
}

void MainMenuState::updateInput(const float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		this->background.setFillColor(sf::Color::Cyan);
}

void MainMenuState::updateButtons() {
	//모든 버튼들의 상태를 기능에맞게 업데이트해줌
	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	//게임시작
	if (this->buttons["GAME_STATE"]->isPressed()) {
		StateManager::getInstance()->GoTo(SafeState(GameState));
		return;
	}

	//설정
	if (this->buttons["SETTING_STATE"]->isPressed()) {
		StateManager::getInstance()->GoTo(SafeState(SettingsState));
		return;
	}

	//에디터
	if (this->buttons["EDITOR_STATE"]->isPressed()) {
		StateManager::getInstance()->GoTo(SafeState(EditorState, this));
		return;
	}

	//종료
	if (this->buttons["EXIT_STATE"]->isPressed()) {
		this->endState();
		return;
	}
}

void MainMenuState::update() {
	State::update();

	auto dt = Game::getInstance()->deltaTime();

	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target) {
	State::render(target);

	if (!target)
		target = Game::getWindow().get();

	target->draw(this->background);
	this->renderButtons(target);

	//삭제예정. 디버깅용.
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 15));
	mouseText.setFont(*this->font);
	mouseText.setCharacterSize(15);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}

void MainMenuState::renderButtons(sf::RenderTarget* target) {
	for (auto& it : this->buttons)
		it.second->render(target);
}
