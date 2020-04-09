#pragma once
#ifndef  FRAMERANGEANIMTOR_H
#define FRAMERANGEANIMTOR_H

#include "basic_includes.h"
#include "Animator.h"
#include "Animation_FrameRange.h"
#include "Sprites.h"

class FrameRangeAnimator : public Animator {
protected:
	FrameRangeAnimation* anim = nullptr;
	unsigned currFrame = 0; // animation state
	unsigned currRep = 0; // animation state
public:
	FrameRangeAnimator(void) = default;
	void Progress(timestamp_t currTime);
	unsigned GetCurrFrame(void) const;
	unsigned GetCurrRep(void) const;
	void Start(FrameRangeAnimation* a, timestamp_t t);
};
#endif // ! ANIMATOR_FRAMERANGE