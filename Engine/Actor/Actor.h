#pragma once

#include "Common/RTTI.h"

#include "Math/Color.h"
#include "Math/Vector2.h"

#include <memory>

namespace JD
{
	class Level;

	class JD_API Actor : public RTTI
	{
		RTTI_DECLARATIONS(Actor, RTTI)

	public:
		Actor(const char* image = " ", const Vector2& position = Vector2::Zero, const Color color = Color::White, const int sortingOrder = 0);
		virtual ~Actor();

		Actor(const Actor&) = delete;
		Actor& operator=(const Actor&) = delete;

	public:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

	public:
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive && destroyRequested == false; }
		inline bool DestroyRequested() const { return destroyRequested; }
		
	public:
		inline void SetOwner(Level* newOwner) { owner = newOwner; }
		inline Level* GetOwner() const { return owner; }

		inline void SetPosition(const Vector2& newPosition) { position = newPosition; }
		inline Vector2 GetPosition() const { return position; }

	private:
		bool hasBeganPlay = false;
		bool isActive = true;
		bool destroyRequested = false;
		Level* owner = nullptr;

	private:
		std::unique_ptr<char[]> image = nullptr;
		Vector2 position{};
		Color color = Color::White;
		int sortingOrder = 0;
	};
}