#include "Player.h"


//Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{
	this->createMovementComponent(200.f);
}

Player::Player(float x,float y, sf::Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPositions(x, y);
}


Player::~Player()
{

}
