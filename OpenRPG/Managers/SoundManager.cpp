#include "stdafx.h"
#include "SoundManager.h"

using namespace std;

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

	this->BGM = NULL;

	// vector 공간 예약 할당
	this->SE.reserve(sizeof(SoundComponent*) * 4);
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
	if (this->BGM != NULL) {
		delete this->BGM;
		this->BGM = NULL;
	}

	// SE 해제
	while (this->SE.size() > 0) {
		auto back = this->SE.back();
		this->SE.pop_back();
		if (back != NULL)
			delete back;
	}

	return this;
}

#pragma region Volume
SoundManager* SoundManager::setVolumeSE(float volume) {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	this->volumeSE = volume;

	// SE 음원은 일회성이기에 재생중인 음원의 음량만 조절
	for (vector<SoundComponent*>::size_type i = 0; i < this->SE.size(); i++) {
		auto item = this->SE[i];
		if (item != NULL && item->isPlaying())
			item->setVolume(volume);
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

	if (this->BGM != NULL)
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
bool SoundManager::LoadBGM(sf::SoundBuffer* buffer) {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	if (buffer == NULL)
		throw "ERROR:SoundManager::buffer is NULL";

	if (this->BGM) {
		if (!this->BGM->isSame(buffer))
			this->BGM->reset(buffer);
	} else {
		this->BGM = new SoundComponent(buffer);
	}

	this->BGM->setVolume(this->volumeBGM);
	return this->BGM->Loaded();
}

SoundComponent* SoundManager::getBGM() {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	return this->BGM;
}

SoundManager* SoundManager::playSE(sf::SoundBuffer* buffer) {
	if (this->disposed)
		throw "ERROR::SoundManager::Already Disposed";

	if (buffer == NULL)
		throw "ERROR:SoundManager::buffer is NULL";

	auto sound = new sf::Sound(*buffer);
	if (sound == NULL)
		return this;

	vector<SoundComponent*>::size_type i;

	// 비어있거나 재생이 끝난 SE가 있는지 검사
	for (i = 0; i < this->SE.size(); i++) {
		auto item = this->SE[i];
		if (item == NULL || !item->isPlaying()) {
			if (item != NULL) {
				delete item;
				this->SE[i] = NULL;
			}
			break;
		}
	}

	// Idle 상태의 SE가 없다면 새 벡터 영역을 할당
	while (i >= this->SE.size())
		this->SE.push_back(NULL);

	auto item = new SoundComponent(buffer);
	item->setVolume(this->volumeSE); // 관리중인 볼륨으로
	item->play();
	this->SE[i] = item; // 벡터에 삽입

	return this;
}
#pragma endregion
