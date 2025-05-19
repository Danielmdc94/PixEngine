#pragma once

#include <SFML/Graphics.hpp>

class UIManager;
enum class UIElementType;

class UIElement {
public:
    UIElement(UIManager* l_uiManager) : m_uiManager(l_uiManager), m_visible(true), m_active(true) {}
    virtual ~UIElement() = default;
    
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;
    virtual void Update(const sf::Time& l_deltaTime) = 0;
    virtual void Draw() = 0;

    UIManager* GetUIManager() { return m_uiManager; }
    
    void SetPosition(const sf::Vector2f& l_pos) { m_position = l_pos; }
    void SetVisible(const bool& l_visible) { m_visible = l_visible; }
    bool IsVisible()const { return m_visible; }
    void SetActive(const bool& l_active) { m_active = l_active; }
    bool IsActive()const { return m_active; }
    
protected:
    UIManager* m_uiManager;
    sf::Vector2f m_position;
    bool m_visible;
    bool m_active;
};
