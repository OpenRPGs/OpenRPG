#pragma once

#include "Components/SoundComponent.h"

/// <summary>
/// <see cref="SoundComponent"/>를 통합 관리하는 클래스입니다.
/// </summary>
class SoundManager {
  public:
	/// <summary>
	/// 싱글톤 인스턴스를 가져옵니다.
	/// 기존에 인스턴스가 없었다면 새로 생성합니다.
	/// </summary>
	/// <returns><see cref="SoundManager"/>의 싱글톤 객체입니다.</returns>
	static SoundManager* getInstance();
	/// <summary>
	///SE 음원의 음량을 설정합니다. 범위는 0.f ~ 100.f 입니다.
	///	</summary>
	SoundManager* setVolumeSE(float volume);
	/// 
	///<summary>SE 음원의 음량을 가져옵니다. 범위는 0.f ~ 100.f 입니다.
	///</summary>
	float getVolumeSE();
	/// <summary>
	///BGM 음원의 음량을 설정합니다. 범위는 0.f ~ 100.f 입니다.
	///</summary>
	SoundManager* setVolumeBGM(float volume);
	/// <summary>
	///BGM 음원의 음량을 가져옵니다. 범위는 0.f ~ 100.f 입니다.
	///</summary>
	float getVolumeBGM();
	/// <summary>
	/// 기존의 BGM 정보를 해제하고 새로 BGM 정보를 불러옵니다.
	/// 불러온 정보는 <see cref="getBGM"/>을 통해 불러올 수 있습니다.
	/// </summary>
	/// <param name="buffer">BGM으로 불러올 <see cref="sf::SoundBuffer"/>입니다.</param>
	bool LoadBGM(sf::SoundBuffer& buffer);
	/// <summary>
	/// 불러온 BGM 정보를 가지는 <see cref="SoundComponent"/> 객체입니다.
	/// BGM 정보가 없다면 <c>NULL</c>을 반환합니다.
	/// </summary>
	SoundComponent* getBGM();
	/// <summary>
	/// SE로 재생될 음원을 불러오고 병렬적으로 재생합니다.
	/// </summary>
	/// <param name="buffer">SE로 불러올 <see cref="sf::SoundBuffer"/>입니다.</param>
	SoundManager* playSE(sf::SoundBuffer& buffer);

  private:
	/// <summary>
	/// 싱글톤 인스턴스입니다.
	/// 프로세스 내에 한번만 할당되는 것이 보장됩니다.
	/// </summary>
	static SoundManager* Instance;
	/// <summary>
	/// BGM 정보를 담고있는 <see cref="SoundComponent"/> 객체입니다.
	/// </summary>
	SoundComponent* BGM;
	/// <summary>
	/// 관리되지 않는 SE 정보들을 담고 있는 <see cref="SoundComponent"/> 목록입니다.
	/// </summary>
	std::vector<SoundComponent*> SE;

	float volumeSE;
	float volumeBGM;
	/// <summary>
	/// 생성자입니다. private로 지정하여 일반적인 할당을 금지합니다.
	/// </summary>
	SoundManager();
	~SoundManager();
	static void destroy();
};
