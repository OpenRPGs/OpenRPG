#include "stdafx.h"
#include "Tile.h"



Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision, short type)
{
	this->shap.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shap.setFillColor(sf::Color::White);
	//this->shap.setOutlineThickness(1.f);
	//this->shap.setOutlineColor(sf::Color::Black);
	this->shap.setPosition(x, y);
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

void Tile::update()
{

}

void Tile::render(sf::RenderTarget & target)
{
	target.draw(this->shap);
}
