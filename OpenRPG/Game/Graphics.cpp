#include "stdafx.h"

#include "Game.h"
#include "Graphics.h"

Graphics::Graphics() {
	this->backBuffer = g::safe<sf::RenderTexture>(new sf::RenderTexture());
	this->frozenBuffer = g::safe<sf::RenderTexture>(new sf::RenderTexture());

	this->brightness = 255;
	this->transitionInfo.ready = false;
	this->fadeInfo.fading = false;
}

void Graphics::Transition(const std::string& filename, float duration, int vague) {
	if (!this->frozen)
		return;

	this->transitionInfo.filename = filename;
	this->transitionInfo.duration = duration;
	this->transitionInfo.vague = vague;
	this->transitionInfo.ready = true;
}

void Graphics::FadeIn(float duration) {
	this->fadeInfo.fadeIn = true;
	this->fadeInfo.duration = duration;
	this->fadeInfo.progress = 0;
	this->fadeInfo.fading = true;

	if (this->frozen && !this->transitionInfo.ready)
		this->FadeCore();
}

void Graphics::FadeOut(float duration) {
	this->fadeInfo.fadeIn = false;
	this->fadeInfo.duration = duration;
	this->fadeInfo.progress = 0;
	this->fadeInfo.fading = true;

	if (this->frozen && !this->transitionInfo.ready)
		this->FadeCore();
}

void Graphics::setBrightness(int brightness) {
	this->brightness = brightness;
}

int Graphics::getBrightness() {
	return this->brightness;
}

void Graphics::Freeze() {
	this->frozen = true;

	auto size = this->backBuffer->getSize();

	this->frozenBuffer->create(size.x, size.y);

	sf::Sprite renderTargetSprite(this->backBuffer->getTexture());
	this->frozenBuffer->draw(renderTargetSprite);
}

g::safe<sf::RenderTexture> Graphics::getBackBuffer() {
	return this->backBuffer;
}

void Graphics::resetBackBuffer(int width, int height) {
	this->backBuffer->create(width, height);
}

void Graphics::Present() {
	if (!this->frozen) {
		auto window = Game::getWindow();
		this->backBuffer->display();
		sf::Sprite renderTargetSprite(this->backBuffer->getTexture());
		window->draw(renderTargetSprite);

		this->PresentCore();

		// 그린 결과물을 화면에 표시
		window->display();

		this->backBuffer->clear();
	}
}

void Graphics::PresentCore() {
	if (this->brightness < 255) {
		auto window = Game::getWindow();
		auto size = this->backBuffer->getSize();

		sf::RectangleShape fill;
		fill.setSize(g::Vec2uf(size));
		fill.setFillColor(g::Color("#000000", 255 - this->brightness));
		window->draw(fill);
	}
}

void Graphics::TransitionCore() {
	if (!this->frozen || !this->transitionInfo.ready)
		return;

	auto filename = this->transitionInfo.filename;
	auto duration = this->transitionInfo.duration;
	auto vague = this->transitionInfo.vague;

	vague = vague < 1 ? 1 : vague > 256 ? 256 : vague; // 1 <= vague <= 256

	sf::Texture transMap;
	if (!filename.empty()) {
		if (!transMap.loadFromFile(filename))
			throw "Graphics::Transition::Failed to load transMap";
	}

	this->setBrightness(255);

	auto size = this->backBuffer->getSize();
	sf::RenderTexture currentScreen;
	currentScreen.create(size.x, size.y);

	{
		sf::Sprite renderTargetSprite(this->backBuffer->getTexture());
		currentScreen.draw(renderTargetSprite);
		currentScreen.display();
	}

	auto window = Game::getWindow();
	sf::Shader shader;
	if (filename.empty()) {
		if (!shader.loadFromFile("Resources/shader/transFade.frag", sf::Shader::Type::Fragment))
			throw "Graphics::Transition::Failed to load transFade.rag";

		shader.setUniform("currentScreen", currentScreen.getTexture());
		shader.setUniform("frozenScreen", this->frozenBuffer->getTexture());
	} else {
		if (!shader.loadFromFile("Resources/shader/trans.frag", sf::Shader::Type::Fragment))
			throw "Graphics::Transition::Failed to load transFade.rag";

		shader.setUniform("currentScreen", currentScreen.getTexture());
		shader.setUniform("frozenScreen", this->frozenBuffer->getTexture());
		shader.setUniform("transMap", transMap);
		shader.setUniform("vague", vague / 256.f);
	}

	window->pushGLStates();

	auto frames = static_cast<int>(duration / Game::getInstance()->deltaTime());
	for (auto i = 0; i < frames; ++i) {
		const float prog = 1.f * i / frames;
		shader.setUniform("prog", prog);

		window->clear();
		sf::Sprite sprite(currentScreen.getTexture());
		window->draw(sprite, &shader);
		window->display();

		Game::getInstance()->updateSFMLEvents();
	}

	window->popGLStates();
	this->transitionInfo.ready = false;
	this->frozen = false;
}

void Graphics::FadeCore() {
	if (!this->fadeInfo.fading) return;

	auto duration = this->fadeInfo.duration;
	auto isin = this->fadeInfo.fadeIn;
	auto progress = this->fadeInfo.progress;

	auto window = Game::getWindow();
	auto frames = static_cast<int>(duration / Game::getInstance()->deltaTime());

	if (this->frozen) {
		auto size = this->frozenBuffer->getSize();

		for (auto i = 0; i < frames; i++) {
			const int prog = static_cast<int>(255.f * i / frames);
			this->setBrightness(isin ? prog : 255 - prog);

			window->clear();
			sf::Sprite sprite(this->frozenBuffer->getTexture());
			sprite.setOrigin(0, static_cast<float>(size.y));
			sprite.setScale(1.f, -1.f);
			window->draw(sprite);

			this->PresentCore();

			window->display();

			Game::getInstance()->updateSFMLEvents();
		}
		this->fadeInfo.fading = false;
		this->frozen = false;
	}
	else {
		this->fadeInfo.progress++;

		const int prog = static_cast<int>(255.f * this->fadeInfo.progress / frames);
		this->setBrightness(isin ? prog : 255 - prog);

		if (this->fadeInfo.progress >= frames)
			this->fadeInfo.fading = false;
	}
}
