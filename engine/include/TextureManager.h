#pragma once

#include <SFML/Graphics.hpp>

#include "../include/ResourceManager.h"

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager() : ResourceManager("Textures.cfg") {}

	sf::Texture* Load(const std::string& l_path)
	{
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile(Utils::GetEngineResourceDirectory() + "Textures/" + l_path))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "! Failed to load texture: " << l_path << std::endl;
		}
		return texture;
	}
};