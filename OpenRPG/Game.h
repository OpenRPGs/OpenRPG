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
	//����
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	//�ʱ�ȭ
	void initWindow();

public:
	//������ �� �Ҹ���
	Game();
	virtual ~Game();

	//�Լ�
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};
#endif

