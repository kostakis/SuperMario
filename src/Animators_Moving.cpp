#include "Animator_Moving.h"

void MovingAnimator::Progress(timestamp_t currTime) {
	while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) 
	{
		lastTime += anim->GetDelay();
		NotifyAction(*anim);
		auto temp_a = (++currRep == anim->GetReps());
		auto temp_b = !anim->IsForever();
		if (temp_a && temp_b) 
		{
   			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
	}
}
auto MovingAnimator::GetAnim(void) const -> const MovingAnimation&
{
	return *anim;
}
void MovingAnimator::Start(MovingAnimation* a, timestamp_t t) {
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	currRep = 0;
	NotifyStarted();
}

MovingAnimator::MovingAnimator(void) = default;