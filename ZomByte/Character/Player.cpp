#include "Player.h"
#include "Level/GameLevel.h"

#include "Core/Input.h"
#include "Game/Game.h"

#include "Weapon/Weapon.h"

using namespace JD;

Player::Player(const InitData& initData, const Status& status)
	: Super(initData, status)
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();
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
}

void Player::Draw()
{
	Super::Draw();
}

void Player::MovementInput(float deltaTime)
{
	static const Vector2<int>& mapSize = (GetOwner()->As<GameLevel>())->GetMapSize();

	Vector2<float> moveDirection;

	bool isMove = false;
	if (Input::Instance().GetKey(VK_RIGHT) && GetPosition().x < mapSize.x - 1)
	{
		isMove = true;
		moveDirection.x = 1;
	}
	if (Input::Instance().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		isMove = true;
		moveDirection.x = -1;
	}
	if (Input::Instance().GetKey(VK_UP) && GetPosition().y > 0)
	{
		isMove = true;
		moveDirection.y = -1;
	}
	if (Input::Instance().GetKey(VK_DOWN) && GetPosition().y < mapSize.y - 1)
	{
		isMove = true;
		moveDirection.y = 1;
	}

	if (isMove)
	{
		Super::Move(moveDirection.Normalized() * deltaTime);
	}
}

void Player::ChangeWeaponInput()
{
	if (Input::Instance().GetKeyDown('1'))
	{
		(GetOwner()->As<GameLevel>())->SetCurrentWeaponIndex(0);
	}
	else if (Input::Instance().GetKeyDown('2'))
	{
		(GetOwner()->As<GameLevel>())->SetCurrentWeaponIndex(1);
	}
	else if (Input::Instance().GetKeyDown('3'))
	{
		(GetOwner()->As<GameLevel>())->SetCurrentWeaponIndex(2);
	}
	else if (Input::Instance().GetKeyDown('4'))
	{
		(GetOwner()->As<GameLevel>())->SetCurrentWeaponIndex(3);
	}
	else if (Input::Instance().GetKeyDown('5'))
	{
		(GetOwner()->As<GameLevel>())->SetCurrentWeaponIndex(4);
	}
}
