#include "Entity.h"


void Entity::initVariables()
{
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
}

//Componet functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
	//this->sprite->setTexture(*this->texture);
}

void Entity::createMovementComponent(const float maxVelocity)
{
	this->movementComponent = new MovementComponent(this->sprite,maxVelocity);
}

//Functions

void Entity::setPositions(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); // Set velocity
		
	}
}

void Entity::update(const float & dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
		target->draw(this->sprite);
}
