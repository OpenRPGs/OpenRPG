#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap()
{
	this->gridSizeF = 100.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = 10;
	this->maxSize.y = 10;
	this->layers = 1;

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < maxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile>>());
		for (size_t y = 0; y < maxSize.y; y++)
		{
			this->map[x].push_back(std::vector<Tile>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].push_back(Tile(x * this->gridSizeF, y *this->gridSizeF ,this->gridSizeF));
			}
		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget & target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto &z : y)
			{
				z.render(target);
			}
		}
	}
}
