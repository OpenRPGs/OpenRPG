#pragma once

#include "States/State.h"
#include "Managers/StateManager.h"
#include "../GraphicsSettings.h"
class Game {
private:
	
	//private생성자 소멸자
	Game();
	virtual ~Game();

	//변수
	GraphicsSettings gfxSettings;
	StateData stateData;
	static Game* Instance;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	StateManager* StateManager;

	float gridSize;

	std::map<std::string, int> supportedKeys;
	int frameRate;

	//초기화
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initState();

public:
	static Game* getInstance();

	// Regular
	void endApplication();
	float deltaTime();

	// Update
	void updateSFMLEvents();
	void update();

	// Update + Render
	void setFramerate(int frameRate);
	int getFramerate();



	// Core
	void run();
};
