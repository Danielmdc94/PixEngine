#include "Engine.h"
#include "State_GameIntro.h"
#include "State_GameMenu.h"
#include "State_Game.h"
#include "GameStateType.h"

int main(int argc, char* argv[])
{
	Engine engine;

	// Register this project's own states with the engine and tell it which
	// one to switch to once the built-in PixEngine intro finishes.
	StateManager* stateManager = engine.GetStateManager();
	stateManager->RegisterState<State_GameIntro>(GameStateType::GameIntro);
	stateManager->RegisterState<State_GameMenu>(GameStateType::GameMenu);
	stateManager->RegisterState<State_Game>(GameStateType::Game);
	stateManager->SetInitialState(GameStateType::GameIntro);

	while (!engine.GetWindow()->IsDone())
	{
		engine.Update();
		engine.Render();
		engine.LateUpdate();
	}
	return(0);
}