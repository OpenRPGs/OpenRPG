#include "stdafx.h"

#include "GUI/Gui.h"

gui::DropDownList::DropDownList(
	float x, float y, float width, float height, g::safe<sf::Font> font, std::wstring list[],
	unsigned numOfElements, const unsigned default_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(0.f) {

	this->activeElement = g::safe<gui::Button>(new gui::Button(
		x, y, width, height, this->font, list[default_index], 20, sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 200), g::Color("#14141432"), sf::Color(70, 70, 70, 200),
		sf::Color(155, 155, 155, 200), sf::Color(25, 25, 25, 200), sf::Color(255, 255, 255, 200),
		g::Color("#fff"), sf::Color(25, 25, 25, 50)));

	for (unsigned int i = 0; i < numOfElements; i++) {
		this->list.push_back(g::safe<gui::Button>(new gui::Button(
			x, y + (i + 1) * height, width, height, this->font, list[i], 20,
			sf::Color(255, 255, 255, 150), g::Color("#fff"), g::Color("#14141432"),
			sf::Color(70, 70, 70, 200), sf::Color(155, 155, 155, 200), sf::Color(25, 25, 25, 200),
			sf::Color(255, 255, 255, 200), g::Color("#fff"), sf::Color(25, 25, 25, 50), i)));
	}
}
gui::DropDownList::~DropDownList() {}

const unsigned short gui::DropDownList::getActiveElementId() const {
	return this->activeElement->getId();
}

const bool gui::DropDownList::getKeytime() {
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void gui::DropDownList::updateKeytime(const float dt) {
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f mousePos, const float dt) {
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);

	//드랍다운구현부분
	if (this->activeElement->isPressed() && this->getKeytime()) {
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList) {
		for (auto& i : this->list) {
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime()) {
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget* target) {
	this->activeElement->render(target);

	if (this->showList) {
		for (auto& i : this->list) {
			i->render(target);
		}
	}
}
