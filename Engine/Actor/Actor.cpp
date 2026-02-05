#include "Actor.h"

#include "Render/Renderer.h"

namespace JD
{
	Actor::Actor(const InitData& initData)
		: position(initData.position),
		color(initData.color),
		sortingOrder(initData.sortingOrder)
	{
		size_t length = strlen(initData.image) + 1;
		this->image = std::make_unique<char[]>(length);
		std::memcpy(this->image.get(), initData.image, length);
	}

	Actor::~Actor()
	{
	}

	void Actor::BeginPlay()
	{
		hasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::Draw()
	{
		Renderer::Instance().Submit(image.get(), Vector2<int>(position), color, sortingOrder);
	}
}
