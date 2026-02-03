#include "Game.h"

#include "Engine/Engine.h"
#include "Level/Level.h"

Game::Game()
{
	state = State::GamePlay;
}

Game::~Game()
{
}

Game& Game::Instance()
{
	static Game instance;
	return instance;
}

void Game::Run()
{
	JD::Engine::Instance().Run();
}

void Game::ToggleMenu()
{
	system("cls");

	state = static_cast<State>(1 - static_cast<int>(state));
	JD::Engine::Instance().SetNewLevel(levels[static_cast<int>(state)].get());
}