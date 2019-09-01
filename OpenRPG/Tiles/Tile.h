#pragma once

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
	Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAILT);
	virtual ~Tile();

	const std::string getAsString() const;
	const sf::Vector2f& getPosition() const;
	const bool & getCollision() const;

	void update();
	void render(sf::RenderTarget& target);

};


