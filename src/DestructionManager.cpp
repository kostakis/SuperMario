#include "DestructionManager.h"
#include "CollisionChecker.h"

void DestructionManager::Register(LatelyDestroyable* d)
{
	//assert(!d->getAlive());
	dead.push_back(d);
}

void DestructionManager::Commit()
{
	for (auto* i : dead) {
		CollisionChecker::GetInstance().Cancel((Sprite*)i);
		i->Delete();
	}
	dead.clear();
}

DestructionManager& DestructionManager::GetInstance()
{
	static DestructionManager singleton;
	return singleton;
}

void LatelyDestroyable::Delete()
{
	//assert(!dying);
	dying = true;
	delete this;
}
