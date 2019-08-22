#pragma once

/// <summary><c>State</c>의 <c>update</c> 또는 <c>render</c>가 아래 장면으로 흐를 수 있는지를
/// 결정하는 값입니다.</summary>
enum StateFlow : int {
	/// <summary>흐를 수 없습니다.</summary>
	FLOW_NONE = 0x00,

	/// <summary><c>update</c> 메서드 호출은 흐를 수 있습니다.</summary>
	FLOW_UPDATE = 0x01,

	/// <summary><c>render</c> 메서드 호출은 흐를 수 있습니다.</summary>
	FLOW_RENDER = 0x02,

	/// <summary><c>update</c> 메서드 호출과 <c>render</c> 메서드 호출 모두 흐를 수
	/// 있습니다.</summary>
	FLOW_ALL = FLOW_UPDATE | FLOW_RENDER
};

class State {
  public:
	/// <summary><c>update</c> 또는 <c>render</c>의 흐름 여부를 반환합니다.</summary>
	virtual const StateFlow flow() = 0;

	State();
	~State();

	/// <summary>장면이 화면의 최상단에 위치할 때 호출됩니다.</summary>
	virtual void onActivated() = 0;
	/// <summary>장면이 화면의 최상단에 위치하지 않게될 때 호출됩니다.</summary>
	virtual void onDeactivated() = 0;

	const bool getKeytime();

	void endState();

	virtual void updateInput(const float& dt) = 0;
	virtual void updateKeytime(const float& dt);
	virtual void updateMousePositions();

	virtual void update();
	virtual void render(sf::RenderTarget* target = NULL);

  protected:
	std::map<std::string, int> keybinds;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, sf::SoundBuffer*> sounds;

	//함수
	virtual void initKeybinds() = 0;

  private:
};
