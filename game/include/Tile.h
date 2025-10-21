#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Tile
{
public:
	Tile() : m_id(0), m_solid(false), m_useColor(false) {}

	Tile(sf::Texture* l_texture, const sf::IntRect& l_texRect, bool l_isSolid = false, unsigned l_id = 0) : m_solid(l_isSolid), m_id(l_id)
	{
		if (l_texture)
		{
			m_sprite.setTexture(*l_texture);
			m_sprite.setTextureRect(l_texRect);
			m_sprite.setScale(64.f / l_texRect.width, 64.f / l_texRect.height);
			m_useColor = false;
		}
		else
		{
			m_shape.setSize(sf::Vector2f(64.f, 64.f));
			m_useColor = true;
		}
	}

	// Disable copy to avoid copying SFML objects
	Tile(const Tile&) = delete;
	Tile& operator=(const Tile&) = delete;

	// Allow move
	Tile(Tile&&) = default;
	Tile& operator=(Tile&&) = default;

	virtual ~Tile() = default;

	void Draw(sf::RenderWindow* l_window)
	{
		if (m_useColor)
			l_window->draw(m_shape);
		else
			l_window->draw(m_sprite);
	}

	void SetColor(const sf::Color& l_color)
	{
		if (m_useColor)
			m_shape.setFillColor(l_color);
	}

	void SetPosition(float l_x, float l_y)
	{
		if (m_useColor)
			m_shape.setPosition(l_x, l_y);
		else
			m_sprite.setPosition(l_x, l_y);
	}

	sf::Sprite* GetSprite() { return &m_sprite; }
	unsigned GetID() const { return m_id; }
	bool IsSolid() const { return m_solid; }

private:
	unsigned m_id = 0;
	sf::Sprite m_sprite;
	sf::RectangleShape m_shape;
	bool m_solid = false;
	bool m_useColor = false;
};
