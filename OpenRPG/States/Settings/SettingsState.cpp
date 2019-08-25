#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "Managers/StateManager.h"

#include "SettingsState.h"
#include "States/MainMenu/MainMenuState.h"

void SettingsState::initVariables() {
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts() {
	this->font = g::safe<sf::Font>(new sf::Font());
	if (!this->font->loadFromFile("Fonts/R2.ttc"))
		throw "메인메뉴 폰트로딩 실패";
}

void SettingsState::initKeybinds() {
	auto supportedKeys = Game::getInstance()->getSupportedKeys();

	std::ifstream ifs("Config/editor_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = supportedKeys->at(key2);
	}
	ifs.close();
}

void SettingsState::initGui() {
	this->tx = g::safe<sf::Texture>(new sf::Texture());
	if (!this->tx->loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "btn";

	this->buttons["BACK"] = g::safe<gui::Button>(new gui::Button(
		100, 800, 250, 200, this->tx, this->font, L"뒤로가기", 50, g::Color("#000"), g::Color("#969696fa"), g::Color("#14141432"),
		g::Color("#fff"), g::Color("#fff"), g::Color("#fff")));

	this->buttons["APPLY"] = g::safe<gui::Button>(new gui::Button(
		400, 800, 250, 200, this->tx, this->font, L"적용", 50, g::Color("#000"), g::Color("#969696fa"), g::Color("#14141432"),
		g::Color("#fff"), g::Color("#fff"), g::Color("#fff")));

	std::vector<std::wstring> modes_str;
	for (auto &i : this->modes)
		modes_str.push_back(std::to_wstring(i.width) + L'x' + std::to_wstring(i.height));

	this->dropDownLists["RESOLUTION"] =
		g::safe<gui::DropDownList>(new gui::DropDownList(400, 100, 200, 50, font, modes_str.data(), modes_str.size()));
}

void SettingsState::initText() {
	this->optionsText.setFont(*this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n ");
}

void SettingsState::initBackground() {}

SettingsState::SettingsState() : State() {
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}
SettingsState::~SettingsState() {}

void SettingsState::updateInput(const float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		StateManager::getInstance()->GoTo(SafeState(MainMenuState));
		return;
	}
}

void SettingsState::updateGui() {
	auto dt = Game::getInstance()->deltaTime();

	//모든 버튼들의 상태를 기능에맞게 업데이트해줌
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	//게임종료
	if (this->buttons["BACK"]->isPressed()) {
		StateManager::getInstance()->GoTo(SafeState(MainMenuState));
		return;
	}

	if (this->buttons["APPLY"]->isPressed()) {
		//삭제예정 테스트용 설정이날아가기때문에 프레임이 솓구칩니다.
		auto gfxSettings = Game::getGraphicsSettings();
		gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

		auto window = Game::getWindow();
		window->create(gfxSettings->resolution, gfxSettings->title, sf::Style::Default);
		window->setFramerateLimit(Game::getInstance()->getFramerate());
	}

	//드랍다운리스트
	for (auto &it : this->dropDownLists) {
		it.second->update(this->mousePosView, dt);
	}
}

void SettingsState::update() {
	State::update();

	auto dt = Game::getInstance()->deltaTime();

	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui();
}

void SettingsState::renderGui(sf::RenderTarget *target) {
	for (auto &it : this->buttons)
		it.second->render(target);

	for (auto &it : this->dropDownLists)
		it.second->render(target);
}

void SettingsState::render(sf::RenderTarget *target) {
	State::render(target);

	if (!target)
		target = Game::getWindow().get();

	this->renderGui(target);
	target->draw(this->optionsText);

	//삭제예정. 디버깅용. 마우스위에 좌표표시
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 15));
	mouseText.setFont(*this->font);
	mouseText.setCharacterSize(15);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}