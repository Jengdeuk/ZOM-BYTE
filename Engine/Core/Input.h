#pragma once

#include "Common/Common.h"

namespace JD
{
	class JD_API Input
	{
		friend class Engine;

		struct KeyState
		{
			bool isKeyDown = false;
			bool wasKeyDown = false;
		};

	private:
		Input();
		~Input();

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

	public:
		static Input& Instance();

	public:
		bool GetKeyDown(int keyCode);
		bool GetKeyUp(int keyCode);
		bool GetKey(int keyCode);

	private:
		void ProcessInput();
		void SavePreviousInputStates();

	private:
		KeyState keyState[255] = {};
	};
}