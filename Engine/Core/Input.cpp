#include "Input.h"

#include <Windows.h>

namespace JD
{
	Input::Input()
	{
	}

	Input::~Input()
	{
	}
	
	Input& Input::Instance()
	{
		static Input instance;
		return instance;
	}

	bool Input::GetKeyDown(int keyCode)
	{
		return keyState[keyCode].isKeyDown && keyState[keyCode].wasKeyDown == false;
	}

	bool Input::GetKeyUp(int keyCode)
	{
		return keyState[keyCode].isKeyDown == false && keyState[keyCode].wasKeyDown;
	}

	bool Input::GetKey(int keyCode)
	{
		return keyState[keyCode].isKeyDown && keyState[keyCode].wasKeyDown;
	}

	void Input::ProcessInput()
	{
		for (int i = 0; i < 255; ++i)
		{
			keyState[i].isKeyDown = ((GetAsyncKeyState(i) & 0x8000) > 0);
		}
	}

	void Input::SavePreviousInputStates()
	{
		for (int i = 0; i < 255; ++i)
		{
			keyState[i].wasKeyDown = keyState[i].isKeyDown;
		}
	}
}
