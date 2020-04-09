#pragma once
#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include "basic_includes.h"
#include <list>
#include "Sprites.h"
class SpriteManager final
{
public:
	using SpriteList = std::list<Sprite*>;
	using TypeLists = std::map<string, SpriteList>;

private:
	SpriteList dpyList;
	TypeLists types;
	SpriteManager(void) = default;
	~SpriteManager(void);
	SpriteManager(const SpriteManager&) = delete;
	SpriteManager(SpriteManager&&) = delete;
public:
	void CleanUp();
	void Add(Sprite* s);
	void Remove(Sprite* s);

	auto getDisplayList() -> const SpriteList& {
		return dpyList;
	}

	auto getTypeList(const string& typeId) -> const SpriteList& {
		return types[typeId];
	}

	static SpriteManager& GetInstance();
};
#endif// SPRITEMANAGER_H
