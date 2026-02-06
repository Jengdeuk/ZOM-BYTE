#include "GameLevel.h"

#include "Engine/Engine.h"
#include "Render/Renderer.h"
#include "Character/Player.h"
#include "Character/Zombie.h"

#include <memory>

using namespace JD;

GameLevel::GameLevel(const Vector2<int>& mapSize)
	: mapSize(mapSize)
{
	// Player
	Actor::InitData initData;
	initData.image = "P";
	initData.color = Color::DarkYellow;
	initData.position = Vector2<int>(0, 0);
	initData.sortingOrder = 10;

	Character::Status status;
	status.healthPoint = 5;
	status.attackRate = 1;
	status.moveSpeed = 6;

	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(initData, status);
	player = newPlayer.get();
	AddNewActor(std::move(newPlayer));

	// Zombie
	initData.image = "Z";
	initData.color = Color::DarkGreen;
	initData.position = Vector2<int>(13, 5);
	initData.sortingOrder = 9;

	status.healthPoint = 3;
	status.attackRate = 1;
	status.moveSpeed = 3;

	std::unique_ptr<Zombie> newZombie = std::make_unique<Zombie>(initData, status);
	AddNewActor(std::move(newZombie));
}

void GameLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	survivalTime += deltaTime;
	lastDeltaTime = deltaTime;
}

void GameLevel::Draw()
{
	Super::Draw();

	DrawHUD();
}

void GameLevel::DrawHUD()
{
	// 0 - time, fps
	sprintf_s(buffer_stime, "%d:%d", static_cast<int>(survivalTime / 60), static_cast<int>(survivalTime) % 60);
	Renderer::Instance().Submit(buffer_stime, Vector2<int>(mapSize.x + 2, 0), Color::Gray);

	sprintf_s(buffer_fps, "FPS:%d", static_cast<int>(1.0f / lastDeltaTime));
	Renderer::Instance().Submit(buffer_fps, Vector2<int>(Engine::Instance().GetScreenSize().x - 7, 0), Color::DarkGray);

	// 2 - hp
	const int hp = (player->As<Character>())->GetHealthPoint();
	for (int i = 0; i < hp; ++i)
	{
		buffer_hp[i] = '*';
	}
	Renderer::Instance().Submit(buffer_hp, Vector2<int>(mapSize.x + 2, 2), Color::Red);

	// 4 - killed
	Renderer::Instance().Submit("Killed:", Vector2<int>(mapSize.x + 2, 4), Color::Gray);

	sprintf_s(buffer_killed, "%d", killed);
	Renderer::Instance().Submit(buffer_killed, Vector2<int>(mapSize.x + 2 + 8, 4), Color::DarkGreen);

	// mapSize.y - weapon
	const int weaponY = mapSize.y - 5;
	Renderer::Instance().Submit("*", Vector2<int>(mapSize.x, weaponY + currentWeaponIndex), Color::Gray);
	
	Color weaponTextColor[5]{ Color::DarkGray, Color::DarkGray, Color::DarkGray, Color::DarkGray, Color::DarkGray };
	weaponTextColor[currentWeaponIndex] = Color::Gray;

	Renderer::Instance().Submit("<1>  istol: -", Vector2<int>(mapSize.x + 2, weaponY), weaponTextColor[0]);
	Renderer::Instance().Submit("p", Vector2<int>(mapSize.x + 2 + 4, weaponY), Color::White);

	Renderer::Instance().Submit("<2>  zi: ", Vector2<int>(mapSize.x + 2, weaponY + 1), weaponTextColor[1]);
	Renderer::Instance().Submit("u", Vector2<int>(mapSize.x + 2 + 4, weaponY + 1), Color::Yellow);

	Renderer::Instance().Submit("<3>  hotgun: ", Vector2<int>(mapSize.x + 2, weaponY + 2), weaponTextColor[2]);
	Renderer::Instance().Submit("s", Vector2<int>(mapSize.x + 2 + 4, weaponY + 2), Color::White);

	Renderer::Instance().Submit("<4>  arrel: ", Vector2<int>(mapSize.x + 2, weaponY + 3), weaponTextColor[3]);
	Renderer::Instance().Submit("b", Vector2<int>(mapSize.x + 2 + 4, weaponY + 3), Color::Magenta);

	Renderer::Instance().Submit("<5>  ailgun: ", Vector2<int>(mapSize.x + 2, weaponY + 4), weaponTextColor[4]);
	Renderer::Instance().Submit("r", Vector2<int>(mapSize.x + 2 + 4, weaponY + 4), Color::Cyan);
}
