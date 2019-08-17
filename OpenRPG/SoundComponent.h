#pragma once

#include <iostream>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

class SoundComponent
{
	sf::Sound mysound;
	sf::SoundBuffer buffer;

public:
	void initSoundComponent(const std::string &filename);
	void pause();
	void playSound();
	void stop();

	SoundComponent(const std::string &filename);
	~SoundComponent();
};

