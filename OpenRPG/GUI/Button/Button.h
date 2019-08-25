#pragma once

enum button_state { BTN_IDLE = 0, BTN_ACTIVE, BTN_HOVER };

namespace gui {

class Button {
  private:
	short unsigned buttonState;
	short unsigned id;

	sf::RectangleShape shape;
	// sf::Texture buttonTexture;
	// sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

  public:
	//텍스쳐버튼생성자
	Button(
		float x, float y, float width, float height, g::safe<sf::Texture> buttonTexture,
		g::safe<sf::Font> font, std::wstring text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color);

	//기본버튼생성자
	Button(
		float x, float y, float width, float height, g::safe<sf::Font> font, std::wstring text,
		unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color,
		sf::Color text_active_color, sf::Color idle_Color, sf::Color hover_Color,
		sf::Color active_Color, sf::Color outline_idle_Color = sf::Color::Transparent,
		sf::Color outline_hover_Color = sf::Color::Transparent,
		sf::Color outline_active_Color = sf::Color::Transparent, short unsigned id = 0);

	~Button();

	//접근자
	const bool isPressed() const;
	const std::string getText() const;
	const short unsigned getId() const;

	void setText(const std::string text);
	void setId(const short unsigned id);

	//함수
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

} // namespace gui