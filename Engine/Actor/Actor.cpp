#include "Actor.h"

#include "Render/Renderer.h"

namespace JD
{
	Actor::Actor(const char* image, const Vector2<int>& position, const Color color, const int sortingOrder)
		: position(position), color(color), sortingOrder(sortingOrder)
	{
		size_t length = strlen(image) + 1;
		this->image = std::make_unique<char[]>(length);
		std::memcpy(this->image.get(), image, length);
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