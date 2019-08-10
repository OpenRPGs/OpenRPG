#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/R2.ttc"))
	{
		throw("메인메뉴 폰트로딩 실패");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		int key_value = 0;
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();

	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	:State(window, supportedKeys)
{
	this->initFonts();
	this->initKeybinds();

	this->gamestate_btn = new Button(100,100,150,50, 
		&this->font, L"한글 기능 추가 완료!",
		sf::Color(70,70,70,200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	this->background.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
	delete this->gamestate_btn;
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState! " << std::endl;
}

void MainMenuState::updateInput(const float & dt)
{
	this->checkForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		this->background.setFillColor(sf::Color::Cyan);
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->gamestate_btn->update(this->mousePosView);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->gamestate_btn->render(target);
}
