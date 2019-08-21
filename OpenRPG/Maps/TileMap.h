#pragma once
#include "../Tiles/Tile.h"
class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile>>> map;
public:
	TileMap();
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target);

};

