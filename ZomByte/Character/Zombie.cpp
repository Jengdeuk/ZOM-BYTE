#include "Zombie.h"
#include "Level/GameLevel.h"

#include "Core/Input.h"
#include "Game/Game.h"

#include "Weapon/Pistol.h"
#include "Weapon/Uzi.h"
#include "Weapon/Shotgun.h"

#include <memory>

using namespace JD;

Zombie::Zombie(const InitData& initData, const Status& status)
	: Super(initData, status)
{
}

void Zombie::BeginPlay()
{
	Super::BeginPlay();
}

void Zombie::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void Zombie::Draw()
{
	Super::Draw();
}