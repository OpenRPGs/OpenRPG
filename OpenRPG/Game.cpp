#include "Game.h"

// �����Լ�

// �ʱ�ȭ �Լ�

void Game::initWindow()
{
	//SFML ������â ���� Todo : window.ini���Ϸ� �ʱ�ȭ�ҿ���
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "OpenRPG C++ !");
}

//���� �� �Ҹ��Լ�
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

//�Լ� 
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
