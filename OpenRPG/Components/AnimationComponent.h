#pragma once

#include "Defines/Animation.h"

class AnimationComponent {
  private:
	g::safe<sf::Sprite> sprite;
	g::safe<sf::Texture> textureSheet;
	g::safemap<Animation> animations;

	g::safe<Animation> lastAnimation;
	g::safe<Animation> priorityAnimation;

  public:
	AnimationComponent(g::safe<sf::Sprite> sprite, g::safe<sf::Texture> texture_sheet);
	virtual ~AnimationComponent();

	// Accessor
	const bool isDone(std::string key);

	// Functions
	void addAnimation(
		const std::string key, float animation_Timer, int start_frame_x, int start_frame_y,
		int frames_x, int frames_y, int width, int height);

	const bool play(const std::string key, const float dt, const bool priority = false);
	const bool play(
		const std::string key, const float dt, const float modifier, const float modifier_max,
		const bool priority = false);
};
