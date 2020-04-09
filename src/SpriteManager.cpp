#include "SpriteManager.h"

void SpriteManager::CleanUp()
{
	for (auto& j : types) {
		if(j.second.size() >= 1) j.second.front()->Destroy();
	}
	types.clear();
	for (auto it = types.begin(); it != types.end(); )
			it = types.erase(it);
}

SpriteManager::~SpriteManager(void)
{
	CleanUp();
}

void SpriteManager::Add(Sprite* s)
{
	types[s->GetTypeId()].push_back(s);
}

void SpriteManager::Remove(Sprite* s)
{
	types[s->GetTypeId()].remove(s);
}

SpriteManager& SpriteManager::GetInstance()
{
	static SpriteManager instance;

	return instance;
}
