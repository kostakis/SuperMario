#pragma once
#ifndef DESTRUCTIONMANAGER_H
#define BACKGROUNDLAYER_H

#include "basic_includes.h"

class LatelyDestroyable;
class DestructionManager
{
private:
	std::list<LatelyDestroyable*> dead;
public:
	void Register(LatelyDestroyable* d);
	void Commit();

	static DestructionManager& GetInstance();
};

class LatelyDestroyable {
protected:
	friend class DestructionManager;
	bool alive = true;
	bool dying = false;
	virtual ~LatelyDestroyable() {
		//assert(dying);
	}
	void Delete();
public:
	LatelyDestroyable(void) = default;
	bool getAlive() const {
		return alive;
	}
	void Destroy() {
		if (alive) {
			alive = false;
			DestructionManager::GetInstance().Register(this);
		}
	}
};
#endif // !DESTRUCTIONMANAGER_H