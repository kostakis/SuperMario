#pragma once
#ifndef  COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "basic_includes.h"
#include "Sprites.h"

class CollisionChecker final {
private:
	CollisionChecker(void) = default;
	~CollisionChecker() {
		entries.clear();
	}
	CollisionChecker(const CollisionChecker&) = delete;
	CollisionChecker(CollisionChecker&&) = delete;
public:
	using Action = function<void(Sprite * s1, Sprite * s2)>;
protected:
	using Entry = std::tuple<Sprite*, Sprite*, Action>;
	std::list<Entry> entries;
public:
	template <typename T>
	void Register(Sprite* s1, Sprite* s2, const T& f)
	{
		entries.push_back(std::make_tuple(s1, s2, f));
	}
	void Cancel(Sprite* s1, Sprite* s2);
	void Cancel(Sprite* s1);//TODO
	void Check(void) const;

	static CollisionChecker& GetInstance();
};
#endif // ! COLLISIONCHECKER_H
