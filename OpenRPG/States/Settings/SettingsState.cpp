#include "stdafx.h"

#include "Game/Game.h"
#include "GUI/Gui.h"
#include "SettingsState.h"
#include "States/MainMenu/MainMenuState.h"

void SettingsState::initVariables() {
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts() {
	if (!this->font.loadFromFile("Fonts/R2.ttc")) {
		throw "메인메뉴 폰트로딩 실패";
	}
}

void SettingsState::initKeybinds() {
	auto supportedKeys = Game::getInstance()->getSupportedKeys();

	std::ifstream ifs("Config/editor_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		int key_value = 0;
		while (ifs >> key >> key2) {
			this->keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void SettingsState::initGui() {
	if (!tx.loadFromFile("Resources/image/Buttons/btn1.png"))
		throw "btn";

	this->buttons["BACK"] = new gui::Button(
		100, 800, 250, 200, &tx, &this->font, L"뒤로가기", 50, sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50), sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));

	this->buttons["APPLY"] = new gui::Button(
		400, 800, 250, 200, &tx, &this->font, L"적용", 50, sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50), sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));

	std::vector<std::wstring> modes_str;
	for (auto &i : this->modes) {
		modes_str.push_back(std::to_wstring(i.width) + L'x' + std::to_wstring(i.height));
	}

	this->dropDownLists["RESOLUTION"] =
		new gui::DropDownList(400, 100, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText() {
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n ");
}

void SettingsState::initBackground() {}

void SettingsState::onEnter() {
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

void SettingsState::onLeave() {
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	for (auto it = this->dropDownLists.begin(); it != this->dropDownLists.end(); ++it)
		delete it->second;
}

void SettingsState::updateInput(const float &dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		StateManager::getInstance()->GoTo(new MainMenuState(), [](State *state) { delete state; });
		return;
	}
}

void SettingsState::updateGui() {
	auto dt = Game::getInstance()->frameTime();

	//모든 버튼들의 상태를 기능에맞게 업데이트해줌
	for (auto &it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	//게임종료
	if (this->buttons["BACK"]->isPressed()) {
		StateManager::getInstance()->GoTo(new MainMenuState(), [](State *state) { delete state; });
		return;
	}

	if (this->buttons["APPLY"]->isPressed()) {
		auto window = Game::getInstance()->getWindow();

		//삭제예정 테스트용 설정이날아가기때문에 프레임이 솓구칩니다.
		window->create(
			this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()], "Test",
			sf::Style::Default);
		window->setFramerateLimit(120);
	}

	//드랍다운리스트
	for (auto &it : this->dropDownLists) {
		it.second->update(this->mousePosView, dt);
	}
}

void SettingsState::update() {
	State::update();

	auto dt = Game::getInstance()->frameTime();

	this->updateMousePositions();
	this->updateInput(dt); // TODO 여기서 delete 되고

	this->updateGui(); // TODO 여기서 오류
}

void SettingsState::renderGui(sf::RenderTarget *target) {
	for (auto &it : this->buttons) {
		it.second->render(target);
	}

	for (auto &it : this->dropDownLists) {
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget *target) {
	State::render(target);

	if (!target)
		target = Game::getInstance()->getWindow();

	this->renderGui(target);
	target->draw(this->optionsText);

	//삭제예정. 디버깅용. 마우스위에 좌표표시
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 15));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(15);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}