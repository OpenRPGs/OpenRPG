#pragma once

class State {
  private:
  protected:
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool paused;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> sounds;

	//함수
	virtual void initKeybinds() = 0;
	void initSounds();

  public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();

	void endState();
	void pauseState();
	void unpauseState();

	/// <summary>장면이 화면의 최상단에 위치할 때 호출됩니다.</summary>
	virtual void onActivated();
	/// <summary>장면이 화면의 최상단에 위치하지 않게될 때 호출됩니다.</summary>
	virtual void onDeactivated();
	/// <summary>장면이 화면 스택에 진입한 후에 호출됩니다.</summary>
	virtual void onEnter();
	/// <summary>장면이 화면 스택에서 제거된 후에 호출됩니다.</summary>
	virtual void onLeave();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateKeytime(const float& dt);
	virtual void updateMousePositions();
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
