﻿#include "stdafx.h"
#include "Entity.h"
#include "Components/MovementComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/HitboxComponent.h"
#include "Components/SoundComponent.h"

void Entity::initVariables()
{
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->hitboxComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	//delete this->movementComponent;
	//delete this->animationComponent;
	//delete this->hitboxComponent;
}

//Componet functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
	//this->sprite->setTexture(*this->texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	movementComponent = sharedPtr<MovementComponent>(new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration));
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
	//this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
	animationComponent = sharedPtr<AnimationComponent>(new AnimationComponent(this->sprite, texture_sheet));
}

void Entity::createHitboxComponent(sf::Sprite& sprite, const float offset_x, float offset_y, float width, float height)
{
	//this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
	hitboxComponent = sharedPtr<HitboxComponent>(new HitboxComponent(sprite, offset_x, offset_y, width, height));
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

//Functions

void Entity::setPositions(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt); // Set velocity
}

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget& target)
{

}
