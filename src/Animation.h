#pragma once
#ifndef  ANIMATION_H
#define ANIMATION_H
#include "basic_includes.h"

class Animation {
protected:
	string id;
public:
	Animation(void) = default;
	Animation(const string& _id) {
		id = _id;
	}
	virtual ~Animation(void) = default;

	void SetId(const string& _id) {
		id = _id;
	}

	const string& GetId(void) {
		return id;
	}

};
#endif // ! ANIMATION_H