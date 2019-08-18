#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializer functions
public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accecssors
	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;

	//Functions
	const bool getState(const short unsigned state) const;

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

#endif 