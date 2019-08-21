#include "stdafx.h"
#include "SoundComponent.h"

bool SoundComponent::isSame(sf::SoundBuffer* buffer) {
	return buffer == this->sound->getBuffer();
}

bool SoundComponent::Loaded() {
	return this->sound != NULL;
}

#pragma region Play, Pause, Stop
SoundComponent* SoundComponent::play() {
	if (this->sound == NULL)
		return this;

	this->sound->play();
	return this;
}

SoundComponent* SoundComponent::pause() {
	if (this->sound == NULL)
		return this;

	this->sound->pause();
	return this;
}

SoundComponent* SoundComponent::stop() {
	if (this->sound == NULL)
		return this;

	this->sound->stop();
	return this;
}
#pragma endregion

bool SoundComponent::isPlaying() {
	if (this->sound == NULL)
		return false;
	return this->sound->getStatus() == sf::Sound::Status::Playing;
}

#pragma region Volume
SoundComponent* SoundComponent::setVolume(float volume) {
	if (this->sound == NULL)
		return this;
	this->sound->setVolume(volume);
	return this;
}
float SoundComponent::getVolume() {
	if (this->sound == NULL)
		return -1;
	return this->sound->getVolume();
}
#pragma endregion

#pragma region Offset
SoundComponent* SoundComponent::setOffset(int msec) {
	if (this->sound == NULL)
		return this;

	this->sound->setPlayingOffset(sf::milliseconds(msec));
	return this;
}
int SoundComponent::getOffset() {
	if (this->sound == NULL)
		return -1;

	return this->sound->getPlayingOffset().asMilliseconds();
}
#pragma endregion

#pragma region Loop
SoundComponent* SoundComponent::setLoop(bool loop) {
	if (this->sound == NULL)
		return this;

	this->sound->setLoop(loop);
	return this;
}
bool SoundComponent::getLoop() {
	if (this->sound == NULL)
		return false;
	return this->sound->getLoop();
}
#pragma endregion

SoundComponent::SoundComponent(sf::SoundBuffer* buffer) {
	if (buffer == NULL)
		throw "ERROR:SoundComponent::buffer is NULL";

	this->sound = new sf::Sound(*buffer);
}
SoundComponent::~SoundComponent() {
	if (this->sound != NULL) {
		delete this->sound;
		this->sound = NULL;
	}
}

SoundComponent* SoundComponent::reset(sf::SoundBuffer* buffer) {
	if (buffer == NULL)
		throw "ERROR:SoundComponent::buffer is NULL";

	if (this->sound == NULL)
		return this;

	this->sound->stop();
	this->sound->setBuffer(*buffer);
	this->sound->setPlayingOffset(sf::milliseconds(0));
	return this;
}
