#pragma once

#include "Defines/IDisposable.h"
#include "States/State.h"

#include "Graphics.h"
#include "GraphicsSettings.h"

class Game : public IDisposable {
  private:
	// private생성자 소멸자
	Game();
	virtual ~Game();

	//변수
	GraphicsSettings gfxSettings;
	static Game* Instance;

	g::safe<sf::RenderWindow> window;
	g::safe<Graphics> graphics;
	sf::Event sfEvent;

	float gridSize;

	g::map<int> supportedKeys;
	int frameRate;

	//초기화
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();

	void updateSFMLEvents();

  public:
	static Game* getInstance();
	void Dispose();

	// Regular
	void endApplication();
	float deltaTime();

	// Update
	void update();

	// Framerate
	void setFramerate(int frameRate);
	int getFramerate();

	void setupWindow();

	static g::safe<sf::RenderWindow> getWindow();
	static g::map<int>* getSupportedKeys();
	static bool getFocused();
	static float getGridSize();
	static GraphicsSettings* getGraphicsSettings();
	static g::safe< Graphics> Graphics();

	// Core
	Game* boot();
	Game* run();
};
