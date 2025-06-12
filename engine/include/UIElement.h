#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class UILayer;

class UIElement {
public:
    UIElement() : m_isVisible(true), m_isActive(true), m_isHovered(false), m_isClicked(false) {}
    virtual ~UIElement() = default;

    virtual void Update(const sf::Time& l_deltaTime) = 0;
    virtual void Draw(sf::RenderTarget& l_target) = 0;
    
    void SetPosition(const sf::Vector2f& l_position) { m_position = l_position; }
    const sf::Vector2f& GetPosition() const { return m_position; }
    
    void SetVisible(bool l_visible) { m_isVisible = l_visible; }
    bool IsVisible() const { return m_isVisible; }
    
    void SetActive(bool l_active) { m_isActive = l_active; }
    bool IsActive() const { return m_isActive; }

    void SetHovered(bool l_hovered) { m_isHovered = l_hovered; }
    bool IsHovered() const { return m_isHovered; }

    void SetClicked(bool l_clicked) { m_isClicked = l_clicked; }
    bool IsClicked() const { return m_isClicked; }

    virtual bool Contains(const sf::Vector2f& l_point) const = 0;

protected:
    sf::Vector2f m_position;
    bool m_isVisible;
    bool m_isActive;
    bool m_isHovered;
    bool m_isClicked;
};

