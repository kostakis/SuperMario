#pragma once
#ifndef  ANIMATION_MOVINGPATH_H
#define ANIMATION_MOVINGPATH_H

#include "basic_includes.h"
#include "Animation_Moving.h"
#include "Animation.h"

struct PathEntry {
	int dx = 0, dy = 0;
	unsigned frame = 0;
	unsigned delay = 0;
	PathEntry(void) = default;
	PathEntry(const PathEntry&) = default;
};

class MovingPathAnimation : public Animation {
public:
	using Path = vector<PathEntry>;
private:
	Path path;
public:
	MovingPathAnimation(const std::string& _id, const Path& _path) {
		path = _path;
		Animation(_id);
	}

	void SetPath(const Path& p) {
		path = p;
	}

	const Path& GetPath(void) const {
		return path;
	}
	
};
#endif // ! ANIMATION_MOVINGPATH_H
