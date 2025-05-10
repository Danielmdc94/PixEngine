#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

class Rectangle : public sf::Transformable
{
public:
    Rectangle(sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
    virtual ~Rectangle() {}

    bool collidesWith(Rectangle pOther);

    sf::Vector2f getCenter();

    void setSize(sf::Vector2f size) { m_size = size; }
    sf::Vector2f getSize() const { return m_size; }

    void setColor(sf::Color color) { m_color = color; }
    sf::Color getColor() const { return m_color; }

    sf::RectangleShape GetShape() { return m_shape; };

private:
    sf::Color m_color = sf::Color::White;
    sf::RectangleShape m_shape;
    sf::Vector2f m_size;
};
