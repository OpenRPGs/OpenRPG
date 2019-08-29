#include "stdafx.h"
#include "Game.h"
#include "States/State.h"
#include "States/MainMenu/MainMenuState.h"

#include "Managers/StateManager.h"
#include "Managers/SoundManager.h"

#pragma region getInstance, Constructor, Finalizer
Game* Game::Instance = NULL;

Game* Game::getInstance() {
	if (Game::Instance == NULL) {
		Game::Instance = new Game();
	}
	return Game::Instance;
}

//생성 및 소멸함수
Game::Game() {
	this->initVariables();
	this->initGraphicsSettings();
	// TODO: 이후 initConfiguration 등으로 분리
	this->setFramerate(120);
}

Game::~Game() {
	this->Dispose();
}

void Game::Dispose() {
	if (this->disposed)
		throw "ERROR::Game::Already Disposed";

	this->window.reset();

	StateManager::getInstance()->Dispose();
	SoundManager::getInstance()->Dispose();

	this->disposed = true;
}
#pragma endregion

#pragma region Initializers
void Game::initVariables() {
	this->gridSize = 100.f;
}

void Game::initWindow() {
	if (this->gfxSettings.fullscreen)
		this->window = g::safe<sf::RenderWindow>(new sf::RenderWindow(
			this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen,
			this->gfxSettings.contextSettings));
	else
		this->window = g::safe<sf::RenderWindow>(new sf::RenderWindow(
			this->gfxSettings.resolution, this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings));

	this->setFramerate(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys() {
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
			this->supportedKeys[key] = key_value;
	}
	ifs.close();

	this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
	this->supportedKeys["A"] = sf::Keyboard::Key::A;
	this->supportedKeys["D"] = sf::Keyboard::Key::D;
	this->supportedKeys["W"] = sf::Keyboard::Key::W;
	this->supportedKeys["S"] = sf::Keyboard::Key::S;

	//확인용 삭제예정코드
	for (auto i : this->supportedKeys)
		std::cout << i.first << " " << i.second << std::endl;
}

void Game::initGraphicsSettings() {
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}
#pragma endregion

#pragma region Framerate, deltaTime
void Game::setFramerate(int frameRate) {
	if (this->disposed)
		throw "ERROR::Game::Already Disposed";

	this->frameRate = frameRate;
	if (this->window != NULL)
		this->window->setFramerateLimit(this->frameRate);
}
int Game::getFramerate() {
	if (this->disposed)
		throw "ERROR::Game::Already Disposed";

	return this->frameRate;
}

float Game::deltaTime() {
	//  60 frame = 0.016666...
	// 120 frame = 0.008333...
	return 1.f / this->frameRate;
}
#pragma endregion

#pragma region Getters
g::safe<sf::RenderWindow> Game::getWindow() {
	auto obj = Game::getInstance();
	if (obj->disposed)
		throw "ERROR::Game::Already Disposed";

	return obj->window;
}

g::map<int>* Game::getSupportedKeys() {
	auto obj = Game::getInstance();
	if (obj->disposed)
		throw "ERROR::Game::Already Disposed";

	return &obj->supportedKeys;
}

bool Game::getFocused() {
	auto obj = Game::getInstance();
	if (obj->disposed)
		throw "ERROR::Game::Already Disposed";

	return obj->window->hasFocus();
}

float Game::getGridSize() {
	auto obj = Game::getInstance();
	if (obj->disposed)
		throw "ERROR::Game::Already Disposed";

	return obj->gridSize;
}

GraphicsSettings* Game::getGraphicsSettings() {
	auto obj = Game::getInstance();
	if (obj->disposed)
		throw "ERROR::Game::Already Disposed";

	return &obj->gfxSettings;
}
#pragma endregion

void Game::endApplication() {
	std::cout << "Shutdown" << std::endl;
}

void Game::updateSFMLEvents() {
	// 남아있는 이벤트 전부 처리
	while (this->window->pollEvent(this->sfEvent)) {
		// 종료 이벤트가 발생
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update() {
	if (this->disposed)
		throw "ERROR::Game::Already Disposed";

	// SFML 창의 이벤트들을 처리
	this->updateSFMLEvents();

	auto stateManager = StateManager::getInstance();

	// 남아있는 장면이 없다면 프로그램 종료
	if (stateManager->Empty()) {
		this->endApplication();
		this->window->close();
		return;
	}

	// 이전 그리기 결과물을 제거
	this->window->clear();

	// 갱신 및 그리기 작업
	stateManager->Update();

	// 그린 결과물을 화면에 표시
	this->window->display();
}

Game* Game::boot() {
	if (this->disposed)
		throw "ERROR::Game::Already Disposed";

	this->initWindow();
	this->initKeys();

	StateManager::getInstance()->Push(SafeState(MainMenuState));
	return this;
}

Game* Game::run() {
	if (this->disposed)
		throw "ERROR::Game::Already Disposed";

	while (this->window->isOpen())
		this->update();

	return this;
}
