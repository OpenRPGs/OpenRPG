﻿#include "stdafx.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->paused = false;
}

State::~State()
{
}

const bool & State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}



void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window ->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::initSounds()
{
	if (!this->sounds["BACKGROUND_MUSIC"].loadFromFile("Resources/sound/bgm.wav"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BGM";
	}
}