#include "stdafx.h"

#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF) {
	this->shap.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shap.setFillColor(sf::Color::Green);
	this->shap.setPosition(x, y);
}
Tile::~Tile() {}

void Tile::update() {}

void Tile::render(sf::RenderTarget* target) {
	target->draw(this->shap);
}
