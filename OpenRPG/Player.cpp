#include "stdafx.h"

//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture_sheet, int& window_focus)
{
	this->window_focus = &window_focus;
	this->initVariables();
	this->setPositions(x, y);
	//초록색 캐주얼케릭터 설정
	//this->createMovementComponent(500.f, 500.f, 100.f);
	//this->createAnimationComponent(texture_sheet);

	//this->createHitboxComponent(this->sprite, 32.f, 28.f, 64.f, 74.f);

	//this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 3, 0, 3, 128, 128);
	//this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 0, 3, 0, 128, 128);
	//this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 3, 1, 128, 128);
	//this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 2, 3, 2, 128, 128);
	//this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 3, 3, 3, 128, 128);

	this->createHitboxComponent(this->sprite, 86.f, 55.f, 86.f, 120.f);
	this->createMovementComponent(350.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 5.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);

}


Player::~Player()
{

}

//초록색 캐주얼캐릭터용 update함수
//void Player::update(const float & dt)
//{
//	this->movementComponent->update(dt);
//
//
//	if (this->movementComponent->getState(IDLE))
//		this->animationComponent->play("IDLE_DOWN", dt);
//	else if (this->movementComponent->getState(MOVING_RIGHT))
//	{
//		this->animationComponent->play("WALK_RIGHT", dt);
//	}
//	else if (this->movementComponent->getState(MOVING_LEFT))
//	{
//		this->animationComponent->play("WALK_LEFT", dt);
//	}
//	else if (this->movementComponent->getState(MOVING_UP))
//	{
//		this->animationComponent->play("WALK_UP", dt);
//	}
//	else if (this->movementComponent->getState(MOVING_DOWN))
//	{
//		this->animationComponent->play("WALK_DOWN", dt);
//	}
//	//this->animationComponent->play("IDLE_LEFT", dt);
//
//	this->hitboxComponent->update();
//}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && *window_focus )
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float & dt)
{
	if (this->attacking)
	{
		//바라보는 방향체크
		if (this->sprite.getScale().x > 0.f)//왼쪽
		{
			this->sprite.setOrigin(96.f, 0.f);
		}
		else//오른쪽
		{
			this->sprite.setOrigin(258.f +96.f, 0.f);
		}

		//애니메이션 종료 체크
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			//바라보는 방향체크
			if (this->sprite.getScale().x > 0.f)//왼쪽
			{
				this->sprite.setOrigin(0.f, 0.f); 
			}
			else//오른쪽
			{
				this->sprite.setOrigin(258.f, 0.f);
			}
			this->attacking = false;
		}
	}
	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(258.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

}

void Player::update(const float & dt)
{
	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

