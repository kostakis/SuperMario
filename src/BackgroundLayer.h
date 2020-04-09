#pragma once
#include "basic_includes.h"
#include "ViewData.h"

class BackgroundLayer
{
private:
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* TileSet;
	vector < vector<int> > TileIndexes;
	vector <unsigned char> divIndex;
	vector <unsigned char> modIndex;

	int tileWidth;
	int tileHeight;
	int colums;
	int rows;
	int total;
	int xOff;
	int yOff;
	void createDivMod();
public:
	BackgroundLayer();
	~BackgroundLayer();

	void Init(int w, int h, ALLEGRO_BITMAP* ts);
	void ReadText(const string& path);
	void setXoff(int x);
	void MoveXoff(int x);
	void setYoff(int y);
	void Display(ALLEGRO_BITMAP* buffer,struct ViewData *viewdata);

	ALLEGRO_BITMAP* getBitMap() const;
};