#include "../include/State_Store.h"

void State_Store::OnCreate()
{
	m_type = StateType::Store;
	SetTransparent(true);
	SetTranscendent(true);
	sf::Vector2u windowSize = m_stateManager->GetContext()->m_window->GetRenderWindow()->getSize();
	TextureManager* textureManager = m_stateManager->GetContext()->m_textureManager;
	FontManager* fontManager = m_stateManager->GetContext()->m_fontManager;

	fontManager->RequireResource("MainFont");

	m_textTitle.setFont(*fontManager->GetResource("MainFont"));
	m_textTitle.setString(sf::String("Store"));
	m_textTitle.setCharacterSize(64);
	m_textTitle.setStyle(sf::Text::Bold);
	m_textTitle.setOutlineColor(sf::Color::Black);
	m_textTitle.setOutlineThickness(2.f);

	sf::FloatRect textRect = m_textTitle.getLocalBounds();
	m_textTitle.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_textTitle.setPosition(windowSize.x / 2.0f, windowSize.y / 16.0f);

	m_rectBackground.setSize(sf::Vector2f(windowSize));
	m_rectBackground.setPosition(0, 0);
	m_rectBackground.setFillColor(sf::Color(0, 0, 0, 50));

	//-----Bow Item
	m_bowItem.m_rect = sf::FloatRect(0, 0, 256, 256);
	m_bowItem.m_shape = sf::RectangleShape(sf::Vector2f(m_bowItem.m_rect.width, m_bowItem.m_rect.height));
	m_bowItem.m_shape.setFillColor(sf::Color(255, 255, 255, 50));
	m_bowItem.m_shape.setOutlineThickness(4);
	m_bowItem.m_shape.setOutlineColor(sf::Color(20, 20, 20, 255));
	m_bowItem.m_type = ItemType::Bow;
	m_bowItem.m_price = 15;
	textureManager->RequireResource("WeaponBow");
	m_bowItem.m_sprite.setTexture(*textureManager->GetResource("WeaponBow"));
	m_bowItem.m_sprite.setOrigin(textureManager->GetResource("WeaponBow")->getSize().x / 2.0f, textureManager->GetResource("WeaponBow")->getSize().y / 2.0f);
	m_bowItem.m_sprite.setScale(1.5, 1.5);
	
	m_bowItem.m_text.setFont(*fontManager->GetResource("MainFont"));
	m_bowItem.m_text.setString("Bow: " + std::to_string(m_bowItem.m_price) + " Gold");
	m_bowItem.m_text.setCharacterSize(32);
	m_bowItem.m_text.setOutlineColor(sf::Color::Black);
	m_bowItem.m_text.setOutlineThickness(2.f);
	textRect = m_bowItem.m_text.getLocalBounds();
	m_bowItem.m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//-----------------

	//-----Armor Item
	m_armorItem.m_rect = sf::FloatRect(0, 0, 256, 256);
	m_armorItem.m_shape = sf::RectangleShape(sf::Vector2f(m_armorItem.m_rect.width, m_armorItem.m_rect.height));
	m_armorItem.m_shape.setFillColor(sf::Color(255, 255, 255, 50));
	m_armorItem.m_shape.setOutlineThickness(4);
	m_armorItem.m_shape.setOutlineColor(sf::Color(20, 20, 20, 255));
	m_armorItem.m_type = ItemType::ArmorUpgrade;
	m_armorItem.m_price = 15;
	textureManager->RequireResource("TorsoMedium");
	m_armorItem.m_sprite.setTexture(*textureManager->GetResource("TorsoMedium"));
	m_armorItem.m_sprite.setTextureRect(sf::IntRect(0, 128, 64, 64));
	m_armorItem.m_sprite.setOrigin(m_armorItem.m_sprite.getTextureRect().width / 2.0f, m_armorItem.m_sprite.getTextureRect().height / 2.0f);
	m_armorItem.m_sprite.setScale(1.5, 1.5);

	m_armorItem.m_text.setFont(*fontManager->GetResource("MainFont"));
	m_armorItem.m_text.setString("Armor: " + std::to_string(m_armorItem.m_price) + " Gold");
	m_armorItem.m_text.setCharacterSize(32);
	m_armorItem.m_text.setOutlineColor(sf::Color::Black);
	m_armorItem.m_text.setOutlineThickness(2.f);
	textRect = m_armorItem.m_text.getLocalBounds();
	m_armorItem.m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//-----------------

	//-----Shield Item
	m_shieldItem.m_rect = sf::FloatRect(0, 0, 256, 256);
	m_shieldItem.m_shape = sf::RectangleShape(sf::Vector2f(m_shieldItem.m_rect.width, m_shieldItem.m_rect.height));
	m_shieldItem.m_shape.setFillColor(sf::Color(255, 255, 255, 50));
	m_shieldItem.m_shape.setOutlineThickness(4);
	m_shieldItem.m_shape.setOutlineColor(sf::Color(20, 20, 20, 255));
	m_shieldItem.m_type = ItemType::Shield;
	m_shieldItem.m_price = 20;
	textureManager->RequireResource("WeaponShield");
	m_shieldItem.m_sprite.setTexture(*textureManager->GetResource("WeaponShield"));
	m_shieldItem.m_sprite.setTextureRect(sf::IntRect(0, 128, 64, 64));
	m_shieldItem.m_sprite.setOrigin(m_shieldItem.m_sprite.getTextureRect().width / 2.0f, m_shieldItem.m_sprite.getTextureRect().height / 2.0f);
	m_shieldItem.m_sprite.setScale(2, 2);

	m_shieldItem.m_text.setFont(*fontManager->GetResource("MainFont"));
	m_shieldItem.m_text.setString("Shield: " + std::to_string(m_shieldItem.m_price) + " Gold");
	m_shieldItem.m_text.setCharacterSize(32);
	m_shieldItem.m_text.setOutlineColor(sf::Color::Black);
	m_shieldItem.m_text.setOutlineThickness(2.f);
	textRect = m_shieldItem.m_text.getLocalBounds();
	m_shieldItem.m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//-----------------

	//-----Arrow Item
	m_arrowItem.m_rect = sf::FloatRect(0, 0, 256, 256);
	m_arrowItem.m_shape = sf::RectangleShape(sf::Vector2f(m_arrowItem.m_rect.width, m_arrowItem.m_rect.height));
	m_arrowItem.m_shape.setFillColor(sf::Color(255, 255, 255, 50));
	m_arrowItem.m_shape.setOutlineThickness(4);
	m_arrowItem.m_shape.setOutlineColor(sf::Color(20, 20, 20, 255));
	m_arrowItem.m_type = ItemType::Arrow;
	m_arrowItem.m_price = 5;
	textureManager->RequireResource("WeaponArrow");
	m_arrowItem.m_sprite.setTexture(*textureManager->GetResource("WeaponArrow"));
	m_arrowItem.m_sprite.setOrigin(textureManager->GetResource("WeaponArrow")->getSize().x / 2.0f, textureManager->GetResource("WeaponArrow")->getSize().y / 2.0f);
	m_arrowItem.m_sprite.setScale(1.5, 1.5);

	m_arrowItem.m_text.setFont(*fontManager->GetResource("MainFont"));
	m_arrowItem.m_text.setString("10 Arrows: " + std::to_string(m_arrowItem.m_price) + " Gold");
	m_arrowItem.m_text.setCharacterSize(32);
	m_arrowItem.m_text.setOutlineColor(sf::Color::Black);
	m_arrowItem.m_text.setOutlineThickness(2.f);
	textRect = m_arrowItem.m_text.getLocalBounds();
	m_arrowItem.m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//-----------------

	//-----Potion Item
	m_potionItem.m_rect = sf::FloatRect(0, 0, 256, 256);
	m_potionItem.m_shape = sf::RectangleShape(sf::Vector2f(m_potionItem.m_rect.width, m_potionItem.m_rect.height));
	m_potionItem.m_shape.setFillColor(sf::Color(255, 255, 255, 50));
	m_potionItem.m_shape.setOutlineThickness(4);
	m_potionItem.m_shape.setOutlineColor(sf::Color(20, 20, 20, 255));
	m_potionItem.m_type = ItemType::Potion;
	m_potionItem.m_price = 10;
	textureManager->RequireResource("ItemPotion");
	m_potionItem.m_sprite.setTexture(*textureManager->GetResource("ItemPotion"));
	m_potionItem.m_sprite.setOrigin(textureManager->GetResource("ItemPotion")->getSize().x / 2.0f, textureManager->GetResource("ItemPotion")->getSize().y / 2.0f);
	m_potionItem.m_sprite.setScale(0.2, 0.2);

	m_potionItem.m_text.setFont(*fontManager->GetResource("MainFont"));
	m_potionItem.m_text.setString("Potion: " + std::to_string(m_potionItem.m_price) + " Gold");
	m_potionItem.m_text.setCharacterSize(32);
	m_potionItem.m_text.setOutlineColor(sf::Color::Black);
	m_potionItem.m_text.setOutlineThickness(2.f);
	textRect = m_potionItem.m_text.getLocalBounds();
	m_potionItem.m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//-----------------

}

void State_Store::OnDestroy()
{

}

void State_Store::Activate()
{

}

void State_Store::Deactivate()
{

}

void State_Store::Update(const sf::Time& l_deltaTime)
{

}

void State_Store::Draw()
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();
	window->draw(m_rectBackground);
	window->draw(m_textTitle);
	DrawItem(&m_bowItem, 0);
	DrawItem(&m_armorItem, 1);
	DrawItem(&m_shieldItem, 2);
	DrawItem(&m_arrowItem, 3);
	DrawItem(&m_potionItem, 4);
}

void State_Store::BuyItem(sf::Vector2i l_mousePosition)
{
	Player* player = m_stateManager->GetContext()->m_entityManager->GetPlayer();
	if (m_bowItem.m_rect.contains(static_cast<sf::Vector2f>(l_mousePosition)))
		player->BuyBow(m_bowItem.m_price);
	if (m_armorItem.m_rect.contains(static_cast<sf::Vector2f>(l_mousePosition)))
		player->BuyArmor(m_armorItem.m_price);
	if (m_arrowItem.m_rect.contains(static_cast<sf::Vector2f>(l_mousePosition)))
		player->BuyArrow(m_arrowItem.m_price);
	if (m_shieldItem.m_rect.contains(static_cast<sf::Vector2f>(l_mousePosition)))
		player->BuyShield(m_shieldItem.m_price);
	if (m_potionItem.m_rect.contains(static_cast<sf::Vector2f>(l_mousePosition)))
		player->BuyPotion(m_potionItem.m_price);
}

void State_Store::DrawItem(StoreItem* l_item, int l_order)
{
	sf::RenderWindow* window = m_stateManager->GetContext()->m_window->GetRenderWindow();

	l_item->m_rect.left = window->getSize().x / 20.0f + l_order * l_item->m_rect.width * 1.2;
	l_item->m_rect.top = window->getSize().x / 12.0f;
	l_item->m_shape.setPosition(l_item->m_rect.left, l_item->m_rect.top);
	l_item->m_sprite.setPosition(l_item->m_rect.left + l_item->m_rect.width / 2, l_item->m_rect.top + l_item->m_rect.height / 2 - 32);
	l_item->m_text.setPosition(l_item->m_rect.left + l_item->m_rect.width / 2, l_item->m_rect.top + l_item->m_rect.height / 2 + 96);

	window->draw(l_item->m_shape);
	window->draw(l_item->m_text);
	window->draw(l_item->m_sprite);
}

void State_Store::Close()
{
	m_stateManager->SwitchTo(StateType::Game);
}
