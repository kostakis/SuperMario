#pragma once

#ifndef  ANIMATOR_MOVING
#define ANIMATOR_MOVING

#include "basic_includes.h"
#include "Animator.h"
#include "Animation_Moving.h"

class MovingAnimator : public Animator {
protected:
	MovingAnimation* anim = nullptr;
	unsigned currRep = 0; // animation state
public:
	void Progress(timestamp_t currTime);
	auto GetAnim(void) const -> const MovingAnimation&;
	void Start(MovingAnimation* a, timestamp_t t);
	MovingAnimator(void);
};
#endif // ! ANIMATOR_MOVING