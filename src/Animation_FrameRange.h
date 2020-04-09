#pragma once
#ifndef  ANIMATION_FRAMERANGE_H
#define ANIMATION_FRAMERANGE_H

#include "basic_includes.h"
#include "Animation_Moving.h"

class FrameRangeAnimation : public MovingAnimation {
protected:
	unsigned start = 0;
	unsigned end = 0;
public:
	FrameRangeAnimation(const string& _id, unsigned s, unsigned e, unsigned r, int dx, int dy, int d);
	FrameRangeAnimation(void) = default;

	Animation* Clone(void) const;

	FrameRangeAnimation& SetStartFrame(unsigned v);
	FrameRangeAnimation& SetEndFrame(unsigned v);

	unsigned GetStartFrame(void) const;
	unsigned GetEndFrame(void) const;
};
#endif // ! ANIMATION_FRAMERANGE_H