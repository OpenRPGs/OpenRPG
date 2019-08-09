#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

class Game
{
private:
	//변수
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	//초기화
	void initWindow();

public:
	//생성자 및 소멸자
	Game();
	virtual ~Game();

	//함수
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};
#endif

