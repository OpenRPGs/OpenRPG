#pragma once

#include "States/State.h"
#include "Managers/StateManager.h"

class Game {
private:
	class GraphicsSettings
	{
	public:
		GraphicsSettings()
		{
			this->title = "Default";
			this->resolution = sf::VideoMode::getDesktopMode();
			this->fullscreen = false;
			this->verticalSync = false;
			this->frameRateLimit = 120;
			this->contextSettings.antialiasingLevel = 0;
			this->videoModes = sf::VideoMode::getFullscreenModes();
		}

		//변수
		std::string title;
		sf::VideoMode resolution;
		bool fullscreen;
		bool verticalSync;
		unsigned frameRateLimit;
		sf::ContextSettings contextSettings;
		std::vector<sf::VideoMode> videoModes;

		//함수
		void saveToFile(const std::string path)
		{
			std::ofstream ofs(path);

			if (ofs.is_open()) {
				ofs << this->title;
				ofs << this->resolution.width << this->resolution.height;
				ofs << this->fullscreen;
				ofs << this->frameRateLimit;
				ofs << this->verticalSync;
				ofs << this->contextSettings.antialiasingLevel;
			}
			ofs.close();
		}
		void loadFromFile(const std::string path)
		{
			std::ifstream ifs(path);

			if (ifs.is_open()) {
				std::getline(ifs, this->title);
				ifs >> this->resolution.width >> this->resolution.height;
				ifs >> this->fullscreen;
				ifs >> this->frameRateLimit;
				ifs >> this->verticalSync;
				ifs >> this->contextSettings.antialiasingLevel;
			}
			ifs.close();
		}
	};

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
