#include "BackgroundLayer.h"
using namespace std;

BackgroundLayer::BackgroundLayer()
{
	this->TileSet = nullptr;
	this->bitmap = nullptr;
	this->xOff = 0;
	this->yOff = 0;
	this->rows = 0;
	this->total = 0;
	this->colums = 0;
	this->tileWidth = 0;
	this->tileHeight = 0;
}

BackgroundLayer::~BackgroundLayer()
{
	al_destroy_bitmap(bitmap);
}

void BackgroundLayer::createDivMod()
{
	for (int i = 0; i < total; ++i) {
		divIndex.push_back(i % NUM_COLUMS); // X
		modIndex.push_back(i / NUM_COLUMS); // Y
	}
}


void BackgroundLayer::Init( int w, int h, ALLEGRO_BITMAP* tileSet)
{
	this->tileWidth = w;
	this->tileHeight = h;
	this->TileSet = tileSet;
}

void BackgroundLayer::ReadText(const string& path)
{
	ifstream file(path);
	string line;

	int tempcols = 0;

	while (getline(file, line)) {//Reading line by line

		std::stringstream iss(line);
		std::string tempword;
		int count = 0;
		vector<int> temp;

		while (iss >> tempword) {
			std::string val;
			vector<int > temp;

			std::stringstream ss(tempword);
			std::string token;


			while (std::getline(ss, token, ',')) {
				int tempint = stoi(token);
				temp.push_back(tempint);
			}

			//Saving column
			if (temp.size() > tempcols) {
				tempcols = temp.size();
			}
			TileIndexes.push_back(temp);
			temp.clear();
		}
	}

	colums = tempcols;
	rows = TileIndexes.size();
	total = colums * rows;
	bitmap = al_create_bitmap(colums * tileWidth, rows * tileHeight);
	if (!bitmap) {
		cerr << "Can not create bitmap for background layer" << endl;
		exit(EXIT_FAILURE);
	}
	createDivMod();
}

void BackgroundLayer::setXoff(int x)
{
	this->xOff = x;
}

void BackgroundLayer::MoveXoff(int x)
{
	xOff += x;
}

void BackgroundLayer::setYoff(int y)
{
	this->yOff = y;
}

void BackgroundLayer::Display(ALLEGRO_BITMAP* buffer, struct ViewData* viewdata)
{
	auto startCol = DIV_TILE_WIDTH(viewdata->x);
	auto endCol = DIV_TILE_WIDTH(viewdata->x + viewdata->width - 1);
	al_hold_bitmap_drawing(1);
	for (auto i = 0; i < TileIndexes.size(); ++i) {
		for (auto j = startCol; j <= endCol; ++j) {
			auto x = divIndex[TileIndexes[i][j]];
			auto y = modIndex[TileIndexes[i][j]];
			al_draw_bitmap_region(TileSet, x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH,
				(j * TILE_WIDTH) - (viewdata->x), (i * TILE_HEIGHT), 0);
		}
	}
	al_hold_bitmap_drawing(0);
}

ALLEGRO_BITMAP* BackgroundLayer::getBitMap() const
{
	return this->bitmap;
}