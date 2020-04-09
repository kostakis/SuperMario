#pragma once
#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "basic_includes.h"
#include "ViewData.h"

#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i) ((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i) ((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i) ((i)&15)
#define GRID_ELEMENT_WIDTH 4
#define GRID_ELEMENT_HEIGHT 4
#if TILE_WIDTH % GRID_ELEMENT_WIDTH != 0
#error "TILE_WIDTH % GRID_ELEMENT_WIDTH must be zero!"
#endif
#if TILE_HEIGHT % GRID_ELEMENT_HEIGHT != 0
#error "TILE_HEIGHT % GRID_ELEMENT_HEIGHT must be zero!"
#endif
#define GRID_BLOCK_COLUMNS (TILE_WIDTH / GRID_ELEMENT_WIDTH)
#define GRID_BLOCK_ROWS (TILE_HEIGHT / GRID_ELEMENT_HEIGHT)
#define GRID_ELEMENTS_PER_TILE (GRID_BLOCK_ROWS * GRID_BLOCK_COLUMNS)
#define GRID_MAX_HEIGHT (4000 * GRID_BLOCK_ROWS)
#define GRID_MAX_WIDTH (4000 * GRID_BLOCK_COLUMNS)

#define GRID_THIN_AIR_MASK 0x0000 // element is ignored
#define GRID_LEFT_SOLID_MASK 0x0001 // bit 0
#define GRID_RIGHT_SOLID_MASK 0x0002 // bit 1
#define GRID_TOP_SOLID_MASK 0x0004 // bit 2
#define GRID_BOTTOM_SOLID_MASK 0x0008 // bit 3
#define GRID_GROUND_MASK 0x0010 // bit 4, keep objects top / bottom (gravity)
#define GRID_FLOATING_MASK 0x0020 // bit 5, keep objects anywhere inside (gravity)
#define GRID_EMPTY_TILE GRID_THIN_AIR_MASK
#define GRID_SOLID_TILE \
(GRID_LEFT_SOLID_MASK | GRID_RIGHT_SOLID_MASK | GRID_TOP_SOLID_MASK | GRID_BOTTOM_SOLID_MASK)

#define MAX_PIXEL_WIDTH MUL_TILE_WIDTH(MAX_MAPWIDTH)
#define MAX_PIXEL_HEIGHT MUL_TILE_HEIGHT(MAX_MAPHEIGHT)
#define DIV_GRID_ELEMENT_WIDTH(i) ((i)>>2)
#define DIV_GRID_ELEMENT_HEIGHT(i) ((i)>>2)
#define MUL_GRID_ELEMENT_WIDTH(i) ((i)<<2)
#define MUL_GRID_ELEMENT_HEIGHT(i) ((i)<<2)



using GridIndex = byte;
typedef GridIndex GridMap[GRID_MAX_WIDTH][GRID_MAX_HEIGHT];
static GridMap grid; // example of a global static grid

void SetGridTile(GridMap* m, int col, int row, GridIndex index);
GridIndex GetGridTile(const GridMap* m, int col, int row);

void SetSolidGridTile(GridMap* m, int col, int row);
void SetEmptyGridTile(GridMap* m, int col, int row);
void SetGridTileFlags(GridMap* m, int col, int row, GridIndex flags);
void SetGridTileTopSolidOnly(GridMap* m, int col, int row);
bool CanPassGridTile(GridMap* m, int col, int row, GridIndex flags);

bool IsTileIndexAssumedEmpty(int index);
void ComputeTileGridBlocks1(const vector<vector<int>> tileMap, GridIndex* grid);
void DisplayGrid(ALLEGRO_BITMAP* gridbitmap, ALLEGRO_DISPLAY* dest, const vector <vector<int> > tileMap, GridIndex* grid,  struct ViewData* vw);
void DrawSolid(int xx, int yy, int row, int col,int startCol);
void DrawEmpty(int xx, int yy, int row, int col, int startCol);

void FilterGridMotion(GridMap* m, const Rectangle& r, int* dx, int* dy);
void FilterGridMotionRight(GridMap* m, const Rectangle& r, int* dx, std::list<Point>* l);
void FilterGridMotionLeft(GridMap* m, const Rectangle& r, int* dx, std::list<Point>* l);
void FilterGridMotionUp(GridMap* m, const Rectangle& r, int* dy, std::list<Point>* l);
void FilterGridMotionDown(GridMap* m, const Rectangle& r, int* dy, std::list<Point>* l);
#endif // !GRIDMAP_H
