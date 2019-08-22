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
	static Game* Instance;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	StateManager* StateManager;

	std::map<std::string, int> supportedKeys;
	int frameRate;

	//초기화
	void initVariables();
	void initWindow();
	void initKeys();
	void initState();
	void initGraphicsSettings();

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
