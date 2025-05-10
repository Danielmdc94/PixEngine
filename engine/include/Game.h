#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Window.h"
#include "SharedContext.h"
#include "StateManager.h"
#include "HUDManager.h"
#include "ResourceManager.h"

# define WIN_NAME   "Sir Hives-a-lot"
# define WIN_W 		1920
# define WIN_H 		1080

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	Window* GetWindow() { return &m_window; };
	sf::Time GetElapsed() { return m_elapsed; };

	void RestartClock() { m_elapsed = m_clock.restart(); };

private:

	SharedContext m_context;
	Window m_window;
	StateManager m_stateManager;
	EventManager m_eventManager;
	TextureManager m_textureManager;
	AudioManager m_audioManager;
	FontManager m_fontManager;
	EntityManager m_entityManager;
	HUDManager m_hudManager;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};