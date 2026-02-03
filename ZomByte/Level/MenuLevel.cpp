#include "MenuLevel.h"

#include "Render/Renderer.h"

using namespace JD;

MenuLevel::MenuLevel()
{
}

MenuLevel::~MenuLevel()
{
}

void MenuLevel::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void MenuLevel::Draw()
{
	Renderer::Instance().Submit("ZOM-BYTE", Vector2::Zero);
}