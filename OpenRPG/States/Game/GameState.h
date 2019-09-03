#pragma once

#include "Entities/Player.h"
#include "GUI/PauseMenu.h"

#include "../../Maps/TileMap.h"
#include "../../PlayerGUI.h"

class GameState :
	public State
{
private:
	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	sf::Shader core_shader;

	Player* player;
	PlayerGUI* playerGUI;
	sf::Texture texture;

	std::vector<Enemy*> activeEnemies;
	EnemySystem *enemySystem;

	TileMap* tileMap;

	//Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initPlayerGUI();
	void initEnemySystem();
	void initTileMap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void updatePlayer(const float& dt);
	void updateEnemies(const float& dt);
	void update();
	void render(sf::RenderTarget* target = NULL);
	void onActivated() {};
	void onDeactivated() {};
	void onEnter() {}
	void onLeave() {}
};