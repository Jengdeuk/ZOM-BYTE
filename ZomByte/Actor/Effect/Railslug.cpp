#include "Railslug.h"

#include "Level/GameLevel.h"
#include "Physics/Collision.h"

#include <cmath>

const char* Railslug::RailslugImage[8] =
{
	"\\", "|", "/",
	"-", "-",
	"/",  "|", "\\"
};

static const Effect::EffectFrame effectSequence[8][6] =
{
	{
		{"\\", 0.07f, Color::Cyan},
		{"\\", 0.07f, Color::White},
		{"\\", 0.07f, Color::Cyan},
		{"\\", 0.07f, Color::Gray},
		{"\\", 0.07f, Color::DarkCyan},
		{"\\", 0.07f, Color::DarkGray}
	},
	{
		{"|", 0.07f, Color::Cyan},
		{"|", 0.07f, Color::White},
		{"|", 0.07f, Color::Cyan},
		{"|", 0.07f, Color::Gray},
		{"|", 0.07f, Color::DarkCyan},
		{"|", 0.07f, Color::DarkGray}
	},
	{
		{"/", 0.07f, Color::Cyan},
		{"/", 0.07f, Color::White},
		{"/", 0.07f, Color::Cyan},
		{"/", 0.07f, Color::Gray},
		{"/", 0.07f, Color::DarkCyan},
		{"/", 0.07f, Color::DarkGray}
	},
	{
		{"-", 0.07f, Color::Cyan},
		{"-", 0.07f, Color::White},
		{"-", 0.07f, Color::Cyan},
		{"-", 0.07f, Color::Gray},
		{"-", 0.07f, Color::DarkCyan},
		{"-", 0.07f, Color::DarkGray}
	},
	{
		{"-", 0.07f, Color::Cyan},
		{"-", 0.07f, Color::White},
		{"-", 0.07f, Color::Cyan},
		{"-", 0.07f, Color::Gray},
		{"-", 0.07f, Color::DarkCyan},
		{"-", 0.07f, Color::DarkGray}
	},
	{
		{"/", 0.07f, Color::Cyan},
		{"/", 0.07f, Color::White},
		{"/", 0.07f, Color::Cyan},
		{"/", 0.07f, Color::Gray},
		{"/", 0.07f, Color::DarkCyan},
		{"/", 0.07f, Color::DarkGray}
	},
	{
		{"|", 0.07f, Color::Cyan},
		{"|", 0.07f, Color::White},
		{"|", 0.07f, Color::Cyan},
		{"|", 0.07f, Color::Gray},
		{"|", 0.07f, Color::DarkCyan},
		{"|", 0.07f, Color::DarkGray}
	},
	{
		{"\\", 0.07f, Color::Cyan},
		{"\\", 0.07f, Color::White},
		{"\\", 0.07f, Color::Cyan},
		{"\\", 0.07f, Color::Gray},
		{"\\", 0.07f, Color::DarkCyan},
		{"\\", 0.07f, Color::DarkGray}
	}
};

Railslug::Railslug(const Actor::InitData& actorInitData, const InitData& initData)
	: Super(actorInitData),
	damage(initData.damage),
	weaponDamage(initData.weaponDamage)
{
	timer.SetTargetTime(initData.lifeTime);
	SetCollisionFilter(CollisionFilter{ BULLET, 0 });

	Effect::Init(effectSequence[initData.dirIdx], sizeof(effectSequence) / sizeof(effectSequence[0]));
}

void Railslug::BeginPlay()
{
	Super::BeginPlay();

	timer.Reset();
}

void Railslug::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (timer.IsTimeOut())
	{
		Destroy();
		return;
	}
}
