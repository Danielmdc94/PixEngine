#include "../include/HUDManager.h"
#include "../include/SharedContext.h"

HUDManager::HUDManager(SharedContext* context) : m_context(context)
{
	
}

HUDManager::~HUDManager()
{

}

void HUDManager::CreateHUD()
{
	sf::Vector2u windowSize = GetContext()->m_window->GetRenderWindow()->getSize();
	TextureManager* textureManager = GetContext()->m_textureManager;
	FontManager* fontManager = GetContext()->m_fontManager;

	fontManager->RequireResource("MainFont");

	textureManager->RequireResource("WeaponArrow");
	m_arrowSprite.setTexture(*textureManager->GetResource("WeaponArrow"));
	m_arrowSprite.setPosition(32, windowSize.y - 230);

	m_arrowText.setFont(*fontManager->GetResource("MainFont"));
	m_arrowText.setString(sf::String("0"));
	m_arrowText.setCharacterSize(88);
	m_arrowText.setOutlineColor(sf::Color::Black);
	m_arrowText.setOutlineThickness(1.f);
	m_arrowText.setPosition(m_arrowSprite.getPosition() + sf::Vector2f(80, -60));

	textureManager->RequireResource("Coin");
	m_coinSprite.setTexture(*textureManager->GetResource("Coin"));
	m_coinSprite.setScale(0.64f, 0.64f);
	m_coinSprite.setPosition(32, windowSize.y - 192);

	m_coinText.setFont(*fontManager->GetResource("MainFont"));
	m_coinText.setString(sf::String("0"));
	m_coinText.setCharacterSize(88);
	m_coinText.setColor(sf::Color(225, 175, 50));
	m_coinText.setOutlineColor(sf::Color::Black);
	m_coinText.setOutlineThickness(1.f);
	m_coinText.setPosition(m_coinSprite.getPosition() + sf::Vector2f(80, -32));

	textureManager->RequireResource("HealthFrame");
	m_healthFrameSprite.setTexture(*textureManager->GetResource("HealthFrame"));
	m_healthFrameSprite.setPosition(32, windowSize.y - 96);
	m_healthFrameSprite.setScale(4.f, 4.f);

	textureManager->RequireResource("HealthBar");
	m_healthBarSprite.setTexture(*textureManager->GetResource("HealthBar"));
	m_healthBarSprite.setPosition(m_healthFrameSprite.getPosition() + sf::Vector2f(14 * 4, 0));
	m_healthBarSprite.setScale(4.f, 4.f);
	m_healthBarRect = sf::IntRect(0, 0, textureManager->GetResource("HealthBar")->getSize().x, textureManager->GetResource("HealthBar")->getSize().y);
}

void HUDManager::Update(float l_deltaTime)
{
	Player* player = GetContext()->m_entityManager->GetPlayer();
	m_coinText.setString(std::to_string(player->GetGold()));
	m_arrowText.setString(std::to_string(player->GetArrows()));
	
	int playerHitPoints = player->GetHitPoints();
	int maxHitPoints = player->GetMaxHitPoints();

	float healthRatio = float(playerHitPoints) / maxHitPoints;
	int newWidth = int(m_healthBarRect.width * healthRatio);
	m_healthBarSprite.setTextureRect(sf::IntRect(m_healthBarRect.left, m_healthBarRect.top, newWidth, m_healthBarRect.height));
}

void HUDManager::Draw()
{
	sf::RenderWindow* window = GetContext()->m_window->GetRenderWindow();
	window->draw(m_arrowSprite);
	window->draw(m_arrowText);
	window->draw(m_coinSprite);
	window->draw(m_coinText);
	window->draw(m_healthFrameSprite);
	window->draw(m_healthBarSprite);
}

SharedContext* HUDManager::GetContext()
{
	return m_context;
}
