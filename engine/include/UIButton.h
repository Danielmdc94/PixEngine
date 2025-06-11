#pragma once

#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class UIButton : public UIElement {
public:
	using Callback = std::function<void()>;

	UIButton();

	void SetSize(const sf::Vector2f& size);
	void SetText(const std::string& text, const sf::Font& font);
	void SetCallback(Callback callback);

	void Update(const sf::Time& deltaTime) override;
	void Draw(sf::RenderTarget& target) override;

	bool Contains(const sf::Vector2f& point) const override;

	void OnHover(bool isHovered);
	void OnClick();

private:
	void CenterText();

	sf::RectangleShape m_shape;
	sf::Text m_text;
	bool m_isHovered;
	Callback m_callback;
};
