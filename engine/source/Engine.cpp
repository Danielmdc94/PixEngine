#include "../include/Engine.h"
#include <iostream>

Engine::Engine() : m_window(WIN_NAME, sf::Vector2u(WIN_W, WIN_H)), m_stateManager(&m_context), m_eventManager(&m_context), m_entityManager(&m_context)
{
	m_clock.restart();
	srand(time(nullptr));

	m_context.m_window = &m_window;
	m_context.m_eventManager = &m_eventManager;
	m_context.m_textureManager = &m_textureManager;
	m_context.m_audioManager = &m_audioManager;
	m_context.m_fontManager = &m_fontManager;
	m_context.m_entityManager = &m_entityManager;
	m_context.m_stateManager = &m_stateManager;
	m_stateManager.SwitchTo(StateType::Intro);
}

Engine::~Engine()
{

}

void Engine::Update()
{
	m_window.Update();
	m_eventManager.Update();
	m_stateManager.Update(m_elapsed);
}

void Engine::Render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Engine::LateUpdate()
{
	RestartClock();
}
