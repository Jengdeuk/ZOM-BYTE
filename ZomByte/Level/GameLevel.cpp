#include "GameLevel.h"

#include "Actor/Player.h"

#include <memory>

using namespace JD;

GameLevel::GameLevel()
{
	AddNewActor(std::make_unique<Player>(Vector2<int>(0, 1)));
}