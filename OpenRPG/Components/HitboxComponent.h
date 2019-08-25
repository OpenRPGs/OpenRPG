#pragma once
class HitboxComponent
{
private:
	g::safe<sf::Sprite> sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(g::safe<sf::Sprite> sprite, float osffset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	// functions
	bool checkIntersect(const sf::FloatRect frect);

	void update();
	void render(sf::RenderTarget* target);

};

