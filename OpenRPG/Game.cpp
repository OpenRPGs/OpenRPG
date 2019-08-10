#include "Game.h"

// �����Լ�

// �ʱ�ȭ �Լ�

void Game::initWindow()
{
	//SFML ������â ���� Todo : window.ini���Ϸ� �ʱ�ȭ�ҿ���(�Ϸ�)
	std::ifstream ifs("Config/window.ini");
	
	std::string title = "None";
	sf::VideoMode window_bounds(800,600);
	unsigned framerate_limit = 120;
	bool vertical_sync_enable = false;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enable;
	}
	ifs.close();

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enable);
}

void Game::initState()
{
	this->states.push(new GameState(this->window));
}

//���� �� �Ҹ��Լ�
Game::Game()
{
	this->initWindow();
	this->initState();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty()) 
	{
		delete this->states.top();
		this->states.pop();
	}
}


//�Լ� 
void Game::endApplication()
{
	std::cout << "Ending Application" << std::endl;
}

void Game::updateDt()
{
	/*Updates the dt varialbe with the time it takes to update an render one frame*/

	this->dt = this->dtClock.restart().asSeconds();
}

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

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else // ���α׷�����
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	//������ �׸���
	if (!this->states.empty())
		this->states.top()->render();

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
