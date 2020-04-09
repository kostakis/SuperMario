#pragma once
#ifndef  ANIMATION_SCROLL_H
#define ANIMATION_SCROLL_H
#include "basic_includes.h"
#include "Animation.h"

struct ScrollEntry {
	int dx = 0;
	int dy = 0;
	unsigned delay = 0;
};

class ScrollAnimation : public Animation {
private:
	vector<ScrollEntry> scroll;
public:
	const vector<ScrollEntry>& GetScroll(void) const;
	void SetScroll(const vector<ScrollEntry>& p);
	ScrollAnimation(const string& _id, const vector<ScrollEntry>& _scroll);
};
#endif // ! ANIMATION_SCROLL_H