#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

enum button_state{ BTN_IDLE = 0, BTN_ACTIVE, BTN_HOVER };

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Texture buttonTexture;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
		sf::Texture* buttonTexture , sf::Font* font, std::wstring text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color);
	~Button();
	//접근자
	const bool isPressed() const;
	//함수
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

#endif 

