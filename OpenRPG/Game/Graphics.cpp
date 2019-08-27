#include "stdafx.h"

#include "Graphics.h"

Graphics::Graphics() {
}

void Graphics::Transition(sf::RenderTexture *screen, const std::string& filename, float duration, int vague) {

}

void Graphics::Freeze() {
	this->freezed = true;
}

sf::RenderTexture *Graphics::getBackBuffer() {
	return this->backBuffer.get();
}

void Graphics::resetBackBuffer(int width, int height) {
	this->backBuffer.reset(new sf::RenderTexture());
	this->backBuffer->create(width, height);
}
