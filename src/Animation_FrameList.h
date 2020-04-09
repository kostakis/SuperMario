#pragma once
#ifndef  ANIMATION_FRAMELIST_H
#define ANIMATION_FRAMELIST_H

#include "basic_includes.h"
#include "Animation_Moving.h"

class FrameListAnimation : public MovingAnimation {
public:
	using Frames = vector<unsigned>;
protected:
	Frames frames;
public:
	const Frames& GetFrames(void) const;
	void SetFrames(const Frames& f);
	FrameListAnimation(const string& _id, const Frames& _frames, unsigned r, int dx, int dy, unsigned d, bool c);
};
#endif  // ! ANIMATION_FRAMELIST_H