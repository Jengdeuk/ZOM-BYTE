#pragma once

#include "Level/Level.h"

class MenuLevel : public JD::Level
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
};