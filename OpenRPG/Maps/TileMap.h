#pragma once

#include "Tiles/Tile.h"

class TileMap {
  private:
	float gridSizeF;
	unsigned gridSizeU;

	sf::Vector2u maxSize;
	unsigned layers;

	std::vector<std::vector<std::vector<Tile*>>> map;
	g::safe<sf::Texture> tileSheet;

public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();
	
	//접근자
	const g::safe<sf::Texture> getTileSheet() const;

	//함수
	void update();
	void render(sf::RenderTarget* target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
};
