﻿#pragma once

#include "../GraphicsSettings.h"


class Player;
class GraphicsSettings;
class State;


class StateData
{
public:
	StateData() {};

	//Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	//std::stack<State*> * states;
};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::SoundBuffer> sounds;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();
	static void destroy();
	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions	
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeytime(const float& dt);
	void initSounds();
	virtual void updateInput(const float& dt) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

	/// <summary>장면이 화면의 최상단에 위치할 때 호출됩니다.</summary>
	virtual void onActivated() = 0;
	/// <summary>장면이 화면의 최상단에 위치하지 않게될 때 호출됩니다.</summary>
	virtual void onDeactivated() = 0;
	/// <summary>장면이 화면 스택에 진입한 후에 호출됩니다.</summary>
	virtual void onEnter() = 0;
	/// <summary>장면이 화면 스택에서 제거된 후에 호출됩니다.</summary>
	virtual void onLeave() = 0;
};
