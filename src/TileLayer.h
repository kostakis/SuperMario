#pragma once
#ifndef TILELAYER_H
#define TILELAYER_H

#include "basic_includes.h"
#include "ViewData.h"

class TileLayer
{
private:
	ALLEGRO_BITMAP* bitmap;
	/*The image with the tiles*/
	ALLEGRO_BITMAP* TileSet;
	/*The tile indexes we read from a file*/
	vector < vector<int> > TileIndexes;
	vector <unsigned char> divIndex;
	vector <unsigned char> modIndex;
	vector < vector<bool> > toShow;
	int rows;
	int colums;
	int total;
	int TileWidth;
	int TileHeight;
	string csvPath;

	void CreateDivMod();
public:
	TileLayer();
	~TileLayer();

	void Init(int tileW, int tileH, const string& bitmappath);
	void ReadTextMap(string path);
	void Render(ALLEGRO_BITMAP* buffer, const struct ViewData* viewdata);


	int GetRows() const;
	int GetColumns() const;
	int GetTotal() const;
	int GetTileWidth() const;
	int GetTileHeight() const;
	ALLEGRO_BITMAP* GetTileSet() const;
	ALLEGRO_BITMAP* getBitmap() const;
	vector < vector<int> >  GetTileIndexes() const;
};

#endif // !TILELAYER_H