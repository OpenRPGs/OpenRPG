#pragma once
#include "../Tiles/Tile.h"
class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSize;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::string textureFile;
	sf::Texture tileSheet;
	

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();
	
	//접근자
	const sf::Texture* getTileSheet() const;

	//함수
	void update();
	void render(sf::RenderTarget& target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);
};

