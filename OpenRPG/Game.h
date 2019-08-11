#pragma once
#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "MainMenuState.h"

class Game
{
private:
	//변수
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states; // 게임state, 메인메뉴state 등등..

	std::map<std::string, int> supportedKeys;

	//초기화
	void initVariables();
	void initWindow();
	void initKeys();
	void initState();
public:
	//생성자 및 소멸자
	Game();
	virtual ~Game();

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};
#endif

