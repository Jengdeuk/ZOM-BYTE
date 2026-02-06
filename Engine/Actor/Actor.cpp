#include "Actor.h"

#include "Render/Renderer.h"

#include "Engine/Engine.h"

namespace JD
{
	Actor::Actor(const InitData& initData)
		: position(initData.position),
		color(initData.color),
		sortingOrder(initData.sortingOrder)
	{
		if (initData.image == nullptr)
		{
			return;
		}

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
		//if (IsOutOfMap())
		//{
		//	return;
		//}

		//// 1. world space -> view space
		//Vector2<float> viewPosition = 

		//// 2. veiw space -> screen space

		Renderer::Instance().Submit(image.get(), Vector2<int>(position), color, sortingOrder);
	}

	void Actor::Destroy()
	{
		destroyRequested = true;
	}

	bool Actor::IsOutOfMap()
	{
		static const Vector2<float> mapHalfSize = Vector2<float>(Engine::Instance().GetMapSize()) * 0.5f;
		return position.x <= - mapHalfSize.x  || position.x >= mapHalfSize.x || position.y <= - mapHalfSize.y || position.y >= mapHalfSize.y;
	}
}
