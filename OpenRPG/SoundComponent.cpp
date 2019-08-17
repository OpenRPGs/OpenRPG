#include "SoundComponent.h"


void SoundComponent::initSoundComponent(const std::string &filename)
{
	if (!this->buffer.loadFromFile(filename))
		throw "ERROR::SOUNDCOMPONENT::COULD_NOT_LOAD_SOUND_FILE";
}

void SoundComponent::pause()
{
	this->mysound.pause();
}

void SoundComponent::playSound()
{
	this->mysound.setBuffer(buffer);
	this->mysound.play();
}

void SoundComponent::stop()
{
	this->mysound.stop();
}

SoundComponent::SoundComponent(const std::string &filename)
{
	this->initSoundComponent(filename);
}


SoundComponent::~SoundComponent()
{
}
