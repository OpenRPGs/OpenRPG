#pragma once

enum button_state { BTN_IDLE = 0, BTN_ACTIVE, BTN_HOVER };

namespace gui {
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
			sf::Texture* buttonTexture, sf::Font* font, std::wstring text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color);

		Button(float x, float y, float width, float height,
			sf::Font* font, std::wstring text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color);

		~Button();
		//접근자
		const bool isPressed() const;
		//함수
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

	};


	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		//생성자 소멸자
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::wstring list[], unsigned numOfElements, const unsigned default_index = 0);
		~DropDownList();


		//함수
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};
}
