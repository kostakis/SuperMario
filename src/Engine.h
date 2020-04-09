#pragma once
#ifndef  ENGINE_H
#define ENGINE_H

#include "basic_includes.h"
#include "GridMap.h"
#include "TileLayer.h"
#include "BackgroundLayer.h"

class Engine
{
private:
	TileLayer* tileLayer = nullptr;
	BackgroundLayer* backgroundLayer = nullptr;
	string filePath;
	string bitMapPath; 
	string backGroundPath;

	// Our display
	ALLEGRO_DISPLAY* display = nullptr;
	//Map to display at the screen
	ALLEGRO_BITMAP* map = nullptr;

public:
	Engine() = default;
	Engine(const string& filePathCsv, const string& bitMapPath, const string& backgroundpath);
	~Engine() = default;

	void Initialise();
	void Load();
	void Clear();

	ALLEGRO_DISPLAY* getDisplay() const;
	TileLayer* getTileLayer() const;
	BackgroundLayer* getBackgroundLayer() const;
};
#endif // ! ENGINE_H