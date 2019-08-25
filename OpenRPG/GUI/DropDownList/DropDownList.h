#pragma once

namespace gui {

class DropDownList {
  private:
	float keytime;
	float keytimeMax;

	g::safe<sf::Font> font;

	g::safe<gui::Button> activeElement;
	g::safevector<gui::Button> list;

	bool showList;

  public:
	//생성자 소멸자
	DropDownList(
		float x, float y, float width, float height, g::safe<sf::Font> font, std::wstring list[],
		unsigned numOfElements, const unsigned default_index = 0);
	~DropDownList();

	const unsigned short getActiveElementId() const;

	//함수
	const bool getKeytime();
	void updateKeytime(const float dt);
	void update(const sf::Vector2f mousePos, const float dt);
	void render(sf::RenderTarget* target);
};

} // namespace gui