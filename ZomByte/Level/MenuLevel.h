#pragma once

#include "Level/Level.h"
#include "Math/Color.h"

#include <memory>
#include <vector>

using namespace JD;

struct MenuItem
{
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
		: onSelected(onSelected)
	{
		size_t length = strlen(text) + 1;
		this->text = std::make_unique<char[]>(length);
		std::memcpy(this->text.get(), text, length);
	}

	std::unique_ptr<char[]> text;
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

public:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	int currentIndex = 0;
	Color selectedColor = Color::Green;
	Color unselectedColor = Color::White;
	std::vector<std::unique_ptr<MenuItem>> items;
};