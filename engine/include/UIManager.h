#pragma once

#include "SharedContext.h"
#include "UIElement.h"
#include <memory>
#include <unordered_map>


enum class UIElementType
{
    Button = 0, Panel
};

using UIElementContainer = std::unordered_map<std::string, std::unique_ptr<UIElement>>;

class UIManager
{
public:
    UIManager(SharedContext* l_context);
    ~UIManager();
    
    void Update(const sf::Time& l_deltaTime);
    void Draw();

    SharedContext* GetContext();
    
    template<typename T>
T* CreateElement(const std::string& l_id, int renderOrder = -1)
    {
        if (HasElement(l_id)) {
            return nullptr;
        }
        auto element = std::make_unique<T>(this);
        T* elementPtr = element.get();
        m_elements[l_id] = std::move(element);
        if (renderOrder < 0)
        {
            m_elementOrder.push_back(elementPtr);
        }
        else
        {
            auto it = m_elementOrder.begin() + std::min(renderOrder, (int)m_elementOrder.size());
            m_elementOrder.insert(it, elementPtr);
        }
        elementPtr->OnCreate();
        return elementPtr;
    }

    std::vector<UIElement*>* GetElements();

    UIElement* GetElement(const std::string& l_id);
    bool HasElement(const std::string& l_id) const;
    void RemoveElement(const std::string& l_id);
    
private:
    SharedContext* m_context;

    UIElementContainer m_elements;
    std::vector<UIElement*> m_elementOrder;
};
