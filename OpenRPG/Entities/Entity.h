#pragma once

#include "Components/MovementComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/HitboxComponent.h"
#include "Components/SoundComponent.h"

class Entity
{
private:
	void initVariables();
protected:

	sf::Sprite sprite;

	//MovementComponent* movementComponent;
	sharedPtr<MovementComponent> movementComponent;
	//AnimationComponent* animationComponent;
	sharedPtr<AnimationComponent> animationComponent;
	//HitboxComponent* hitboxComponent;
	sharedPtr<HitboxComponent> hitboxComponent;
	//SoundComponent* soundComponent;
	sharedPtr<SoundComponent> soundComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite,const float offset_x, float offset_y, float width, float height);

	//함수들
	virtual void setPositions(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

};


