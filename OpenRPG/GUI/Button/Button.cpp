#include "stdafx.h"

#include "GUI/Gui.h"

gui::Button::Button(
	float x, float y, float width, float height, g::safe<sf::Texture> buttonTexture,
	g::safe<sf::Font> font, std::wstring text, unsigned character_size, sf::Color text_idle_color,
	sf::Color text_hover_color, sf::Color text_active_color, sf::Color idle_Color,
	sf::Color hover_Color, sf::Color active_Color) {
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_Color);
	this->shape.setTexture(buttonTexture.get());

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) -
			this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) -
			this->text.getGlobalBounds().height / 2.f - 10.f);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_Color;
	this->hoverColor = hover_Color;
	this->activeColor = active_Color;
}

gui::Button::Button(
	float x, float y, float width, float height, g::safe<sf::Font> font, std::wstring text,
	unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color,
	sf::Color text_active_color, sf::Color idle_Color, sf::Color hover_Color,
	sf::Color active_Color, sf::Color outline_idle_Color, sf::Color outline_hover_Color,
	sf::Color outline_active_Color, short unsigned id) {
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_Color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_Color);

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) -
			this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) -
			this->text.getGlobalBounds().height / 2.f - 10.f);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_Color;
	this->hoverColor = hover_Color;
	this->activeColor = active_Color;

	this->outlineIdleColor = outline_idle_Color;
	this->outlineHoverColor = outline_hover_Color;
	this->outlineActiveColor = outline_active_Color;
}

gui::Button::~Button() {}

//접근자
const bool gui::Button::isPressed() const {
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

const std::string gui::Button::getText() const {
	return this->text.getString();
}

const short unsigned gui::Button::getId() const {
	return this->id;
}

// Modifiers
void gui::Button::setText(const std::string text) {
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id) {
	this->id = id;
}

//함수

void gui::Button::update(const sf::Vector2f mousePos) {
	// Update the booleans for hover and pressed

	this->buttonState = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState) {
		case BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			break;

		case BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;

		case BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			this->text.setFillColor(this->textActiveColor);
			this->shape.setOutlineColor(this->outlineActiveColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Blue);
			this->shape.setOutlineColor(sf::Color::Green);
			break;
	}
}

void gui::Button::render(sf::RenderTarget* target) {
	target->draw(this->shape);
	target->draw(this->text);
}
