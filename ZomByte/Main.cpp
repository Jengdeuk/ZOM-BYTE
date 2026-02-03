#include <iostream>

#include "Engine/Engine.h"

int main()
{
	DEBUG_MEMORY_LEAK;

	JD::Engine::Instance().Run();
}