#include "FrameRangeAnimator.h"

void FrameRangeAnimator::Progress(timestamp_t currTime) {
	while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {

		if (currFrame == anim->GetEndFrame()) {
			currFrame = anim->GetStartFrame(); // flip to start
		}
		else ++currFrame;

		lastTime += anim->GetDelay();
		NotifyAction(*anim);
		if (currFrame == anim->GetEndFrame())
			if (!anim->IsForever() && ++currRep == anim->GetReps()) {
				state = ANIMATOR_FINISHED;
				NotifyStopped();
				return;
			}
	}
}

unsigned FrameRangeAnimator::GetCurrFrame(void) const {
	return currFrame; 
}

unsigned FrameRangeAnimator::GetCurrRep(void) const {
	return currRep; 
}

void FrameRangeAnimator::Start(FrameRangeAnimation* a, timestamp_t t) {
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	currFrame = anim->GetStartFrame();
	currRep = 0;
	NotifyStarted();
	NotifyAction(*anim);
}