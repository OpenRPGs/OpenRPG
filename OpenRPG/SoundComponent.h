#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

class SoundComponent
{
	sf::Sound sound;

public:
	void initSoundComponent(sf::SoundBuffer &buffer, bool loop);
	void pause();
	void playSound();
	void stop();

	SoundComponent(sf::SoundBuffer &buffer, bool loop);
	virtual ~SoundComponent();
};

#endif