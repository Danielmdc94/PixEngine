#pragma once

struct SharedContext;
enum class StateType;

class EventManager
{
public:
	EventManager(SharedContext* context);
	~EventManager();

	sf::Vector2i GetMousePosition();

	void SetCurrentState(StateType l_type) { m_currentState = l_type; };

	void Update();

private:
	void HandleGeneralEvents(sf::Event l_event);
	void HandleIntroEvents(sf::Event l_event);

	SharedContext* m_context;
	StateType m_currentState;
	sf::Vector2i m_mousePosition;
};