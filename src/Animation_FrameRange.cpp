#pragma once
#include "Animation_FrameRange.h"

unsigned FrameRangeAnimation::GetStartFrame(void) const { 
	return start; 
}

FrameRangeAnimation& FrameRangeAnimation::SetStartFrame(unsigned v) { 
	start = v; 
	return *this; 
}

unsigned FrameRangeAnimation::GetEndFrame(void) const { 
	return end; 
}

FrameRangeAnimation& FrameRangeAnimation::SetEndFrame(unsigned v) {
	end = v; 
	return *this; 
}

FrameRangeAnimation::FrameRangeAnimation(
	const std::string& _id,
	unsigned s, unsigned e,
	unsigned r, int dx, int dy, int d
) : start(s), end(e), MovingAnimation(id, r, dx, dy, d) 
{

}