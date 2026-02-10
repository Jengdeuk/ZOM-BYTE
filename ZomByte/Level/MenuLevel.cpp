#include "MenuLevel.h"

#include "Engine/Engine.h"

#include "Core/Input.h"
#include "Render/Renderer.h"

#include "Game/Game.h"

#include <memory>

using namespace JD;

MenuLevel::MenuLevel()
{
	LoadTitle("title.txt");

	items.emplace_back(std::make_unique<MenuItem>(
		"Resume Game",
		[]()
		{
			Game::Instance().ToggleMenu();
		}
	));

	items.emplace_back(std::make_unique<MenuItem>(
		"Quit Game",
		[]()
		{
			Game::Instance().QuitEngine();
		}
	));
}

MenuLevel::~MenuLevel()
{
}

void MenuLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	static int length = static_cast<int>(items.size());
	if (Input::Instance().GetKeyDown(VK_UP))
	{
		currentIndex = (length + currentIndex - 1) % length;
	}

	if (Input::Instance().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Input::Instance().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onSelected();
	}

	if (Input::Instance().GetKeyDown(VK_ESCAPE))
	{
		Game::Instance().ToggleMenu();

		currentIndex = 0;
	}
}

void MenuLevel::Draw()
{
	const Vector2<int> screenSize = Engine::Instance().GetScreenSize();

	const int imglen = static_cast<int>(titleImgSliced.size());
	for (int i = 0; i < imglen; ++i)
	{
		Renderer::Instance().Submit(titleImgSliced[i].get(), Vector2<int>(screenSize.x / 2 - 25, screenSize.y / 2 - 4 + i), Color::Green, 0);
	}
	
	//Renderer::Instance().Submit("ZOM-BYTE", Vector2<int>(screenSize.x / 2 - 4, screenSize.y / 2 - 1), Color::Green);

	for (int i = 0; i < static_cast<int>(items.size()); ++i)
	{
		Color textColor = (i == currentIndex ? selectedColor : unselectedColor);
		Renderer::Instance().Submit(
			items[i]->text.get(),
			Vector2<int>(
				screenSize.x / 2 - static_cast<int>(strlen(items[i]->text.get())) / 2,
				screenSize.y / 2 + 4 + i
			),
			textColor
		);
	}
}

void MenuLevel::LoadTitle(const char* filename)
{
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (file == nullptr)
	{
		DEBUG_BREAK("Failed to open background file.");
	}

	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	titleImg = std::make_unique<char[]>(fileSize + 1);

	size_t readSize = fread(titleImg.get(), sizeof(char), fileSize, file);

	int i = -1;
	while (true)
	{
		++i;

		if (titleImg[i] == '\0')
		{
			break;
		}

		if (titleImg[i] == '\n')
		{
			continue;
		}

		titleImgSliced.emplace_back(std::make_unique<char[]>(52));
		for (int j = 0; j < 51; ++j)
		{
			titleImgSliced.back()[j] = titleImg[i++];
		}
	}

	fclose(file);
}
