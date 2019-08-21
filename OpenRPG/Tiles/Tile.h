#pragma once

class Tile
{
private:
protected:
	sf::RectangleShape shap;

public:
	Tile(float x, float y, float gridSizeF);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget& target);

};


