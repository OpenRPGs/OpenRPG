#pragma once
class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float osffset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	//접근자
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	// functions
	bool intersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);

};

