#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "States/State.h"
#include "PauseMenuState.h"
#include "States/MainMenu/MainMenuState.h"

#pragma region Initializer
void PauseMenuState::initBackground() {
	auto window = Game::getInstance()->getWindow();

	this->background.setSize(sf::Vector2f(
		static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

	this->background.setFillColor(sf::Color(20, 20, 20, 100));
}

void PauseMenuState::initContainer() {
	auto window = Game::getInstance()->getWindow();

	this->container.setSize(sf::Vector2f(
		static_cast<float>(window->getSize().x) / 4.f,
		static_cast<float>(window->getSize().y) - 120.f));

	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(
		static_cast<float>(window->getSize().x) / 2.f - this->container.getSize().x / 2.f, 30.f));
}

void PauseMenuState::initText() {
	this->menuText.setFont(font);
	this->menuText.setCharacterSize(50);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 255));
	this->menuText.setString(L"일시 정지");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f -
			this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f);
}

void PauseMenuState::initKeybinds() {}
#pragma endregion

void PauseMenuState::onEnter() {
	if (!this->font.loadFromFile("Fonts/R2.ttc"))
		throw "ERROR:PauseMenuState::FAILED_TO_LOAD_FONT";

	if (!btnTexture.loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "ERROR::PauseMenuState::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - 250.f / 2.f;
	float y = 800.f;
	this->buttons["QUIT"] = new gui::Button(
		x, y, 250, 160, &this->btnTexture, &this->font, L"Quit", 40, sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50), sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));
}

void PauseMenuState::onLeave() {
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

PauseMenuState::PauseMenuState(State* parent) : State() {
	this->parent = parent;
}

void PauseMenuState::update() {
	State::update();

	this->updateMousePositions();

	if (this->buttons["QUIT"]->isPressed()) {
		this->endState();
		StateManager::getInstance()->GoTo(new MainMenuState(), [](State *state) { delete state; });
		return;
	}
}

void PauseMenuState::updateInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void PauseMenuState::render(sf::RenderTarget* target) {
	State::render(target);

	if (!target)
		target = Game::getInstance()->getWindow();

	target->draw(background);
	target->draw(container);

	for (auto& i : this->buttons)
		i.second->render(target);

	target->draw(this->menuText);
}
