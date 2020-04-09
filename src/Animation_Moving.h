#pragma once
#ifndef  ANIMATION_MOVING_H
#define ANIMATION_MOVING_H

#include "basic_includes.h"
#include "Animation.h"


class MovingAnimation : public Animation {
protected:
	unsigned reps = 1; // 0=forever
	int dx = 0, dy = 0;
	unsigned delay = 0;
public:

	MovingAnimation(const string& _id, unsigned _reps, int _dx, int _dy, unsigned _delay);
	MovingAnimation(void) = default;

	MovingAnimation& SetDx(int v);
	MovingAnimation& SetDy(int v);
	MovingAnimation& SetDelay(unsigned v);
	MovingAnimation& SetReps(unsigned n);
	MovingAnimation& SetForever(void);

	int GetDx(void) const;
	int GetDy(void) const;
	unsigned GetDelay(void) const;
	unsigned GetReps(void) const;
	bool IsForever(void) const;
	
};
#endif // ! ANIMATION_MOVING_H