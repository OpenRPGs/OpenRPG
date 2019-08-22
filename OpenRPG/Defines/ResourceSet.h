#pragma once

class ResourceSet {
  public:
	g::safemap<sf::Texture> Textures;
	g::safemap<sf::SoundBuffer> Sounds;
};
