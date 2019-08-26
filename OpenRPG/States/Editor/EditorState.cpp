#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "States/State.h"
#include "EditorState.h"

//Initaillizer functions
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/R2.ttc"))
	{
		throw("메인메뉴 폰트로딩 실패");
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editor_keybinds.ini");

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

}

void EditorState::initButtons()
{
	if (!tx.loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "btn";

	//this->buttons["EXIT_STATE"] = new gui::Button(
	//	250, 100, 1250, 80,
	//	tx, this->font, L"(에디터) 맵수정, 캐릭터배치 등등 ", 50,
	//	sf::Color(0, 0, 0, 255), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
	//	sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));
}

void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(15);
	this->cursorText.setFillColor(sf::Color::Red);
	this->cursorText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 30));
}

void EditorState::initBackground()
{
}


void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 800.f, "Quit", this->tx);
}

void EditorState::initGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);
	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, this->stateData->gridSize, this->tileMap->getTileSheet());
}


void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}


EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;
	delete this->tileMap;
	delete this->textureSelector;
}


//함수


void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput(const float & dt)
{
	//타일 맵 추가하기
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->getKeytime())
	{
		if (this->textureRect.left < 300)
		{
			this->textureRect.left += 100;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->getKeytime())
	{
		if (this->textureRect.left > 0)
		{
			this->textureRect.left -= 100;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->getKeytime())
	{
		if (this->textureRect.top < 200)
		{
			this->textureRect.top += 100;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->getKeytime())
	{
		if (this->textureRect.top > 0)
		{
			this->textureRect.top -= 100;
		}
	}
}

void EditorState::updateButtons()
{
	////모든 버튼들의 상태를 기능에맞게 업데이트해줌
	//for (auto &it : this->buttons)
	//{
	//	it.second->update(this->mousePosView);
	//}

	//if (this->buttons["EXIT_STATE"]->isPressed())
	//{
	//	this->endState();
	//}
}

void EditorState::updateGui()
{
	this->selectorRect.setTextureRect(this->textureRect);
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y* this->stateData->gridSize);

	this->cursorText.setPosition(sf::Vector2f(this->mousePosView.x + 100.f, this->mousePosView.y - 30));
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		'\n'<<this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		'\n' << this->textureRect.left << " " << this->textureRect.top;
	cursorText.setString(ss.str());

	this->textureSelector->update(this->mousePosWindow);
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::update()
{
	auto dt = Game::getInstance()->deltaTime();

	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateButtons();
		this->updateGui();
		this->updateEditorInput(dt);
	}
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget & target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget & target)
{
	target.draw(this->selectorRect);
	this->textureSelector->render(target);
	target.draw(this->cursorText);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->tileMap->render(*target);

	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused) {
		this->pmenu->render(*target);
	}


}