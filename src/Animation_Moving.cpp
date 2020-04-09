#pragma once
#include "Animation_Moving.h"

int MovingAnimation::GetDx(void) const {
	return dx;
}

MovingAnimation& MovingAnimation::SetDx(int v) {
	dx = v;
	return *this;
}

int MovingAnimation::GetDy(void) const {
	return dy;
}

MovingAnimation& MovingAnimation::SetDy(int v) {
	dy = v;
	return *this;
}

unsigned MovingAnimation::GetDelay(void) const {
	return delay;
}

MovingAnimation& MovingAnimation::SetDelay(unsigned v) {
	delay = v;
	return *this;
}

unsigned MovingAnimation::GetReps(void) const {
	return reps;
}

MovingAnimation& MovingAnimation::SetReps(unsigned n) {
	reps = n;
	return *this;
}

bool MovingAnimation::IsForever(void) const {
	return !reps;
}

MovingAnimation& MovingAnimation::SetForever(void) {
	reps = 0;
	return *this;
}

MovingAnimation::MovingAnimation(const std::string& _id, unsigned _reps, int _dx, int _dy, unsigned _delay) : Animation(_id), reps(_reps), dx(_dx), dy(_dy), delay(_delay)
{

}