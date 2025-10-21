#include "TileMap.h"

#include <iostream>

#include "Utilities.h"

TileMap::TileMap(unsigned l_width, unsigned l_height, unsigned l_tileSize) : m_width(l_width), m_height(l_height), m_tileSize(l_tileSize)
{
	
}

bool TileMap::LoadFromFile(const std::string& l_filename, sf::Texture* l_tileset, unsigned l_tileSize)
{
	std::ifstream file(Utils::GetGameResourceDirectory() + "maps/" + l_filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open tilemap file: " << l_filename << std::endl;
		return false;
	}

	m_tiles.clear();
	std::string line;
	unsigned y = 0;

	while (std::getline(file, line))
	{
		unsigned x = 0;
		for (char c : line)
		{
			unsigned id = c - '0';
			bool solid = (id == 1);
			auto tile = std::make_unique<Tile>(l_tileset, sf::IntRect(0, 0, 64, 64), solid, id);

			if (!l_tileset)
			{
				switch (id)
				{
				case 0: tile->SetColor(sf::Color::Transparent); break;	// floor
				case 1: tile->SetColor(sf::Color::White); break;		// wall
				case 2: tile->SetColor(sf::Color::Blue); break;			// player start
				case 3: tile->SetColor(sf::Color::Green); break;		// end
				case 4: tile->SetColor(sf::Color::Red); break;			// hazard
				}
			}

			tile->SetPosition(static_cast<float>(x * m_tileSize), static_cast<float>(y * m_tileSize));
			m_tiles.push_back(std::move(tile));
			++x;
		}
		++y;
	}

	return true;
}

Tile* TileMap::GetTile(unsigned l_x, unsigned l_y)
{
	if (l_x >= m_width || l_y >= m_height)
	{
		return nullptr;
	}
	return m_tiles[l_y * m_width + l_x].get();
}

void TileMap::Draw(sf::RenderWindow* l_window)
{
	for (auto& tile : m_tiles)
	{
		tile->Draw(l_window);
	}
}