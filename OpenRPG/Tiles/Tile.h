﻿#pragma once

enum TileTypes { DEFAILT = 0, DAMAGING };

class Tile
{
private:
protected:
	sf::RectangleShape shap;
	bool collision;
	short type;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAILT);
	virtual ~Tile();

	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);

};


