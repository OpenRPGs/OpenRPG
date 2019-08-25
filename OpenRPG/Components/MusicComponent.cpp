#include "stdafx.h"
#include "MusicComponent.h"

bool MusicComponent::Loaded() {
	return !!this->music;
}

#pragma region Play, Pause, Stop
MusicComponent* MusicComponent::play() {
	if (!this->music)
		return this;

	this->music->play();
	return this;
}

MusicComponent* MusicComponent::pause() {
	if (!this->music)
		return this;

	this->music->pause();
	return this;
}

MusicComponent* MusicComponent::stop() {
	if (!this->music)
		return this;

	this->music->stop();
	return this;
}
#pragma endregion

bool MusicComponent::isPlaying() {
	if (!this->music)
		return false;
	return this->music->getStatus() == sf::SoundSource::Status::Playing;
}

#pragma region Volume
MusicComponent* MusicComponent::setVolume(float volume) {
	if (!this->music)
		return this;
	this->music->setVolume(volume);
	return this;
}
float MusicComponent::getVolume() {
	if (!this->music)
		return -1;
	return this->music->getVolume();
}
#pragma endregion

#pragma region Offset
MusicComponent* MusicComponent::setOffset(int msec) {
	if (!this->music)
		return this;

	this->music->setPlayingOffset(sf::milliseconds(msec));
	return this;
}
int MusicComponent::getOffset() {
	if (!this->music)
		return -1;

	return this->music->getPlayingOffset().asMilliseconds();
}
#pragma endregion

#pragma region Loop
MusicComponent* MusicComponent::setLoop(bool loop) {
	if (!this->music)
		return this;

	this->music->setLoop(loop);
	return this;
}
bool MusicComponent::getLoop() {
	if (!this->music)
		return false;
	return this->music->getLoop();
}
#pragma endregion

MusicComponent::MusicComponent(const std::string& path) {
	this->reset(path);
}
MusicComponent::~MusicComponent() {}

MusicComponent* MusicComponent::reset(const std::string& path) {
	this->music = g::safe<sf::Music>(new sf::Music());
	if (!this->music->openFromFile(path))
		throw "ERROR:MusicComponent::Failed to load file";

	return this;
}
