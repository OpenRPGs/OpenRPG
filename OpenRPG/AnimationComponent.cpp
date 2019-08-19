#include "stdafx.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{
}

//Accessors
const bool & AnimationComponent::isDone(std::string key) 
{
	return this->animations[key]->isDone();
	// TODO: 여기에 반환 구문을 삽입합니다.
}

//Functions
AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animations)
		delete i.second;
}



void AnimationComponent::addAnimation(
	const std::string key,
	float animation_Timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, animation_Timer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height
	);
}

const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{

	if (this->priorityAnimation) // 만약 우선순위인 애니메이션이있다면
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			//If the priority animation is done, remove it
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else {
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}
		//To DO : Coustomizing Animations More Smooth.. (19/08/16 bugfix Done!!)
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt);
	}
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float & dt, const float & modifier, const float & modifier_max, const bool priority)
{
	if (this->priorityAnimation) // 만약 우선순위인 애니메이션이있다면
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done, remove it
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}
	return this->animations[key]->isDone();
}

