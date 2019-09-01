#include "stdafx.h"

#include "State.h"
#include "Managers/StateManager.h"
#include "../Entities/Player.h"

State::State(StateData* state_data) {
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 0.1f;
	this->gridSize = state_data->gridSize;
}

State::~State() {}

const bool State::getKeytime() {
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

//현재 스테이지를 끝내는 것이므로 pop으로 수정. //재수정
void State::endState() {
	StateManager::getInstance()->PopUntil(this);
}
void State::pauseState() {
	this->paused = true;
}
void State::unpauseState() {
	this->paused = false;
}

void State::updateKeytime(const float& dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 0.5f * dt;
}

void State::updateMousePositions(sf::View* view ) {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	
	if(view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid =
		sf::Vector2u(
			static_cast<unsigned>(this->mousePosView.x)/static_cast<unsigned>(this->gridSize),
			static_cast<unsigned>(this->mousePosView.y/ static_cast<unsigned>(this->gridSize))
		);

	this->window->setView(this->window->getDefaultView());
}

void State::initSounds() {
	if (!this->sounds["BACKGROUND_MUSIC"].loadFromFile("Resources/sound/bgm.ogg")) {
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BGM";
	}
}
