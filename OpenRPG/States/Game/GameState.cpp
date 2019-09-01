#include "stdafx.h"

#include "Game/Game.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "GUI/Gui.h"
#include "GUI/PauseMenu.h"
#include "States/State.h"
#include "GameState.h"	

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height)
	);
}

void GameState::initVariable()
{
	this->fadInFlag = true;
	this->backGroundColor = 255.f;
}

void GameState::initBackground() {
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));

	this->background.setFillColor(sf::Color::Transparent);
}

//Initializer functions
void GameState::initButtons()
{
	if (!btnTexure.loadFromFile("Resources/image/Buttons/btn1.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
}

void GameState::initKeybinds()
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

void GameState::initTextures()
{
	//초록색 : walk_sprite  중세시대기사 : PLAYER_SHEET
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/image/Sprites/Player/walk_sprite.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/R2.ttc"))
	{
		throw("메인메뉴 폰트로딩 실패");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 800.f, L"메인으로", this->btnTexure);
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}


void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/map/sheet.png");
	this->tileMap->loadFromFile("text.slmp");
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width / 2.f,
			this->stateData->gfxSettings->resolution.height / 2.f
		)
	);

}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"], window_focus);
}

//Constructors / Destructors
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initVariable();
	this->initButtons();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
	this->initBackground();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pmenu;
	delete this->tileMap;
}


void GameState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}



//Update functions

void GameState::updatePauseButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float & dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player);
}

void GameState::updateFadeIn(float time)
{
	auto dt = Game::getInstance()->deltaTime();
	if (fadInFlag)
	{
		std::cout << backGroundColor << std::endl;
		this->backGroundColor -= (dt * time);
		this->background.setFillColor(sf::Color(0.f, 0.f, 0.f, this->backGroundColor));
		if (backGroundColor < 0.f)
		{
			fadInFlag = false;
			backGroundColor = 255.f;
		}
	}
}

void GameState::updatePlayerInput(const float & dt)
{
	if (this->window->hasFocus()) {
		//사용자 입력 업데이트
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
			this->player->move(-2.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
			this->player->move(2.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
			this->player->move(0.f, -2.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
			this->player->move(0.f, 2.f, dt);
	}
}

void GameState::update()
{
	auto dt = Game::getInstance()->deltaTime();

	//윈도우 활성체크
	window_focus = this->window->hasFocus();

	this->updateMousePositions(&this->view); //일시정지든 아니든 마우스는 사용가능해야함
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateFadeIn(100.f);
	this->updatePauseButtons();

	if (!this->paused) // 일시정지가 걸려있지않으면 모두 업데이트를 진행한다.
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->player->update(dt);

		this->updateTileMap(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseButtons();
	}
}


//Render

void GameState::render(sf::RenderTarget* target)
{

	if (!target)
		target = this->window;
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture);

	this->player->render(this->renderTexture);

	if (this->paused)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
		
	}

	 //최종랜더링
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
	target->draw(this->background);//페이드인효과
}

