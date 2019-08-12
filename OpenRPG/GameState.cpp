#include "GameState.h"

//Initializer functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		int key_value = 0;
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();

	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/image/Sprites/Player/test.gif"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, &this->textures["PLAYER_IDLE"]);
}

//Constructors / Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
}


//Update functions
void GameState::updateInput(const float & dt)
{

	//사용자 입력 업데이트
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(dt, -2.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(dt, 2.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(dt, 0.f, -2.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(dt, 0.f, 2.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateInput(dt);

	this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player->render(this->window);

}
