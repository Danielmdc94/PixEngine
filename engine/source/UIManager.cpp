#include "../include/UIManager.h"

UIManager::UIManager(SharedContext* l_context) : m_context(l_context)
{

}

UIManager::~UIManager()
{

}

void UIManager::Update(const sf::Time& l_deltaTime)
{
	for (auto* element : m_elementOrder)
	{
		if (element->IsActive())
		{
			element->Update(l_deltaTime);
		}
	}
}

void UIManager::Draw()
{
	for (auto* element : m_elementOrder)
	{
		if (element->IsVisible())
		{
			element->Draw();
		}
	}
}

SharedContext* UIManager::GetContext()
{
	return m_context;
}

UIElement* UIManager::GetElement(const std::string& l_id)
{
	auto it = m_elements.find(l_id);
	if (it != m_elements.end()) {
		return it->second.get();
	}
	return nullptr;
}

bool UIManager::HasElement(const std::string& l_id) const
{
	return m_elements.find(l_id) != m_elements.end();
}


void UIManager::RemoveElement(const std::string& l_id)
{
	if (!HasElement(l_id))
	{
		return;
	}

	UIElement* elementPtr = m_elements[l_id].get();

	auto newEnd = std::remove(m_elementOrder.begin(), m_elementOrder.end(), elementPtr);
	m_elementOrder.erase(newEnd, m_elementOrder.end());

	m_elements.erase(l_id);
}
