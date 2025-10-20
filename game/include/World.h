#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "BaseState.h"

class World
{
public:
	World(BaseState* l_owner) : m_owner(l_owner), m_tileSize(64) {}

	~World() = default;

	void OnCreate();
	void OnDestroy();

	void Draw(sf::RenderWindow* l_window);
	void Update(sf::Time l_deltaTime);

	float GetGridSize() const { return m_tileSize; }
	BaseState* GetOwner() const { return m_owner; }
	
	void SetGridSize(float l_gridSize) { m_tileSize = l_gridSize; }


protected:
	BaseState* m_owner;
	
private:
	sf::RectangleShape m_tileSelector;
	float m_tileSize;
	sf::Vector2i m_mapSize;
	std::vector<std::vector<sf::RectangleShape>> m_tileMap;
};
