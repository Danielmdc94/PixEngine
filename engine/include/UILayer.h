#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "UIButton.h"

class UILayer {
public:
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

    void HandleMouseMove(const sf::Vector2f& l_mousePos);
    void HandleClick(const sf::Vector2f& l_mousePos);

    void Clear();

private:
    std::vector<std::unique_ptr<UIElement>> m_elements;
};
