#include "stdafx.h"

#include "SoundManager.h"

#pragma region getInstance, Constructor, Finalizer, Dispose
SoundManager* SoundManager::Instance = NULL;

SoundManager* SoundManager::getInstance() {
	if (SoundManager::Instance == NULL) {
		SoundManager::Instance = new SoundManager();
	}
	return SoundManager::Instance;
}

SoundManager::SoundManager() {
	// 초기 볼륨
	this->volumeBGM = this->volumeSE = 100.f;
}

SoundManager::~SoundManager() {
	this->Dispose();
}

void SoundManager::Dispose() {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	this->Clear();

	this->disposed = true;
}
#pragma endregion

SoundManager* SoundManager::Clear() {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	// BGM 해제
	if (this->BGM)
		this->BGM.reset();

	// SE 해제
	this->SE.clear();
	return this;
}

#pragma region Volume
SoundManager* SoundManager::setVolumeSE(float volume) {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	this->volumeSE = volume;

	// SE 음원은 일회성이기에 재생중인 음원의 음량만 조절
	for (auto se : this->SE) {
		if (se->isPlaying())
			se->setVolume(volume);
	}
	return this;
}
float SoundManager::getVolumeSE() {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	return this->volumeSE;
}

SoundManager* SoundManager::setVolumeBGM(float volume) {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	this->volumeBGM = volume;

	if (this->BGM)
		this->BGM->setVolume(volume);

	return this;
}
float SoundManager::getVolumeBGM() {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	return this->volumeBGM;
}
#pragma endregion

#pragma region BGM, SE
bool SoundManager::LoadBGM(const std::string& path) {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	this->BGM = g::safe<MusicComponent>(new MusicComponent(path));

	this->BGM->setVolume(this->volumeBGM);
	return this->BGM->Loaded();
}

g::safe<MusicComponent> SoundManager::getBGM() {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	return this->BGM;
}

SoundManager* SoundManager::playSE(g::safe<sf::SoundBuffer> buffer) {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	if (buffer == NULL)
		throw "ERROR:SoundManager::buffer is NULL";

	auto sound = new sf::Sound(*buffer);
	if (sound == NULL)
		return this;

	// 비어있거나 재생이 끝난 SE가 있는지 검사
	for (auto it = this->SE.begin(); it != this->SE.end();) {
		auto se = *it;
		if (!se->isPlaying())
			this->SE.erase(it);
		else
			it++;
	}

	auto item = g::safe<SoundComponent>(new SoundComponent(buffer));
	this->SE.push_back(item); // 벡터에 삽입

	item->setVolume(this->volumeSE)->play(); // 관리중인 볼륨으로 설정하고 재생
	return this;
}
#pragma endregion
