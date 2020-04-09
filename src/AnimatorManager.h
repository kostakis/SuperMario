#pragma once
#ifndef  ANIMATORMANAGER_H
#define ANIMATORMANAGER_H

#include "basic_includes.h"
#include "Animator.h"

class AnimatorManager {
private:
	set<Animator*> running, suspended;
	AnimatorManager(void) = default;
	~AnimatorManager(void) = default;
	AnimatorManager(const AnimatorManager&) = delete;
	AnimatorManager(AnimatorManager&&) = delete;
public:
	void Register(Animator* a);
	void Cancel(Animator* a);
	void MarkAsRunning(Animator* a);
	void MarkAsSuspended(Animator* a);
	void Progress(timestamp_t currTime);
	void Timeshift(timestamp_t newTime);
	static AnimatorManager& GetInstance();
};
#endif // ! ANIMATOR_MANAGER