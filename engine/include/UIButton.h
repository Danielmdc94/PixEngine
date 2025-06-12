#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>

class UIButton : public UIElement {
public:
	using Callback = std::function<void()>;

	UIButton();

	void SetSize(const sf::Vector2f& l_size);
	void SetText(const std::string& l_text, const sf::Font& l_font, unsigned int l_charSize);
	void SetCallback(Callback l_callback);

	void Update(const sf::Time& l_deltaTime) override;
	void Draw(sf::RenderTarget& l_target) override;

	bool Contains(const sf::Vector2f& l_point) const override;

	void OnClick();

private:
	void CenterText();

	sf::RectangleShape m_shape;
	sf::Text m_text;
	Callback m_callback;
};
