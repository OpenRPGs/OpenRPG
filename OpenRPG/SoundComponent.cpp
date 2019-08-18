#include "stdafx.h"
#include "SoundComponent.h"


void SoundComponent::initSoundComponent(sf::SoundBuffer &buffer, bool loop)
{
	this->sound.setBuffer(buffer);
	this->sound.setLoop(loop);
}

void SoundComponent::pause()
{
	this->sound.pause();
}

void SoundComponent::playSound()
{
	this->sound.play();
}

void SoundComponent::stop()
{
	this->sound.stop();
}

SoundComponent::SoundComponent(sf::SoundBuffer &buffer, bool loop)
{
	this->initSoundComponent(buffer, loop);
}


SoundComponent::~SoundComponent()
{
}
