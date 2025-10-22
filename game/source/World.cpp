#include "World.h"

#include "StateManager.h"

void World::OnCreate()
{
	m_mapSize = sf::Vector2i(64, 32);
	m_tileSize = 64.f;
	m_tileMap2 = new TileMap(m_mapSize.x, m_mapSize.y, static_cast<unsigned>(m_tileSize));
	//m_owner->GetStateManager()->GetContext()->m_textureManager->RequireResource("BrickTile");
	m_tileMap2->LoadFromFile("Map.txt", nullptr);
	//Tile groundTile(m_owner->GetStateManager()->GetContext()->m_textureManager->GetResource("BrickTile"), sf::IntRect(0, 0, 250, 250), true, 1);
	//for (unsigned x = 0; x < m_tileMap2->GetWidth(); ++x)m_tileMap2->SetTile(x, m_tileMap2->GetHeight() - 1, groundTile);

	
	m_tileMap.resize(m_mapSize.x, std::vector<sf::RectangleShape>());
	for (int x = 0; x < m_mapSize.x; ++x)
	{
		m_tileMap[x].resize(m_mapSize.y, sf::RectangleShape());
		for (int y = 0; y < m_mapSize.y; ++y)
		{
			m_tileMap[x][y].setSize({m_tileSize, m_tileSize});
			m_tileMap[x][y].setFillColor(sf::Color::Transparent);
			m_tileMap[x][y].setOutlineColor(sf::Color::White);
			m_tileMap[x][y].setOutlineThickness(1.f);
			m_tileMap[x][y].setPosition(x * m_tileSize, y * m_tileSize);
		}
	}

	

	
	m_tileSelector.setSize({m_tileSize, m_tileSize});
	m_tileSelector.setFillColor(sf::Color::Transparent);
	m_tileSelector.setOutlineColor(sf::Color::Green);
	m_tileSelector.setOutlineThickness(2.f);
	m_tileSelector.setPosition(0.f, 0.f);
}

void World::OnDestroy()
{
	m_tileMap.clear();
}

void World::Draw(sf::RenderWindow* l_window)
{
	for (int x = std::max((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).x) / 64) - 3, 0); x < std::min((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).x) / 64) + 4, m_mapSize.x); ++x)
	{
		m_tileMap[x].resize(m_mapSize.y, sf::RectangleShape());
		for (int y = std::max((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).y) / 64) - 3, 0); y < std::min((int(m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(l_window).y) / 64) + 4, m_mapSize.y ); ++y)
		{
			l_window->draw(m_tileMap[x][y]);
		}
	}
	
	l_window->draw(m_tileSelector);
	m_tileMap2->Draw(l_window);
}

void World::Update(sf::Time l_deltaTime)
{
	sf::RenderWindow* window = m_owner->GetStateManager()->GetContext()->m_window->GetRenderWindow();
	sf::Vector2f mouseWorld = m_owner->GetStateManager()->GetContext()->m_eventManager->GetMousePositionView(window);

	const float size = m_tileSize;
	sf::Vector2f snapped(std::floor(mouseWorld.x / size) * size, std::floor(mouseWorld.y / size) * size);
	m_tileSelector.setPosition(snapped);

}
