#pragma once
#include <fstream>
#include <vector>

#include "Tile.h"
#include "SFML/Graphics/RenderWindow.hpp"

class TileMap
{
public:
	TileMap(unsigned width, unsigned height, unsigned tileSize);

	bool LoadFromFile(const std::string& l_filename, sf::Texture* l_tileset = nullptr, unsigned l_tileSize = 64);
	Tile* GetTile(unsigned l_x, unsigned l_y);
	
	unsigned GetWidth() const { return m_width; }
	unsigned GetHeight() const { return m_height; }
	unsigned GetTileSize() const { return m_tileSize; }

	void Draw(sf::RenderWindow* l_window);

private:
	unsigned m_width;
	unsigned m_height;
	unsigned m_tileSize;

	std::vector<std::unique_ptr<Tile>> m_tiles;
};
