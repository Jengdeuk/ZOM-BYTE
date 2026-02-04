#include "MenuLevel.h"

#include "Core/Input.h"
#include "Render/Renderer.h"

#include "Game/Game.h"

#include <memory>

using namespace JD;

MenuLevel::MenuLevel()
{
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
	Renderer::Instance().Submit("ZOM-BYTE", Vector2<int>(0, 0));

	for (int i = 0; i < static_cast<int>(items.size()); ++i)
	{
		Color textColor = (i == currentIndex ? selectedColor : unselectedColor);
		Renderer::Instance().Submit(items[i]->text.get(), Vector2<int>(0, 2 + i), textColor);
	}
}