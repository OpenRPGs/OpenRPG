#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State
{
private:
	
protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::SoundBuffer> sounds;
	std::map<std::string,sf::Texture> textures;

	//함수
	virtual void initKeybinds() = 0;
	void initSounds();

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	void endState();
	
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePositions();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};
#endif
