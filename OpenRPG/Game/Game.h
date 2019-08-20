#pragma once

#include "States/State.h"
#include "Managers/StateManager.h"

class Game {
  private:
	/// <summary>
	/// 싱글톤 인스턴스입니다.
	/// 프로세스 내에 한번만 할당되는 것이 보장됩니다.
	/// </summary>
	static Game* Instance;

	/// <summary>
	/// 생성자와 소멸자입니다. private로 지정하여 일반적인 할당을 금지합니다.
	/// </summary>
	Game();
	virtual ~Game();

	/// <summary>프로그램 화면을 가리키는 객체입니다.</summary>
	sf::RenderWindow* window;

	/// <summary>프로그램 화면에서 발생한 이벤트를 전달하는 객체입니다.</summary>
	sf::Event sfEvent;

	/// <summary>프로그램 화면의 크기를 담은 객체입니다.</summary>
	std::vector<sf::VideoMode> videoModes;

	/// <summary>프로그램 화면을 나타낼 때 사용되는 설정들을 담은 객체입니다.</summary>
	sf::ContextSettings windowSettings;

	/// <summary>최대화 화면으로 나타낼지 여부입니다.</summary>
	bool fullscreen;

	/// <summary>장면 관리자입니다.</summary>
	StateManager* StateManager;

	/// <summary>사용 가능한 키들을 관리하는 맵입니다.</summary>
	std::map<std::string, int> supportedKeys;

	/// <summary>현재 게임이 작동하는 프레임 레이트입니다.</summary>
	int frameRate;

	//초기화
	void initVariables();
	void initWindow();
	void initKeys();
	void initState();

  public:
	/// <summary>
	/// 싱글톤 인스턴스를 가져옵니다.
	/// 기존에 인스턴스가 없었다면 새로 생성합니다.
	/// </summary>
	/// <returns><see cref="Game"/>의 싱글톤 객체입니다.</returns>
	static Game* getInstance();

	// Regular
	void endApplication();

	// Update
	void updateSFMLEvents();

	// Update + Render
	void update();

	/// <summary>현재 게임이 작동하고 있는 프레임 레이트를 설정합니다.</summary>
	/// <param name="frameRate">설정할 프레임 레이트입니다. 1 이상의 값이어야 합니다.</param>
	void setFramerate(int frameRate);

	/// <summary>현재 게임이 작동하고 있는 프레임 레이트를 가져옵니다.</summary>
	int getFramerate();

	/// <summary>프레임 레이트에 기반한 프레임당 소요 시간입니다.</summary>
	float frameTime();

	// Core
	void run();
};
