#pragma once

#include "State.h"
#include "StateManager.h"

enum class ItemType
{
	ArmorUpgrade, Bow, Arrow, Shield, Potion
};

struct StoreItem
{
	ItemType m_type;
	int m_price;

	sf::Sprite m_sprite;
	sf::Text m_text;
	sf::FloatRect m_rect;
	sf::RectangleShape m_shape;

};

class State_Store : public State
{
public:
	State_Store(StateManager* l_stateManager) : State(l_stateManager) {}
	
	void OnCreate() override;
	void OnDestroy() override;
	void Activate() override;
	void Deactivate() override;
	void Update(const sf::Time& l_deltaTime) override;
	void Draw() override;

	void BuyItem(sf::Vector2i l_mousePosition);

	void DrawItem(StoreItem* l_item, int l_order);

	void Close();

private:
	sf::RectangleShape m_rectBackground;
	sf::Text m_textTitle;
	sf::Text m_textContinue;
	sf::Font m_font;

	StoreItem m_bowItem;
	StoreItem m_armorItem;
	StoreItem m_arrowItem;
	StoreItem m_shieldItem;
	StoreItem m_potionItem;
};