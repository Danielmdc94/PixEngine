#include "UILayer.h"

#include "StateManager.h"

void UILayer::OnCreate()
{
    EventManager* eventManager = m_owner->GetStateManager()->GetContext()->m_eventManager;
    StateType currentState = eventManager->GetCurrentState();
        
    eventManager->AddCallback(currentState, "LMouse_Down", &UILayer::HandleLMouseDown, this);
    eventManager->AddCallback(currentState, "LMouse_Up", &UILayer::HandleLMouseUp, this);
    eventManager->AddCallback(currentState, "Mouse_Move", &UILayer::HandleMouseMove, this);
}

void UILayer::OnDestroy()
{
    EventManager* eventManager = m_owner->GetStateManager()->GetContext()->m_eventManager;
    StateType currentState = eventManager->GetCurrentState();
    
    eventManager->RemoveCallback(currentState, "LMouse_Down");
    eventManager->RemoveCallback(currentState, "LMouse_Up");
    eventManager->RemoveCallback(currentState, "Mouse_Move");

    Clear();
}

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

void UILayer::HandleLMouseDown(EventDetails* l_details)
{
    for (auto& element : m_elements)
    {
        if (auto* button = dynamic_cast<UIButton*>(element.get()))
        {
            if (button->Contains(l_details->m_mouse))
            {
                button->OnLMouseDown();
                break;
            }
        }
    }
}

void UILayer::HandleLMouseUp(EventDetails* l_details)
{
    for (auto& element : m_elements)
    {
        if (auto* button = dynamic_cast<UIButton*>(element.get()))
        {
            if (button->Contains(l_details->m_mouse))
            {
                button->OnLMouseUp();
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
                button->SetHovered(true);
                break;
            }
            button->SetHovered(false);
            button->SetClicked(false);
        }
    }
}

void UILayer::Clear()
{
    m_elements.clear();
}
