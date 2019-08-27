#pragma once

class Graphics {
public:
	/// <summary>화면을 효과 이미지에 맞추어서 전환합니다.</summary>
	/// <param name="screen">그려지고 있던 화면입니다.</param>
	/// <param name="duration">전환이 걸리는 시간입니다. 초 단위입니다.</param>
	/// <param name="filename">전환에 쓰일 효과 이미지 경로입니다.</param>
	/// <param name="vague">전환 중의 경계의 모호함을 결정합니다.</param>
	void Transition(sf::RenderTexture *screen, const std::string& filename, float duration = 8.f, int vague = 40);

	/// <summary>화면 갱신을 중지합니다. 백 버퍼는 갱신되지만 화면에 표시되지 않습니다.</summary>
	void Freeze();

	/// <summary>백 버퍼 내용을 화면에 그립니다. Freeze 상태라면 그리지 않습니다.</summary>
	void Present();

	/// <summary>백 버퍼 객체를 가져옵니다.</summary>
	sf::RenderTexture* getBackBuffer();

	/// <summary>백 버퍼 객체를 새로 생성합니다.</summary>
	void resetBackBuffer(int width, int height);

	Graphics();

private:
	g::safe<sf::RenderTexture> backBuffer;
	bool freezed = false;
};
