#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "UIButton.h"

class UILayer {
public:
    template<typename T, typename... Args>
    T* CreateElement(Args&&... args) {
        static_assert(std::is_base_of<UIElement, T>::value, "T must inherit from UIElement");
        auto element = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = element.get();
        m_elements.push_back(std::move(element));
        return ptr;
    }

    void Update(const sf::Time& deltaTime);
    void Draw(sf::RenderTarget& target);

    void HandleMouseMove(const sf::Vector2f& mousePos);
    void HandleClick(const sf::Vector2f& mousePos);

    void Clear();

private:
    std::vector<std::unique_ptr<UIElement>> m_elements;
};
