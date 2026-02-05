#pragma once

namespace JD
{
	class Timer
	{
	public:
		Timer(float targetTime = 1.0f);

	public:
		void Tick(float deltaTime);
	
	public:
		void Reset();
		bool IsTimeOut() const;
		void SetTargetTime(float newTargetTime);

	private:
		float elapsedTime = 0.0f;
		float targetTime = 0.0f;
	};
}
