#pragma once

#include "Common/Common.h"
#include "Math/Vector2.h"

namespace JD
{
	class Level;

	class JD_API Engine
	{
		struct EngineSetting
		{
			float frameRate = 0.0f;
			int width = 0;
			int height = 0;
		};

	private:
		Engine();
		virtual ~Engine();

		Engine(Engine&) = delete;
		Engine& operator=(Engine&) = delete;

	public:
		static Engine& Instance();

	public:
		void Run();
		void QuitEngine();
		void SetNewLevel(Level* newLevel);
		inline const Vector2<int> GetScreenSize() const { return Vector2<int>(setting.width, setting.height); }

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		void Draw();

	private:
		void LoadSetting();
		void Shutdown();

	private:
		bool isQuit = false;
		Level* mainLevel = nullptr;
		EngineSetting setting{};
	};
}
