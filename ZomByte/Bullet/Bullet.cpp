#include "Bullet.h"

#include "Level/GameLevel.h"

#include <cmath>

const char* Bullet::bulletImage[8] =
{
	"\\", "|", "/",
	"-", "-",
	"/",  "|", "\\"
};

Bullet::Bullet(const Actor::InitData& actorInitData, const InitData& initData)
	: Super(
		Super::InitData
		{
			bulletImage[initData.dirIdx],
			actorInitData.position,
			actorInitData.color,
			actorInitData.sortingOrder
		}),
	damage(initData.damage),
	direction(initData.fireDir),
	moveSpeed(initData.moveSpeed),
	drag(initData.drag),
	lastPosition(actorInitData.position)
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
	if (timer.IsTimeOut() || moveSpeed <= 10.0f)
	{
		Destroy();
		return;
	}

	UpdateMovement(deltaTime);
}

void Bullet::UpdateMovement(float deltaTime)
{
	// 1) 속도 지수 감쇠: speed(t+dt) = speed(t) * e^(-drag*dt)
	moveSpeed *= std::exp(-drag * deltaTime);
	SetPosition(GetPosition() + direction * moveSpeed * deltaTime);
}
