#pragma once
#ifndef  ANIMATION_FLASH_H
#define ANIMATION_FLASH_H

#include "basic_includes.h"
#include "Animation.h"

class FlashAnimation : public Animation {
private:
	unsigned repetitions = 0;
	unsigned hideDelay = 0;
	unsigned showDelay = 0;
public:
	FlashAnimation(void) = default;

	FlashAnimation(const string& _id, unsigned n, unsigned show, unsigned hide) :
		Animation(id), repetitions(n), hideDelay(hide), showDelay(show) {}

	FlashAnimation& SetRepetitions(unsigned n) {
		repetitions = n;
		return *this;
	}
	FlashAnimation& SetHideDeay(unsigned d) {
		hideDelay = d;
		return *this;
	}
	FlashAnimation& SetShowDeay(unsigned d) {
		showDelay = d;
		return *this;
	}

	unsigned GetRepetitions(void) const {
		return repetitions;
	}
	unsigned GetHideDeay(void) const {
		return hideDelay;
	}
	unsigned GetShowDeay(void) const {
		return showDelay;
	}
};
#endif // ! ANIMATION_FLASH