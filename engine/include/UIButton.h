#pragma once

#include "UIElement.h"
#include "UIManager.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class UIButton : public UIElement
{
public:
	UIButton(UIManager* l_uiManager) : UIElement(l_uiManager) {}
	~UIButton() override = default;
	
	void OnCreate() override;
	void OnDestroy() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;

	void SetSize(const sf::Vector2f& l_size);
	void SetText(const std::string& l_text, const sf::Font& l_font, unsigned int l_charSize = 20);
	void SetCallback(std::function<void()> l_callback); 

	void OnClick();
	bool IsHovered(const sf::Vector2f& mousePos) const;

protected:
	sf::RectangleShape m_shape;
	sf::Text m_text;
	
	std::function<void()> m_callback;
};
