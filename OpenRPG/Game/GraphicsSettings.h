#pragma once

class GraphicsSettings {
  public:
	GraphicsSettings();

	//변수
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	//함수
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
