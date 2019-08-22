#include "stdafx.h"
#include "SoundComponent.h"

bool SoundComponent::isSame(g::safe<sf::SoundBuffer> buffer) {
	return buffer.get() == this->sound->getBuffer();
}

bool SoundComponent::Loaded() {
	return this->sound != NULL;
}

#pragma region Play, Pause, Stop
SoundComponent* SoundComponent::play() {
	if (!this->sound)
		return this;

	this->sound->play();
	return this;
}

SoundComponent* SoundComponent::pause() {
	if (!this->sound)
		return this;

	this->sound->pause();
	return this;
}

SoundComponent* SoundComponent::stop() {
	if (!this->sound)
		return this;

	this->sound->stop();
	return this;
}
#pragma endregion

bool SoundComponent::isPlaying() {
	if (!this->sound)
		return false;
	return this->sound->getStatus() == sf::Sound::Status::Playing;
}

#pragma region Volume
SoundComponent* SoundComponent::setVolume(float volume) {
	if (!this->sound)
		return this;
	this->sound->setVolume(volume);
	return this;
}
float SoundComponent::getVolume() {
	if (!this->sound)
		return -1;
	return this->sound->getVolume();
}
#pragma endregion

#pragma region Offset
SoundComponent* SoundComponent::setOffset(int msec) {
	if (!this->sound)
		return this;

	this->sound->setPlayingOffset(sf::milliseconds(msec));
	return this;
}
int SoundComponent::getOffset() {
	if (!this->sound)
		return -1;

	return this->sound->getPlayingOffset().asMilliseconds();
}
#pragma endregion

#pragma region Loop
SoundComponent* SoundComponent::setLoop(bool loop) {
	if (!this->sound)
		return this;

	this->sound->setLoop(loop);
	return this;
}
bool SoundComponent::getLoop() {
	if (!this->sound)
		return false;
	return this->sound->getLoop();
}
#pragma endregion

SoundComponent::SoundComponent(g::safe<sf::SoundBuffer> buffer) {
	if (buffer == NULL)
		throw "ERROR:SoundComponent::buffer is NULL";

	this->sound = g::safe<sf::Sound>(new sf::Sound(*buffer));
}
SoundComponent::~SoundComponent() {}

SoundComponent* SoundComponent::reset(g::safe<sf::SoundBuffer> buffer) {
	if (!buffer)
		throw "ERROR:SoundComponent::buffer is NULL";

	if (!this->sound) {
		this->sound = g::safe<sf::Sound>(new sf::Sound(*buffer));
	} else {
		this->sound->stop();
		this->sound->setBuffer(*buffer);
		this->sound->setPlayingOffset(sf::milliseconds(0));
	}
	return this;
}
