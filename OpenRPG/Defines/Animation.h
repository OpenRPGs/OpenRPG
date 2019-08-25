#pragma once

class Animation {
  public:
	// Variables
	g::safe<sf::Sprite> sprite;
	g::safe<sf::Texture> textureSheet;

	float animationTimer;
	float timer;
	bool done;
	int width;
	int height;

	sf::IntRect startRect;
	sf::IntRect currentRect;
	sf::IntRect endRect;

	Animation(
		g::safe<sf::Sprite> sprite, g::safe<sf::Texture> textureSheet, float animation_Timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	// Accecssor
	const bool isDone() const;

	// Fonctions
	const bool play(const float dt);
	const bool play(const float dt, float mod_percentage);

	void reset();
};
