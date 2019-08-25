#pragma once

class Tile {
  private:
  protected:
	sf::RectangleShape shap;

public:
	Tile(float x, float y, float gridSizeF,const sf::Texture& texture, const sf::IntRect& texture_rect);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget* target);
};
