#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "UIElement.h"
#include "UIButton.h"

class BaseState;
enum class StateType;

class UILayer {
public:
    UILayer(BaseState* l_owner) : m_owner(l_owner) {}
    virtual ~UILayer() = default;

    virtual void OnCreate();
    virtual void OnDestroy();
    
    template<typename T, typename... Args>
    T* CreateElement(Args&&... l_args) {
        static_assert(std::is_base_of<UIElement, T>::value, "T must inherit from UIElement");
        auto element = std::make_unique<T>(std::forward<Args>(l_args)...);
        T* ptr = element.get();
        m_elements.push_back(std::move(element));
        return ptr;
    }

    void Update(const sf::Time& l_deltaTime);
    void Draw(sf::RenderTarget& l_target);

    BaseState* GetOwner() const { return m_owner; }

    void HandleClick(EventDetails* l_details);
    void HandleMouseMove(EventDetails* l_details);

    void Clear();
    
protected:
    BaseState* m_owner;
    
    std::vector<std::unique_ptr<UIElement>> m_elements;
};
