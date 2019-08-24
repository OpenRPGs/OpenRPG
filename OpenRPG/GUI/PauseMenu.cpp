#include "stdafx.h"
#include "Gui.h"
#include "PauseMenu.h"
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	//배경 초기화
	this->background.setSize(sf::Vector2f
	(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y))
	);

	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f
	(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y) - 120.f
	)
	);
	//컨테이너 초기화
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f
	(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f)
	);

	//text초기화
	this->menuText.setFont(font);
	this->menuText.setCharacterSize(50);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 255));
	this->menuText.setString(L"일시 정지");
	this->menuText.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);
}


PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}
//Accecssors
std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}




//Functions

const bool PauseMenu::isButtonPressed(const std::string key) 
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text, sf::Texture& btnTexure)
{
	float width = 250.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons["QUIT"] = new gui::Button(
		x, y, 250, 80,
		btnTexure, this->font, L"새 게임", 40,
		sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget & target)
{
	target.draw(background);
	target.draw(container);

	for (auto &i : this->buttons)
		i.second->render(target);

	target.draw(this->menuText);
}
