#include "Bullet.h"

#include "Level/GameLevel.h"

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
	if (timer.IsTimeOut() || IsOutOfMap())
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

bool Bullet::IsOutOfMap()
{
	static const Vector2<int>& mapSize = (GetOwner()->As<GameLevel>())->GetMapSize();
	const Vector2<int> position = Vector2<int>(GetPosition());
	return position.x < 0 || position.x >= mapSize.x || position.y < 0 || position.y >= mapSize.y;
}
