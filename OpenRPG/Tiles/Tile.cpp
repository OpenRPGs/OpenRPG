#include "stdafx.h"

#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF,const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->shap.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shap.setFillColor(sf::Color::White);
	//this->shap.setOutlineThickness(1.f);
	//this->shap.setOutlineColor(sf::Color::Black);
	this->shap.setPosition(x, y);
	this->shap.setTexture(&texture);
	this->shap.setTextureRect(texture_rect);
}
Tile::~Tile() {}

void Tile::update() {}

void Tile::render(sf::RenderTarget* target) {
	target->draw(this->shap);
}
