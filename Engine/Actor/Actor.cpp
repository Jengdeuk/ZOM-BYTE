#include "Actor.h"

#include "Render/Renderer.h"

namespace JD
{
	Actor::Actor(const char* image, const Vector2& position, const Color color, const int sortingOrder)
		: position(position), color(color), sortingOrder(sortingOrder)
	{
		this->image = std::make_unique<char[]>(strlen(image) + 1);
		std::memcpy(this->image.get(), image, strlen(image) + 1);
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
		Renderer::Instance().Submit(image.get(), position, color, sortingOrder);
	}
}