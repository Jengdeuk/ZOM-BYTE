#include "Engine.h"

#include <Windows.h>
#include <iostream>

namespace JD
{
	Engine::Engine()
	{
		LoadSetting();
	}

	Engine::~Engine()
	{
	}

	Engine& Engine::Instance()
	{
		static Engine instance;
		return instance;
	}

	void Engine::Run()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		int64_t currentTime = 0;
		int64_t previousTime = 0;

		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		currentTime = time.QuadPart;
		previousTime = currentTime;

		setting.frameRate = (setting.frameRate == 0.0f ? 60.0f : setting.frameRate);

		float oneFrameTime = 1.0f / setting.frameRate;
		while (isQuit == false)
		{
			QueryPerformanceCounter(&time);
			currentTime = time.QuadPart;

			float deltaTime = static_cast<float>(currentTime - previousTime) / frequency.QuadPart;
			if (deltaTime >= oneFrameTime)
			{
				BeginPlay();
				Tick(deltaTime);
				Draw();

				previousTime = currentTime;
			}
		}

		Shutdown();
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	void Engine::BeginPlay()
	{
	}

	void Engine::Tick(float deltaTime)
	{
		std::cout << "Player::Tick(). deltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << '\n';
	}

	void Engine::Draw()
	{
	}

	void Engine::LoadSetting()
	{
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt");
		if (file == nullptr)
		{
			DEBUG_BREAK("Failed to open engine setting file.");
			return;
		}

		char buffer[2048] = {};
		size_t readSize = fread(buffer, sizeof(char), 2048, file);
		sscanf_s(buffer, "frameRate = %f", &setting.frameRate);

		fclose(file);
	}

	void Engine::Shutdown()
	{
	}
}