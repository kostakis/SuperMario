#include "Animator.h"
#include "AnimatorManager.h"

Animator::Animator()
{
	AnimatorManager::GetInstance().Register(this);
}

void Animator::NotifyStopped(void)
{
	AnimatorManager::GetInstance().MarkAsSuspended(this);
	if (onFinish)
		(onFinish)(this);
}

void Animator::NotifyStarted(void)
{
	AnimatorManager::GetInstance().MarkAsRunning(this);
	if (onStart)
		(onStart)(this);
}

void Animator::NotifyAction(const Animation& anim)
{
	if (onAction) {
		(onAction)(this, anim);
	}
}

void Animator::Finish(bool isForced)
{
	if (!HasFinished()) {
 		state = isForced ? ANIMATOR_STOPPED : ANIMATOR_FINISHED;
		NotifyStopped();
	}
}

void Animator::Stop(void)
{
	Finish(true);
}


void Animator::TimeShift(timestamp_t offset)
{
	lastTime += offset;
}

bool Animator::HasFinished(void) const {
	return state != ANIMATOR_RUNNING;
}

Animator::~Animator()
{
	AnimatorManager::GetInstance().Cancel(this);
}