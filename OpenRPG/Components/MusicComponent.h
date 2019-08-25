#pragma once

class MusicComponent {
  private:
	g::safe<sf::Music> music;

  public:
	bool Loaded();
	
	MusicComponent *play();
	MusicComponent *pause();
	MusicComponent *stop();

	bool isPlaying();

	MusicComponent *setVolume(float volume);
	float getVolume();

	MusicComponent *setOffset(int msec);
	int getOffset();

	MusicComponent *setLoop(bool loop);
	bool getLoop();

	MusicComponent(const std::string &path);
	virtual ~MusicComponent();

	MusicComponent *reset(const std::string& path);
};
