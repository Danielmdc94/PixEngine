#pragma once

#include <SFML/Graphics.hpp>

#include "../include/ResourceManager.h"

class FontManager : public ResourceManager<FontManager, sf::Font>
{
public:
	FontManager() : ResourceManager("Fonts.cfg") {}

	sf::Font* Load(const std::string& l_path)
	{
		sf::Font* font = new sf::Font();
		if (!font->loadFromFile(Utils::GetEngineResourceDirectory() + "Fonts/" + l_path))
		{
			delete font;
			font = nullptr;
			std::cerr << "! Failed to load font: " << l_path << '\n';
		}
		return font;
	}
};