#include "EditorState.h"


//Initaillizer functions
void EditorState::initVariables()
{

}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/R2.ttc"))
	{
		throw("���θ޴� ��Ʈ�ε� ����");
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
	this->buttons["GAME_STATE"] = new Button(950, 100, 250, 70,
		&this->font, L"(������) �ʼ���, ĳ���͹�ġ ��� ", 50,
		sf::Color(255, 0, 0, 255), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void EditorState::initBackground()
{
}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons()
{
	//��� ��ư���� ���¸� ��ɿ��°� ������Ʈ����
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();


}

void EditorState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderButtons(target);

	//��������. ������.
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 15));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(15);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}