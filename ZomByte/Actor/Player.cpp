#include "Player.h"

#include "Core/Input.h"
#include "Game/Game.h"

using namespace JD;

Player::Player(const Vector2<int>& position)
	: Super("P", position, Color::DarkYellow, 10)
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

	if (Input::Instance().GetKey(VK_RIGHT) && GetPosition().x < 70)
	{
		Vector2<float> newPosition(GetPosition().x + 1, GetPosition().y);
		SetPosition(newPosition);
	}
	if (Input::Instance().GetKey(VK_LEFT) && GetPosition().x > 0)
	{
		Vector2<float> newPosition(GetPosition().x - 1, GetPosition().y);
		SetPosition(newPosition);
	}
	if (Input::Instance().GetKey(VK_UP) && GetPosition().y > 0)
	{
		Vector2<float> newPosition(GetPosition().x, GetPosition().y - 1);
		SetPosition(newPosition);
	}
	if (Input::Instance().GetKey(VK_DOWN) && GetPosition().y < 25)
	{
		Vector2<float> newPosition(GetPosition().x, GetPosition().y + 1);
		SetPosition(newPosition);
	}
}

void Player::Draw()
{
	Super::Draw();
}