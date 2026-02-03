#pragma once

#include "Common/RTTI.h"

#include <memory>

namespace JD
{
	class Level;

	class JD_API Actor : public RTTI
	{
		RTTI_DECLARATIONS(Actor, RTTI)

	public:
		Actor();
		virtual ~Actor();

	public:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

	public:
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive && destroyRequested == false; }
		inline bool DestroyRequested() const { return destroyRequested; }
		
		inline void SetOwner(Level* newOwner) { owner = newOwner; }
		inline Level* GetOwner() const { return owner; }

	private:
		bool hasBeganPlay = false;
		bool isActive = true;
		bool destroyRequested = false;
		Level* owner = nullptr;
	};
}