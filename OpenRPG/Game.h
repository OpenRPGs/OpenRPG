#pragma once
#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "MainMenuState.h"

class Game
{
private:
	//����
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states; // ����state, ���θ޴�state ���..

	std::map<std::string, int> supportedKeys;

	//�ʱ�ȭ
	void initVariables();
	void initWindow();
	void initKeys();
	void initState();
public:
	//������ �� �Ҹ���
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

