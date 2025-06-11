#include "UILayer.h"

void UILayer::Update(const sf::Time& deltaTime)
{
    for (auto& element : m_elements)
    {
        if (element->IsActive())
        {
            element->Update(deltaTime);
        }
    }
}

void UILayer::Draw(sf::RenderTarget& target)
{
    for (auto& element : m_elements)
    {
        if (element->IsVisible())
        {
            element->Draw(target);
        }
    }
}

void UILayer::HandleMouseMove(const sf::Vector2f& mousePos)
{
    for (auto& element : m_elements)
    {
        if (auto* button = dynamic_cast<UIButton*>(element.get()))
        {
            button->OnHover(button->Contains(mousePos));
        }
    }
}

void UILayer::HandleClick(const sf::Vector2f& mousePos)
{
    for (auto& element : m_elements)
    {
        if (auto* button = dynamic_cast<UIButton*>(element.get()))
        {
            if (button->Contains(mousePos))
            {
                button->OnClick();
                break;
            }
        }
    }
}

void UILayer::Clear()
{
    m_elements.clear();
}
