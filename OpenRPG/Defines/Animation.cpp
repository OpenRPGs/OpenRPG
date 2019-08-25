#include "stdafx.h"
#include "Animation.h"

Animation::Animation(
	g::safe<sf::Sprite> sprite, g::safe<sf::Texture> textureSheet, float animation_Timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
	: sprite(sprite), textureSheet(textureSheet), animationTimer(animation_Timer), timer(0.f),
	  done(false), width(width), height(height) {

	this->timer = 0.f;
	this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
	this->currentRect = this->startRect;
	this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

	this->sprite->setTexture(*this->textureSheet, true);
	this->sprite->setTextureRect(this->startRect);
}

const bool Animation::isDone() const {
	return this->done;
}

const bool Animation::play(const float dt) {
	// Update timer
	this->done = false;
	this->timer += 100.f * dt;

	if (this->timer >= this->animationTimer) {
		this->timer = 0.f;

		// Animate
		if (this->currentRect != this->endRect) {
			this->currentRect.left += this->width;
		} else { // Reset
			this->currentRect.left = this->startRect.left;
			this->done = true;
		}

		this->sprite->setTextureRect(this->currentRect);
	}
	return this->done;
}

const bool Animation::play(const float dt, float mod_percentage) {
	if (mod_percentage < 0.5f)
		mod_percentage = 0.5f;

	this->done = false;
	this->timer += mod_percentage * 100.f * dt;

	if (this->timer >= this->animationTimer) {
		this->timer = 0.f;

		// Animate
		if (this->currentRect != this->endRect) {
			this->currentRect.left += this->width;
		} else { // Reset
			this->currentRect.left = this->startRect.left;
			this->done = true;
		}

		this->sprite->setTextureRect(this->currentRect);
	}
	return this->done;
}

void Animation::reset() {
	this->timer = this->animationTimer;
	this->currentRect = this->startRect;
}
