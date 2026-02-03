#include "Engine.h"

#include "Core/Input.h"
#include "Render/Renderer.h"

#include "Level/Level.h"

#include <Windows.h>
#include <iostream>

namespace JD
{
	Engine::Engine()
	{
		LoadSetting();
		Renderer::Instance().Init(Vector2(setting.width, setting.height));
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
				Input::Instance().ProcessInput();

				BeginPlay();
				Tick(deltaTime);
				Draw();

				previousTime = currentTime;
				Input::Instance().SavePreviousInputStates();
				if (mainLevel)
				{
					mainLevel->ProcessAddAndDestroyActors();
				}
			}
		}

		Shutdown();
	}

	void Engine::QuitEngine()
	{
		isQuit = true;
	}

	void Engine::SetNewLevel(Level* newLevel)
	{
		mainLevel = newLevel;
	}

	void Engine::BeginPlay()
	{
		if (mainLevel == nullptr)
		{
			DEBUG_BREAK("Error: Engine::BeginPlay(). mainLevel is empty.");
			return;
		}

		mainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		//std::cout << "Player::Tick(). deltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << '\n';
		if (mainLevel == nullptr)
		{
			DEBUG_BREAK("Error: Engine::Tick(). mainLevel is empty.");
			return;
		}

		mainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		if (mainLevel == nullptr)
		{
			DEBUG_BREAK("Error: Engine::Draw(). mainLevel is empty.");
			return;
		}

		mainLevel->Draw();

		Renderer::Instance().Draw();
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

		char* context = nullptr;
		char* token = nullptr;

		token = strtok_s(buffer, "\n", &context);
		while (token)
		{
			char header[10] = {};
			sscanf_s(token, "%s", header, 10);

			if (strcmp(header, "framerate") == 0)
			{
				sscanf_s(token, "framerate = %f", &setting.frameRate);
			}
			else if (strcmp(header, "width") == 0)
			{
				sscanf_s(token, "width = %d", &setting.width);
			}
			else if (strcmp(header, "height") == 0)
			{
				sscanf_s(token, "height = %d", &setting.height);
			}

			token = strtok_s(nullptr, "\n", &context);
		}

		fclose(file);
	}

	void Engine::Shutdown()
	{
	}
}