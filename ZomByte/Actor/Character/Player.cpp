#include "Player.h"
#include "Level/GameLevel.h"

#include "Core/Input.h"
#include "Render/Renderer.h"

#include "Physics/Collision.h"

#include "Game/Game.h"

#include "Actor/Weapon/Pistol.h"
#include "Actor/Weapon/Uzi.h"
#include "Actor/Weapon/Shotgun.h"

#include <memory>

using namespace JD;

Player::Player(const InitData& initData, const Status& status)
	: Super(initData, status)
{
	SetCollisionFilter(CollisionFilter{ PLAYER, ZOMBIE });
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	TakeWeapons();
}

void Player::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (Input::Instance().GetKeyDown(VK_ESCAPE))
	{
		Game::Instance().ToggleMenu();
		return;
	}

	MovementInput(deltaTime);
	ChangeWeaponInput();
	UseWeaponInput();
}

void Player::TakeWeapons()
{
	std::unique_ptr<Weapon> newWeapon;
	Weapon::InitData initData;

	// 1. Pistol
	initData.timerTime = 0.425f;
	initData.attackRate = 1;
	initData.owner = this;

	newWeapon = std::make_unique<Pistol>(initData);
	weapons.emplace_back(newWeapon.get());
	GetOwner()->AddNewActor(std::move(newWeapon));

	// 2. Uzi
	initData.timerTime = 0.175f;
	initData.attackRate = 1;
	initData.owner = this;

	newWeapon = std::make_unique<Uzi>(initData);
	weapons.emplace_back(newWeapon.get());
	GetOwner()->AddNewActor(std::move(newWeapon));

	// 3. Shotgun
	initData.timerTime = 1.0f;
	initData.attackRate = 4;
	initData.owner = this;

	newWeapon = std::make_unique<Shotgun>(initData);
	weapons.emplace_back(newWeapon.get());
	GetOwner()->AddNewActor(std::move(newWeapon));

	currentWeapon = weapons.front();
}

void Player::EnhanceWeapons()
{
	for (auto& weapon : weapons)
	{
		weapon->SetAttackRate(GetStatus().attackRate);
	}
}

void Player::StrengthTraining(const int amount)
{
	Super::StrengthTraining(amount);

	EnhanceWeapons();
}

void Player::MovementInput(float deltaTime)
{
	Vector2<float> moveDirection;

	bool isMove = false;
	if (Input::Instance().GetKey(VK_RIGHT))
	{
		isMove = true;
		moveDirection.x = 1;
	}
	if (Input::Instance().GetKey(VK_LEFT))
	{
		isMove = true;
		moveDirection.x = -1;
	}
	if (Input::Instance().GetKey(VK_UP))
	{
		isMove = true;
		moveDirection.y = 1;
	}
	if (Input::Instance().GetKey(VK_DOWN))
	{
		isMove = true;
		moveDirection.y = -1;
	}

	if (isMove)
	{
		Character::AccumulateMove(moveDirection.Normalized());
	}
}

void Player::ChangeWeaponInput()
{
	int selectIndex = -1;
	if (Input::Instance().GetKeyDown('1'))
	{
		selectIndex = 0;
	}
	else if (Input::Instance().GetKeyDown('2'))
	{
		selectIndex = 1;
	}
	else if (Input::Instance().GetKeyDown('3'))
	{
		selectIndex = 2;
	}
	else if (Input::Instance().GetKeyDown('4'))
	{
		selectIndex = 3;
	}
	else if (Input::Instance().GetKeyDown('5'))
	{
		selectIndex = 4;
	}
	
	if (selectIndex >= 0 && selectIndex < static_cast<int>(weapons.size()))
	{
		(GetOwner()->As<GameLevel>())->SetCurrentWeaponIndex(selectIndex);
		currentWeapon = weapons[selectIndex];
	}
}

void Player::UseWeaponInput()
{
	int dirIdx = -1;
	if (Input::Instance().GetKey('Q'))
	{
		dirIdx = 0;
	}
	else if (Input::Instance().GetKey('W'))
	{
		dirIdx = 1;
	}
	else if (Input::Instance().GetKey('E'))
	{
		dirIdx = 2;
	}
	else if (Input::Instance().GetKey('A'))
	{
		dirIdx = 3;
	}
	else if (Input::Instance().GetKey('D'))
	{
		dirIdx = 4;
	}
	else if (Input::Instance().GetKey('Z'))
	{
		dirIdx = 5;
	}
	else if (Input::Instance().GetKey('X'))
	{
		dirIdx = 6;
	}
	else if (Input::Instance().GetKey('C'))
	{
		dirIdx = 7;
	}

	if (dirIdx >= 0)
	{
		currentWeapon->Fire(dirIdx);
	}
}

void Player::TransformUpdate(float deltaTime)
{
	Super::TransformUpdate(deltaTime);

	Renderer::Instance().SetViewTransform(Vector2<int>(GetPosition() * -1));
}
