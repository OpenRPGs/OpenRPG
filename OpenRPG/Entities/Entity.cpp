#include "stdafx.h"
#include "Entity.h"
#include "Components/MovementComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/HitboxComponent.h"
#include "Components/SoundComponent.h"

Entity::Entity() {
	this->sprite = g::safe<sf::Sprite>(new sf::Sprite());
}
Entity::~Entity() {}

// Componet functions
void Entity::setTexture(g::safe<sf::Texture> texture) {
	this->sprite->setTexture(*texture);
}

void Entity::createMovementComponent(
	const float maxVelocity, const float acceleration, const float deceleration) {
	this->movementComponent = g::safe<MovementComponent>(
		new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration));
}

void Entity::createAnimationComponent(g::safe<sf::Texture> texture_sheet) {
	this->animationComponent =
		g::safe<AnimationComponent>(new AnimationComponent(this->sprite, texture_sheet));
}

void Entity::createHitboxComponent(
	g::safe<sf::Sprite> sprite, const float offset_x, float offset_y, float width, float height) {
	this->hitboxComponent =
		g::safe<HitboxComponent>(new HitboxComponent(sprite, offset_x, offset_y, width, height));
}

// Functions

void Entity::setPositions(const float x, const float y) {
	this->sprite->setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float dt) {
	if (this->movementComponent) {
		this->movementComponent->move(dir_x, dir_y, dt); // Set velocity
	}
}

void Entity::update(const float dt) {}

void Entity::render(sf::RenderTarget* target) {
	target->draw(*this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}
