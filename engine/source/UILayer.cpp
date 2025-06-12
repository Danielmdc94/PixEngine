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

void UILayer::HandleClick(EventDetails* l_details)
{
    for (auto& element : m_elements)
    {
        if (auto* button = dynamic_cast<UIButton*>(element.get()))
        {
            if (button->Contains(l_details->m_mouse))
            {
                button->OnClick();
                break;
            }
        }
    }
}

void UILayer::HandleMouseMove(EventDetails* l_details)
{
    for (auto& element : m_elements)
    {
        if (auto* button = dynamic_cast<UIButton*>(element.get()))
        {
            if (button->Contains(l_details->m_mouse))
            {
                button->OnHover(true);
                break;
            }
            button->OnHover(false);
        }
    }
}

void UILayer::Clear()
{
    m_elements.clear();
}
