#include "UILayer.h"

#include "StateManager.h"

void UILayer::OnCreate()
{
    EventManager* eventManager = m_owner->GetStateManager()->GetContext()->m_eventManager;

    m_boundState = eventManager->GetCurrentState();
        
    eventManager->AddCallback(m_boundState, "LMouse_Down", &UILayer::HandleLMouseDown, this);
    eventManager->AddCallback(m_boundState, "LMouse_Up", &UILayer::HandleLMouseUp, this);
    eventManager->AddCallback(m_boundState, "Mouse_Move", &UILayer::HandleMouseMove, this);

    m_callbacksBound = true;
    //std::cout << "UILayer created! boundState=" << static_cast<int>(m_boundState) << " this=" << this << "\n";
}

void UILayer::OnDestroy()
{
    UnbindCallbacks();
    Clear();
}

void UILayer::UnbindCallbacks()
{
    if (!m_callbacksBound)
    {
        return;
    }

    EventManager* eventManager = m_owner->GetStateManager()->GetContext()->m_eventManager;

    eventManager->RemoveCallback(m_boundState, "LMouse_Down");
    eventManager->RemoveCallback(m_boundState, "LMouse_Up");
    eventManager->RemoveCallback(m_boundState, "Mouse_Move");

    m_callbacksBound = false;
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
    m_elements.shrink_to_fit();
}
