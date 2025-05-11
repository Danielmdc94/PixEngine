#include "../include/Engine.h"

int main(int argc, char* argv[])
{
	Engine engine;
	while (!engine.GetWindow()->IsDone())
	{
		engine.Update();
		engine.Render();
		engine.LateUpdate();
	}
	return(0);
}