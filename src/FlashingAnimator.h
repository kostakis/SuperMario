#pragma once
#ifndef FLASHINGANIMATOR_H
#define FLASHINGANIMATOR_H

#include "Animator.h"
#include "Animation_Flash.h"

class FlashAnimator :
	public Animator
{
protected:
	FlashAnimation* anim = nullptr;
	int currState = 0; //0 do hide, 1 do show
	int count = 0;
public:
	FlashAnimator(void) = default;

	void setCount(int _count);

	void Progress(timestamp_t currTime);
	void Start(FlashAnimation* a, timestamp_t t);

	auto GetAnim(void) const -> const FlashAnimation&;
	int getCurrentState() const;
};
#endif // !FLASHINGANIMATOR_H
