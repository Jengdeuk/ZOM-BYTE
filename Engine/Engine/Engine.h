#pragma once

#include "Common/Common.h"

namespace JD
{
	class JD_API Engine
	{
		struct EngineSetting
		{
			float frameRate = 0.0f;
		};

	private:
		Engine();
		~Engine();

		Engine(Engine&) = delete;
		Engine& operator=(Engine&) = delete;

	public:
		static Engine& Instance();

	public:
		void Run();
		void QuitEngine();

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		void Draw();
		void Shutdown();

	private:
		void LoadSetting();

	private:
		bool isQuit = false;
		EngineSetting setting;
	};
}