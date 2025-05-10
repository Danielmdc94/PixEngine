#include "../include/game.h"

int main(int argc, char* argv[])
{
	//ResourceManager::init(argv[0]);

	Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Render();
		game.LateUpdate();
	}
	return(0);
}