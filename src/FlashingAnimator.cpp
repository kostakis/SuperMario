#include "FlashingAnimator.h"

void FlashAnimator::setCount(int _count)
{
	count = _count;
}

void FlashAnimator::Progress(timestamp_t currTime)
{
	int showDelay = anim->GetShowDeay();
	int hideDelay = anim->GetHideDeay();
	int timeDifference = currTime - lastTime;

	while ((currTime > lastTime) && ((currTime - lastTime) >= hideDelay)) {
		lastTime += hideDelay;
		NotifyAction(*anim);
		if (currState == 0) {
			currState = 1;
		}
		else {
			currState = 0;
		}

		if (++count == anim->GetRepetitions()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
	}
}

void FlashAnimator::Start(FlashAnimation* a, timestamp_t t)
{
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	currState = 0;
	NotifyStarted();
}

auto FlashAnimator::GetAnim(void) const -> const FlashAnimation&
{
	return *anim;
}

int FlashAnimator::getCurrentState() const
{
	return currState;
}
