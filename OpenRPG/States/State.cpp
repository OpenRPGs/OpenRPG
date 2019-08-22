﻿#include "stdafx.h"

#include "Game/Game.h"
#include "State.h"
#include "Managers/StateManager.h"
#include "Entities/Player.h"

State::State(State* parent) {
	this->parent = parent;
	
	this->keyTime = 0.f;
	this->keyTimeMax = 0.1f;
}
State::~State() {
}

const bool State::getKeytime() {
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

//현재 스테이지를 끝내는 것이므로 pop으로 수정.
void State::endState() {
	StateManager::getInstance()->PopUntil(this);
}

void State::updateKeytime(const float dt) {
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 0.5f * dt;
}

void State::updateMousePositions() {
	auto window = Game::getWindow();

	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*window);
	this->mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::update() {
	auto dt = Game::getInstance()->deltaTime();
	this->updateKeytime(dt);
}
void State::render(sf::RenderTarget* target) {}
