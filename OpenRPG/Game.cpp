#include "Game.h"

// 전역함수

// 초기화 함수

void Game::initWindow()
{
	//SFML 윈도우창 생성 Todo : window.ini파일로 초기화할예정
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "OpenRPG C++ !");
}

//생성 및 소멸함수
Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::updateDt()
{
	/*Updates the dt varialbe with the time it takes to update an render one frame*/

	this->dt = this->dtClock.restart().asSeconds();

	system("cls");
	std::cout << this -> dt << '\n';
}

//함수 
void Game::updateSFMLEvents()
{

	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();
	int sum = 0;
	//for (size_t i = 0; i < 10000; i++)
	//{
	//	sum += i;
	//}
}

void Game::render()
{
	this->window->clear();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
