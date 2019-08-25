#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "States/State.h"
#include "Managers/StateManager.h"

#include "PauseMenuState.h"
#include "States/MainMenu/MainMenuState.h"

#pragma region Initializer
void PauseMenuState::initTexture() {
	this->btnTexture = g::safe<sf::Texture>(new sf::Texture());
	if (!this->btnTexture->loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "ERROR::PauseMenuState::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	auto window = Game::getWindow();

	this->background.setSize(sf::Vector2f(
		static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
}

void PauseMenuState::initFont() {
	this->font = g::safe<sf::Font>(new sf::Font());
	if (!this->font->loadFromFile("Fonts/R2.ttc"))
		throw "ERROR:PauseMenuState::FAILED_TO_LOAD_FONT";
}

void PauseMenuState::initContainer() {
	auto window = Game::getWindow();

	this->container.setSize(sf::Vector2f(
		static_cast<float>(window->getSize().x) / 4.f,
		static_cast<float>(window->getSize().y) - 120.f));

	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(
		static_cast<float>(window->getSize().x) / 2.f - this->container.getSize().x / 2.f, 30.f));
}

void PauseMenuState::initText() {
	this->menuText.setFont(*this->font);
	this->menuText.setCharacterSize(50);
	this->menuText.setFillColor(g::Color("#fff"));
	this->menuText.setString(L"일시 정지");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f -
			this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f);
}

void PauseMenuState::initButtons() {
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - 250.f / 2.f;
	float y = 800.f;
	this->buttons["QUIT"] = g::safe<gui::Button>(new gui::Button(
		x, y, 250, 160, this->btnTexture, this->font, L"Quit", 40, g::Color("#000"),
		g::Color("#969696fa"), g::Color("#14141432"), g::Color("#fff"), g::Color("#fff"),
		g::Color("#fff")));
}

void PauseMenuState::initKeybinds() {}
#pragma endregion

PauseMenuState::PauseMenuState() : State() {
	this->initTexture();
	this->initContainer();
	this->initFont();
	this->initText();
	this->initButtons();
	this->initKeybinds();
}
PauseMenuState::~PauseMenuState() {}

void PauseMenuState::updateInput(const float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}
void PauseMenuState::update() {
	State::update();

	this->updateMousePositions();

	for (auto& it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->buttons["QUIT"]->isPressed()) {
		this->endState();
		StateManager::getInstance()->GoTo(SafeState(MainMenuState));
		return;
	}
}

void PauseMenuState::render(sf::RenderTexture* target) {
	State::render(target);

	target->draw(background);
	target->draw(container);

	for (auto& i : this->buttons)
		i.second->render(target);

	target->draw(this->menuText);
}
