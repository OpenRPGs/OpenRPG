#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();
protected:

	sf::Sprite sprite;

	MovementComponent* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

	//ÇÔ¼öµé
	virtual void setPositions(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

};
#endif // !ENTITY_H

