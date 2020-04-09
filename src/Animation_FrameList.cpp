#pragma once
#include "Animation_FrameList.h"

const FrameListAnimation::Frames& FrameListAnimation::GetFrames(void) const
{
	return frames;
}
void FrameListAnimation::SetFrames(const Frames& f)
{
	frames = f;
}


FrameListAnimation::FrameListAnimation(
	const string& _id,
	const Frames& _frames,
	unsigned r, int dx, int dy, unsigned d, bool c
) : frames(_frames), MovingAnimation(id, r, dx, dy, d) {}