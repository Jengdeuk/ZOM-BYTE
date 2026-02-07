#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace JD;

class Effect : public Actor
{
	RTTI_DECLARATIONS(Effect, Actor)

	struct EffectFrame
	{
		EffectFrame(
			const char* image,
			float playTime,
			Color color)
			: playTime(playTime), color(color)
		{
			size_t length = strlen(image) + 1;
			this->image = std::make_unique<char[]>(length);
			std::memcpy(this->image.get(), image, length);
		}

		EffectFrame(const EffectFrame&) = delete;
		EffectFrame& operator=(const EffectFrame&) = delete;

		std::unique_ptr<char[]> image;
		float playTime = 0.0f;
		Color color = Color::Gray;
	};

public:
	Effect(const Actor::InitData& initData);

protected:
	void Init(const EffectFrame* initSequence, const int size);

public:
	virtual void Tick(float deltaTime) override;

private:
	int effectSequenceCount = 0;
	int currentSequenceIndex = 0;
	const EffectFrame* sequence = nullptr;
	Timer timer;
};
