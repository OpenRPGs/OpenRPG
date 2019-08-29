#pragma once



/// <summary>그래픽 처리를 담당하는 클래스입니다.</summary>
class Graphics {
public:
	/// <summary>
	/// 그려지고 있던 화면을 효과 이미지에 맞추어서 최종적으로 그려진 화면으로 전환합니다.
	/// 그리기가 흐를 수 없는 화면으로 전환되려면, 이전 화면에서 Freeze 해야합니다.
	/// </summary>
	/// <param name="duration">전환이 걸리는 시간입니다. 초 단위입니다.</param>
	/// <param name="filename">전환에 쓰일 효과 이미지 경로입니다.</param>
	/// <param name="vague">전환 중의 경계의 모호함을 결정합니다.</param>
	void Transition(const std::string& filename, float duration = 2.f, int vague = 40);

	/// <summary>화면을 점점 밝게 그립니다.</summary>
	void FadeIn(float duration = 2.f);

	/// <summary>화면을 점점 어둡게 그립니다.</summary>
	void FadeOut(float duration = 2.f);

	/// <summary>화면의 밝기를 조절합니다.</summary>
	/// <param name="brightness">0 ~ 255 사이의 값입니다. 이 값이 작을수록 화면이 어두워집니다.</param>
	void setBrightness(int brightness);

	/// <summary>화면의 밝기를 가져옵니다.</summary>
	int getBrightness();

	/// <summary>
	/// 화면 갱신을 중지합니다. 백 버퍼는 갱신되지만 화면에 표시되지 않습니다.
	/// 보통 페이드 처리나 화면 전환을 위해 사용됩니다.
	/// </summary>
	void Freeze();

	/// <summary>백 버퍼 내용을 화면에 그리고 버퍼를 비웁니다. Freeze 상태라면 그리지 않습니다.</summary>
	void Present();

	/// <summary>백 버퍼 객체를 가져옵니다.</summary>
	g::safe<sf::RenderTexture> getBackBuffer();

	/// <summary>백 버퍼 객체를 새로 생성합니다.</summary>
	/// <param name="width">새로운 백 버퍼의 가로 크기입니다.</param>
	/// <param name="height">새로운 백 버퍼의 세로 크기입니다.</param>
	void resetBackBuffer(int width, int height);

	/// <summary>생성자입니다.</summary>
	Graphics();

protected:
	g::safe<sf::RenderTexture> backBuffer;
	g::safe<sf::RenderTexture> frozenBuffer;

	bool frozen = false;
	int brightness = 255;

	struct {
		bool ready;

		std::string filename;
		float duration;
		int vague;
	} transitionInfo;

	struct {
		bool fading;
		bool fadeIn;
		float duration;
		int progress;
	} fadeInfo;

	void PresentCore();
	void TransitionCore();
	void FadeCore();

	friend class Game;
};
