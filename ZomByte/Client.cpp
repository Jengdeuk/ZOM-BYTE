#include "Game/Game.h"

int main()
{
	DEBUG_MEMORY_LEAK;
	Game::Instance().Run();
}