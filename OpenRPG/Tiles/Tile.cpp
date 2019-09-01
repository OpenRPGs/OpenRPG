#include "stdafx.h"
#include "Tile.h"



Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision, short type)
{
	this->shap.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shap.setFillColor(sf::Color::White);
	//this->shap.setOutlineThickness(1.f);
	//this->shap.setOutlineColor(sf::Color::Black);
	this->shap.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->shap.setTexture(&texture);
	this->shap.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;
}


Tile::~Tile()
{
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->shap.getTextureRect().left << " " << shap.getTextureRect().top << " " << this->collision << " " << this->type;

	return ss.str();
}

const sf::Vector2f & Tile::getPosition() const
{
	return this->shap.getPosition();
}

const bool & Tile::getCollision() const
{
	return this->collision;
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget & target)
{
	target.draw(this->shap);
}
