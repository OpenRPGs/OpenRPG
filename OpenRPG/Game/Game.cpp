#include "stdafx.h"
#include "Game.h"
#include "States/State.h"
#include "States/MainMenu/MainMenuState.h"

// 전역함수

// 초기화 함수

void Game::initVariables() {
	this->window = NULL;
	this->fullscreen = 0;
	this->StateManager = StateManager::getInstance();
}

void Game::initWindow() {
	// SFML 윈도우창 생성 Todo : window.ini파일로 초기화할예정(완료)
	std::ifstream ifs("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	bool vertical_sync_enable = false;
	unsigned antialiasing_level = 0;

	int frameRate = this->getFramerate();

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> frameRate;
		ifs >> vertical_sync_enable;
		ifs >> antialiasing_level;
	}
	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	// 프레임 레이트를 재설정
	// 설정 파일에서 불러온 프레임 레이트 값이 다르다면 재설정을 해야하고,
	// this->window가 할당되었으니 알아서 setFramerateLimit을 호출할 것
	this->setFramerate(frameRate);
	this->window->setVerticalSyncEnabled(vertical_sync_enable);
}

void Game::initKeys() {
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value) {
			this->supportedKeys[key] = key_value;
		}
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

void Game::initState() {
	this->StateManager->Push(new MainMenuState(this->window, &this->supportedKeys));
}

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

	// TODO: 이후 initConfiguration 등으로 분리
	this->setFramerate(120);

	this->initWindow();
	this->initKeys();
	this->initState();
}

Game::~Game() {
	delete this->window;
	this->StateManager->Clear();
}
#pragma endregion

#pragma region Framerate
void Game::setFramerate(int frameRate) {
	this->frameRate = frameRate;
	if (this->window != NULL)
		this->window->setFramerateLimit(this->frameRate);
}
int Game::getFramerate() {
	return this->frameRate;
}

float Game::frameTime() {
	//  60 frame = 0.016666...
	// 120 frame = 0.008333...
	return 1.f / this->frameRate;
}
#pragma endregion

//함수
void Game::endApplication() {
	std::cout << "Ending Application" << std::endl;
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
	// SFML 창의 이벤트들을 처리
	this->updateSFMLEvents();

	// 남아있는 장면이 없다면 프로그램 종료
	if (this->StateManager->Empty()) {
		this->endApplication();
		this->window->close();
		return;
	}

	// 이전 그리기 결과물을 제거
	this->window->clear();

	// 갱신 및 그리기 작업
	this->StateManager->Update();

	// 그린 결과물을 화면에 표시
	this->window->display();
}

void Game::run() {
	while (this->window->isOpen()) {
		this->update();
	}
}
