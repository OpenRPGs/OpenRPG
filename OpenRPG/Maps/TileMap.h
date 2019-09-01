#pragma once
#include "../Tiles/Tile.h"
#include "../Entities/Entity.h"
class TileMap
{
private:

	void clear();

	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;

	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	//접근자
	const sf::Texture* getTileSheet() const;

	//함수
	void updateCollision(Entity* entity);
	void update();
	void render(sf::RenderTarget& target, Entity* entity = NULL );

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const std::string fileName);
	void loadFromFile(const std::string fileName);
};

