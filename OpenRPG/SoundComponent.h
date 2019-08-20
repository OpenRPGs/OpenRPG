#pragma once

/// <summary>
/// <see cref="sf::SoundBuffer"/>를 재생 가능한 상태로 불러오는 클래스입니다.
/// </summary>
class SoundComponent
{
	/// <summary>
	/// 버퍼에서 생성된 <see cref="sf::Sound"/> 객체입니다.
	/// 할당에 실패하면 <c>NULL</c> 입니다.
	/// </summary>
	sf::Sound *sound;

public:
	/// <summary>음원을 불러오는데 성공했는지 여부입니다.</summary>
	bool Loaded();

	/// <summary>불러온 음원을 재생합니다.</summary>
	SoundComponent *play();
	/// <summary>재생중인 음원을 일시중지합니다.</summary>
	SoundComponent *pause();
	/// <summary>재생중인 음원을 중지합니다. 오프셋이 처음으로 돌아갑니다.</summary>
	SoundComponent *stop();

	/// <summary>음원이 재생중인지 여부입니다.</summary>
	bool isPlaying();

	/// <summary>음원의 음량을 설정합니다. 범위는 0.f ~ 100.f 입니다.</summary>
	SoundComponent *setVolume(float volume);
	/// <summary>음원의 음량을 가져옵니다.  범위는 0.f ~ 100.f 입니다.</summary>
	float getVolume();

	/// <summary>
	/// 음원의 재생 위치를 변경합니다.
	/// 재생 위치의 단위는 밀리초입니다.
	/// </summary>
	SoundComponent *setOffset(int msec);
	/// <summary>
	/// 음원의 재생 위치를 가져옵니다.
	/// 재생 위치의 단위는 밀리초입니다.
	/// </summary>
	int getOffset();

	/// <summary>반복 재생 여부를 설정합니다.</summary>
	SoundComponent *setLoop(bool loop);
	/// <summary>반복 재생 여부를 가져옵니다.</summary>
	bool getLoop();

	/// <summary>
	/// <see cref="sf::SoundBuffer"/>로부터 재생 가능하고 관리되는 <see cref="SoundComponent"/>를 생성합니다.
	/// </summary>
	SoundComponent(sf::SoundBuffer &buffer);

	/// <summary>
	/// <see cref="SoundComponent"/>가 해제될 때, 할당된 자원들을 같이 해제합니다.
	/// </summary>
	virtual ~SoundComponent();

	/// <summary>
	/// 음원의 버퍼를 교체합니다.
	/// </summary>
	SoundComponent* reset(sf::SoundBuffer &buffer);
};
