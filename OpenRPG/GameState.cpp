#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending GameState! " << std::endl;
}

void GameState::updateKeybinds(const float & dt)
{
	this->checkForQuit();
}

void GameState::update(const float& dt)
{
	this->updateKeybinds(dt);

	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (target)
	{

	}
	else 
	{
		this->player.render(this->window);
	}
}
