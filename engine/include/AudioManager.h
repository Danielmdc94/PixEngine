#pragma once

#include <SFML/Audio.hpp>

#include "../include/ResourceManager.h"

class AudioManager : public ResourceManager<AudioManager, sf::Music>
{
public:
	AudioManager() : ResourceManager("Audio.cfg") {}

	sf::Music* Load(const std::string& l_path)
	{
		sf::Music* audio = new sf::Music();
		if (!audio->openFromFile(Utils::GetEngineResourceDirectory() + "audio/" + l_path))
		{
			delete audio;
			audio = nullptr;
			std::cerr << "! Failed to load audio file: " << l_path << '\n';
		}
		return audio;
	}
};