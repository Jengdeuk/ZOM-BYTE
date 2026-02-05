#include "Bullet.h"

const char* Bullet::bulletImage[8] =
{
	"\\", "|", "/",
	"-", "-",
	"/",  "|", "\\"
};

Bullet::Bullet(const InitData& initData)
	: Super(
		Super::InitData
		{
			bulletImage[initData.dirIdx],
			Vector2<int>(initData.firePos),
			Color::White,
			5
		}),
	direction(initData.fireDir),
	moveSpeed(initData.moveSpeed)
{
	timer.SetTargetTime(initData.lifeTime);
}

void Bullet::BeginPlay()
{
	Super::BeginPlay();

	timer.Reset();
}

void Bullet::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (timer.IsTimeOut())
	{
		Destroy();
		return;
	}

	UpdateMovement(deltaTime);
}

void Bullet::UpdateMovement(float deltaTime)
{
	SetPosition(GetPosition() + direction * moveSpeed * deltaTime);
}
