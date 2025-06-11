#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class UILayer;

class UIElement {
public:
    UIElement() : m_isVisible(true), m_isActive(true) {}
    virtual ~UIElement() = default;

    virtual void Update(const sf::Time& deltaTime) = 0;
    virtual void Draw(sf::RenderTarget& target) = 0;
    
    void SetPosition(const sf::Vector2f& position) { m_position = position; }
    const sf::Vector2f& GetPosition() const { return m_position; }
    
    void SetVisible(bool visible) { m_isVisible = visible; }
    bool IsVisible() const { return m_isVisible; }
    
    void SetActive(bool active) { m_isActive = active; }
    bool IsActive() const { return m_isActive; }

    virtual bool Contains(const sf::Vector2f& point) const = 0;

protected:
    sf::Vector2f m_position;
    bool m_isVisible;
    bool m_isActive;
};

