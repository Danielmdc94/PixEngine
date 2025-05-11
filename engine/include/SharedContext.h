#pragma once

#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "FontManager.h"
#include "EntityManager.h"

class StateManager;

struct SharedContext
{
	SharedContext() : m_window(nullptr), m_eventManager(nullptr), m_textureManager(nullptr), m_audioManager(nullptr), m_fontManager(nullptr), m_entityManager(nullptr), m_stateManager(nullptr) {}

	Window* m_window;
	EventManager* m_eventManager;
	TextureManager* m_textureManager;
	AudioManager* m_audioManager;
	FontManager* m_fontManager;
	EntityManager* m_entityManager;
	StateManager* m_stateManager;
};