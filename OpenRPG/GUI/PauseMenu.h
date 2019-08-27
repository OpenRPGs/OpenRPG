#pragma once

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;
	


public:

	PauseMenu(sf::RenderWindow& window,sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::wstring text, sf::Texture& btnTexure);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

