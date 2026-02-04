#pragma once

#include "Common/Common.h"

#include <memory>
#include <vector>

enum class State
{
	None = -1,
	GamePlay = 0,
	Menu = 1,
	Length
};

namespace JD { class Level; }

class Game
{
private:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

public:
	static Game& Instance();

public:
	void Run();

public:
	void ToggleMenu();
	void QuitEngine();

private:
	std::vector<std::unique_ptr<JD::Level>> levels;
	State state = State::GamePlay;
};