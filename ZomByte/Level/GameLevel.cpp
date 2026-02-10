#include "GameLevel.h"

#include "Engine/Engine.h"
#include "Core/Input.h"
#include "Render/Renderer.h"
#include "Physics/PhysicsManager.h"

#include "Game/Game.h"

#include "Actor/Character/Player.h"
#include "Actor/Character/Zombie.h"

#include "Actor/Weapon/Weapon.h"

#include "Util/Util.h"

#include <memory>

using namespace JD;

static Actor::InitData spawnData{ "Z", Vector2<float>(), Color::DarkGreen, 9 };
static Character::Status minStat{ 1, 1, 1 };
static Character::Status maxStat{ 1, 1, 2 };

GameLevel::GameLevel(const Vector2<int>& mapSize)
	: mapSize(mapSize),
	level(1),
	regenTime(5.0f),
	regenCount(3)
{
	LoadGround("ground.txt");

	levelUpTimer.Reset();
	levelUpTimer.SetTargetTime(30.0f);

	regenTimer.Reset();
	regenTimer.SetTargetTime(regenTime);

	// Spawn Player
	Actor::InitData initData;
	initData.image = "P";
	initData.color = Color::DarkYellow;
	initData.position = Vector2<float>(0.0f, 0.0f);
	initData.sortingOrder = 15;

	Character::Status status;
	status.healthPoint = 3;
	status.attackRate = 1;
	status.moveSpeed = 5;

	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(initData, status);
	player = newPlayer.get();
	AddNewActor(std::move(newPlayer));

	Regen();
}

void GameLevel::Tick(float deltaTime)
{
	if (Input::Instance().GetKeyDown(VK_ESCAPE))
	{
		Game::Instance().ToggleMenu();
		return;
	}

	if (player->IsDead())
	{
		return;
	}

	Super::Tick(deltaTime);

	PhysicsUpdate(deltaTime);
	TransformUpdate(deltaTime);

	levelUpTimer.Tick(deltaTime);
	if (levelUpTimer.IsTimeOut())
	{
		LevelUp();
	}

	regenTimer.Tick(deltaTime);
	if (regenTimer.IsTimeOut())
	{
		Regen();
	}

	survivalTime += deltaTime;
	lastDeltaTime = deltaTime;
}

void GameLevel::Draw()
{
	DrawBackground();

	Super::Draw();

	DrawHUD();
}

void GameLevel::TickGameOver(float deltaTime)
{
}

void GameLevel::PhysicsUpdate(float deltaTime)
{
	PhysicsManager::Instance().PhysicsUpdate(Super::GetActors(), deltaTime);
}

void GameLevel::TransformUpdate(float deltaTime)
{
	Super::TransformUpdate(deltaTime);

	PhysicsManager::Instance().ResolvePenetration(Super::GetActors(), deltaTime);
}

void GameLevel::OnKilled()
{
	++killed;
}

void GameLevel::LevelUp()
{
	levelUpTimer.Reset();

	++level;
	regenTime -= round(regenTime * 0.05f);
	regenCount += static_cast<int>(round(regenCount * 0.1f));

	++minStat.healthPoint;
	++maxStat.healthPoint;

	maxStat.moveSpeed += static_cast<int>(round(maxStat.moveSpeed * 0.2f));

	++minStat.attackRate;
	++maxStat.attackRate;
}

void GameLevel::Regen()
{
	regenTimer.Reset();

	const Vector2<float> targetPos{ player->GetPosition() };
	const Vector2<float> halfMapSize{ mapSize.x * 0.5f + 3.0f, mapSize.y * 0.5f + 3.0f };

	Character::Status status;
	Actor::InitData initData{ spawnData };

	// Left
	for (int i = 0; i < regenCount; ++i)
	{
		status.healthPoint = static_cast<int>(Util::Random(minStat.healthPoint, maxStat.healthPoint));
		status.attackRate = minStat.attackRate;
		status.moveSpeed = Util::Randomf(minStat.moveSpeed, maxStat.moveSpeed);

		const float summonX = targetPos.x - halfMapSize.x;
		const float summonY = Util::Randomf(targetPos.y - halfMapSize.y, targetPos.y + halfMapSize.y);
		initData.position = Vector2<float>(summonX, summonY);

		std::unique_ptr<Zombie> newZombie = std::make_unique<Zombie>(initData, status);
		AddNewActor(std::move(newZombie));
	}

	// Top
	for (int i = 0; i < regenCount; ++i)
	{
		status.healthPoint = static_cast<int>(Util::Random(minStat.healthPoint, maxStat.healthPoint));
		status.attackRate = minStat.attackRate;
		status.moveSpeed = Util::Randomf(minStat.moveSpeed, maxStat.moveSpeed);

		const float summonX = Util::Randomf(targetPos.x - halfMapSize.x, targetPos.x + halfMapSize.x);
		const float summonY = targetPos.y + halfMapSize.y;
		initData.position = Vector2<float>(summonX, summonY);

		std::unique_ptr<Zombie> newZombie = std::make_unique<Zombie>(initData, status);
		AddNewActor(std::move(newZombie));
	}

	// Right
	for (int i = 0; i < regenCount; ++i)
	{
		status.healthPoint = static_cast<int>(Util::Random(minStat.healthPoint, maxStat.healthPoint));
		status.attackRate = minStat.attackRate;
		status.moveSpeed = Util::Randomf(minStat.moveSpeed, maxStat.moveSpeed);

		const float summonX = targetPos.x + halfMapSize.x;
		const float summonY = Util::Randomf(targetPos.y - halfMapSize.y, targetPos.y + halfMapSize.y);
		initData.position = Vector2<float>(summonX, summonY);

		std::unique_ptr<Zombie> newZombie = std::make_unique<Zombie>(initData, status);
		AddNewActor(std::move(newZombie));
	}

	// Bottom
	for (int i = 0; i < regenCount; ++i)
	{
		status.healthPoint = static_cast<int>(Util::Random(minStat.healthPoint, maxStat.healthPoint));
		status.attackRate = minStat.attackRate;
		status.moveSpeed = Util::Randomf(minStat.moveSpeed, maxStat.moveSpeed);

		const float summonX = Util::Randomf(targetPos.x - halfMapSize.x, targetPos.x + halfMapSize.x);
		const float summonY = targetPos.y - halfMapSize.y;
		initData.position = Vector2<float>(summonX, summonY);

		std::unique_ptr<Zombie> newZombie = std::make_unique<Zombie>(initData, status);
		AddNewActor(std::move(newZombie));
	}
}

void GameLevel::LoadGround(const char* filename)
{
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (file == nullptr)
	{
		DEBUG_BREAK("Failed to open background file.");
	}

	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	backgroundImg = std::make_unique<char[]>(fileSize + 1);

	size_t readSize = fread(backgroundImg.get(), sizeof(char), fileSize, file);

	backgroundImgSliced.reserve(fileSize);
	int i = -1;
	while (true)
	{
		++i;

		if (backgroundImg[i] == '\0')
		{
			break;
		}

		if (backgroundImg[i] == '\n')
		{
			continue;
		}

		backgroundImgSliced.emplace_back(std::make_unique<char[]>(2));
		backgroundImgSliced.back()[0] = backgroundImg[i];
	}

	fclose(file);
}

void GameLevel::DrawBackground()
{
	if (!player)
	{
		return;
	}

	Vector2<int> playerPos{ player->GetPosition() };
	playerPos.y *= -1;
	playerPos.x = (playerPos.x % mapSize.x + mapSize.x) % mapSize.x;
	playerPos.y = (playerPos.y % mapSize.y + mapSize.y) % mapSize.y;

	const int imglen = static_cast<int>(backgroundImgSliced.size());
	for (int y = 0; y < mapSize.y; ++y)
	{
		for (int x = 0; x < mapSize.x; ++x)
		{
			const int sX = (x + playerPos.x) % mapSize.x;
			const int sY = (y + playerPos.y) % mapSize.y;
			int idx = (sY * mapSize.x + sX) % imglen;
			Renderer::Instance().Submit(backgroundImgSliced[idx].get(), Vector2<int>(x, y), Color::DarkGray, 0);
		}
	}
}

void GameLevel::DrawHUD()
{
	const int xPos = mapSize.x + 1;

	// 0 - level
	Renderer::Instance().Submit("Level ", Vector2<int>(xPos, 0), Color::Gray);
	sprintf_s(buffer_level, "%d", level);
	Renderer::Instance().Submit(buffer_level, Vector2<int>(xPos + 6, 0), Color::Gray);

	// 2 - time, mapSize.y - fps
	sprintf_s(buffer_stime, "%02d:%02d", static_cast<int>(survivalTime / 60), static_cast<int>(survivalTime) % 60);
	Renderer::Instance().Submit(buffer_stime, Vector2<int>(xPos, 2), Color::Gray);

	sprintf_s(buffer_fps, "FPS:%d", static_cast<int>(1.0f / lastDeltaTime));
	Renderer::Instance().Submit(buffer_fps, Vector2<int>(Engine::Instance().GetScreenSize().x - 7, mapSize.y - 1), Color::DarkGray);

	// 7 - hp
	const int hp = (player->As<Character>())->GetStatus().healthPoint;
	for (int i = 0; i < hp; ++i)
	{
		buffer_hp[i] = '*';
	}
	buffer_hp[hp] = '\0';
	Renderer::Instance().Submit(buffer_hp, Vector2<int>(xPos, 7), Color::Red);

	// 9 - ar
	const int ar = (player->As<Character>())->GetStatus().attackRate;
	for (int i = 0; i < ar; ++i)
	{
		buffer_ar[i] = '*';
	}
	buffer_ar[ar] = '\0';
	Renderer::Instance().Submit(buffer_ar, Vector2<int>(xPos, 9), Color::Magenta);

	// 11 - ms
	const int ms = static_cast<int>((player->As<Character>())->GetStatus().moveSpeed);
	for (int i = 0; i < ms; ++i)
	{
		buffer_ms[i] = '*';
	}
	buffer_ms[ms] = '\0';
	Renderer::Instance().Submit(buffer_ms, Vector2<int>(xPos, 11), Color::Cyan);

	// 20 - killed
	Renderer::Instance().Submit("Killed:", Vector2<int>(xPos, 20), Color::Gray);
	sprintf_s(buffer_killed, "%d", killed);
	Renderer::Instance().Submit(buffer_killed, Vector2<int>(xPos + 8, 20), Color::DarkGreen);

	// mapSize.y - weapon
	static const std::vector<Weapon*>& weapons = player->GetWeapons();
	if (weapons.empty())
	{
		return;
	}

	const int weaponY = /*mapSize.y - 5*/24;
	const int ammoX = 13;
	Renderer::Instance().Submit(">", Vector2<int>(xPos - 1, weaponY + currentWeaponIndex), Color::Gray);
	
	Color weaponTextColor[5]{ Color::DarkGray, Color::DarkGray, Color::DarkGray, Color::DarkGray, Color::DarkGray };
	weaponTextColor[currentWeaponIndex] = Color::Gray;

	Renderer::Instance().Submit("1. istol  ", Vector2<int>(xPos + 1, weaponY), weaponTextColor[0]);
	Renderer::Instance().Submit("p", Vector2<int>(xPos + 3, weaponY), Color::White);
	sprintf_s(buffer_ammo[0], "%d", weapons[0]->GetMagazine());
	Renderer::Instance().Submit(buffer_ammo[0], Vector2<int>(xPos + ammoX, weaponY), weaponTextColor[0]);

	Renderer::Instance().Submit("2. zi     ", Vector2<int>(xPos + 1, weaponY + 1), weaponTextColor[1]);
	Renderer::Instance().Submit("u", Vector2<int>(xPos + 3, weaponY + 1), Color::Yellow);
	sprintf_s(buffer_ammo[1], "%d", weapons[1]->GetMagazine());
	Renderer::Instance().Submit(buffer_ammo[1], Vector2<int>(xPos + ammoX, weaponY + 1), weaponTextColor[1]);

	Renderer::Instance().Submit("3. hotgun ", Vector2<int>(xPos + 1, weaponY + 2), weaponTextColor[2]);
	Renderer::Instance().Submit("s", Vector2<int>(xPos + 3, weaponY + 2), Color::White);
	sprintf_s(buffer_ammo[2], "%d", weapons[2]->GetMagazine());
	Renderer::Instance().Submit(buffer_ammo[2], Vector2<int>(xPos + ammoX, weaponY + 2), weaponTextColor[2]);

	Renderer::Instance().Submit("4. arrel  ", Vector2<int>(xPos + 1, weaponY + 3), weaponTextColor[3]);
	Renderer::Instance().Submit("b", Vector2<int>(xPos + 3, weaponY + 3), Color::Magenta);
	sprintf_s(buffer_ammo[3], "%d", weapons[3]->GetMagazine());
	Renderer::Instance().Submit(buffer_ammo[3], Vector2<int>(xPos + ammoX, weaponY + 3), weaponTextColor[3]);

	Renderer::Instance().Submit("5. ailgun ", Vector2<int>(xPos + 1, weaponY + 4), weaponTextColor[4]);
	Renderer::Instance().Submit("r", Vector2<int>(xPos + 3, weaponY + 4), Color::Cyan);
	sprintf_s(buffer_ammo[4], "%d", weapons[4]->GetMagazine());
	Renderer::Instance().Submit(buffer_ammo[4], Vector2<int>(xPos + ammoX, weaponY + 4), weaponTextColor[4]);

	if (player->IsDead())
	{
		const Vector2<int> screenSize = Engine::Instance().GetScreenSize();
		Renderer::Instance().Submit("Game Over!", Vector2<int>(screenSize.x / 2 - 4, screenSize.y / 2), Color::Red, 20);
	}
}
