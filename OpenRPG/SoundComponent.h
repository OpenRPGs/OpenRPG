#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include <iostream>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"

class SoundComponent
{
	sf::Sound sound;

public:
	void initSoundComponent(sf::SoundBuffer &buffer, bool loop);
	void pause();
	void playSound();
	void stop();

	SoundComponent(sf::SoundBuffer &buffer, bool loop);
	~SoundComponent();
};

#endif