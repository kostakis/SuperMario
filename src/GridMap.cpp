#include "GridMap.h"
#include "TileActions.h"

void SetGridTile(GridMap* m, int col, int row, GridIndex index)
{
	(*m)[row][col] = index;
}

GridIndex GetGridTile(const GridMap* m, int col, int row)
{
	return (grid)[row][col];
}

void SetSolidGridTile(GridMap* m, int col, int row)
{
	SetGridTile(m, col, row, GRID_SOLID_TILE);
}

void SetEmptyGridTile(GridMap* m, int col, int row)
{
	SetGridTile(m, col, row, GRID_EMPTY_TILE);
}

void SetGridTileFlags(GridMap* m, int col, int row, GridIndex flags)
{
	SetGridTile(m, col, row, flags);
}

void SetGridTileTopSolidOnly(GridMap* m, int col, int row)
{
	SetGridTileFlags(m, row, col, GRID_TOP_SOLID_MASK);
}

bool CanPassGridTile(GridMap* m, int col, int row, GridIndex flags)
{
	return GetGridTile(m, row, col) & (flags != 0);
}

bool IsTileIndexAssumedEmpty(int index)
{
	if (index == 0 || index == 2 || index == 60 || index == 41 || index == 42 || index == 61) {
		return  false; //SOLID
	}
	else {
		return  true;  //EMPTY
	}
}

void ComputeTileGridBlocks1(const vector<vector<int>> tileMap, GridIndex* grid123)
{
	for (auto row = 0; row < tileMap.size(); ++row) {
		for (auto col = 0; col < tileMap[row].size(); ++col) {

			auto index = tileMap[row][col];
			if (index == 0 || index == 1 || index == 2 ||  index == 41 || index == 42 || index == 48 || index == 50 || index == 60 || index == 61
				|| index == 78 || index == 81 || index == 82 || index == 83 || index==97 || index == 100 || index == 101 || index == 102) {
				for (auto k = row; k < row + 4; k++)
				{
					for (auto l = col; l < col + 4; l++)
					{
						SetSolidGridTile(&grid, l, k);
					}
				}
			}
			else {

				for (auto k = row; k < row + 4; k++)
				{
					for (auto l = col; l < col + 4; l++)
					{
						SetEmptyGridTile(&grid, l, k);
					}
				}
			}
		}
	}
}

void DisplayGrid(ALLEGRO_BITMAP* buffer, ALLEGRO_DISPLAY* dest, const vector <vector<int> > tileMap, GridIndex* grid123, struct ViewData* vw)
{

	al_set_target_bitmap(buffer);
	al_hold_bitmap_drawing(1);
	auto startCol = DIV_TILE_WIDTH(vw->x);
	auto startRow = DIV_TILE_HEIGHT(vw->y);
	auto endCol = DIV_TILE_WIDTH(vw->x + vw->width - 1);
	auto endRow = DIV_TILE_HEIGHT(vw->y + vw->y - 1);

	for (auto row = 0; row < tileMap.size(); ++row) {
		for (auto col = startCol; col < endCol; ++col) {
			if (tileMap[row][col] >= 0) {
				int xx = MUL_TILE_WIDTH(col - startCol);
				int yy = (row * SCALED_HEIGHT);
				auto temp = GetGridTile(&grid, col, row) && GRID_SOLID_TILE;

				if (temp) {
					DrawSolid(xx, yy, row, col, startCol);
				}
				else {
					DrawEmpty(xx, yy, row, col, startCol);
				}
			}
		}
	}
	al_hold_bitmap_drawing(0);
}

void DrawSolid(int xx, int yy, int row, int col, int startCol)
{
	for (int k = row; k < row + 4; k++)
	{
		for (int l = col; l < col + 4; l++)
		{
			al_draw_rectangle(xx, yy, xx + GRID_ELEMENT_WIDTH, yy + GRID_ELEMENT_HEIGHT, al_map_rgb(255, 0, 0), 1); //KOKKINO
			xx += GRID_ELEMENT_WIDTH;
		}
		yy += GRID_ELEMENT_HEIGHT;
		xx = MUL_TILE_WIDTH(col - startCol);
	}
}

void DrawEmpty(int xx, int yy, int row, int col, int startCol)
{
	for (int k = row; k < row + 4; k++)
	{
		for (int l = col; l < col + 4; l++)
		{
			al_draw_rectangle(xx, yy, xx + GRID_ELEMENT_WIDTH, yy + GRID_ELEMENT_HEIGHT, al_map_rgb(0, 255, 0), 1); //PRASINO
			xx += GRID_ELEMENT_WIDTH;
		}
		yy += GRID_ELEMENT_HEIGHT;
		xx = MUL_TILE_WIDTH(col - startCol);
	}
}

void FilterGridMotionRight(GridMap* m, const Rectangle& r, int* dx, std::list<Point>* crossedTiles) {
	std::list<Point> l;
	auto x2 = r.x;
	auto x2_next = x2 + *dx;
	auto newCol = DIV_TILE_WIDTH(x2_next);
	auto currCol = DIV_TILE_WIDTH(x2);
	auto startRow = DIV_TILE_HEIGHT(r.y);
	auto endRow = DIV_TILE_HEIGHT(r.y + r.height - 1);
	for (auto row = startRow; row <= endRow; ++row) {
		auto temp = GetGridTile(&grid, newCol + *dx, row) && GRID_SOLID_TILE;
		if (temp) {//SOLID
			*dx = MUL_TILE_WIDTH(newCol) - (x2 + 1);
			l.clear();
			break;
		}
		else {//NON-SOLID
			//cout << "COL IS right" << newCol << endl;
			//cout << "row IS right" << row << endl;
			l.push_back({ newCol,row });
			std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
		}
		
	}
}

void FilterGridMotionLeft(GridMap* m, const Rectangle& r, int* dx, std::list<Point>* crossedTiles)
{
	if (r.x < 0) {
		*dx = 0;
		return;
	}

	std::list<Point> l;
	auto x2 = r.x;
	auto x2_next = x2 + *dx;
	auto newCol = DIV_TILE_WIDTH(x2_next);
	auto currCol = DIV_TILE_WIDTH(x2);
	auto startRow = DIV_TILE_HEIGHT(r.y);
	auto endRow = DIV_TILE_HEIGHT(r.y + r.height - 1);
	for (auto row = startRow; row <= endRow; ++row) {
		auto temp = GetGridTile(&grid, (newCol + *dx ) +  1, row) && GRID_SOLID_TILE;
		if (temp) {//SOLID
			*dx = /*MUL_TILE_WIDTH(newCol + *dx) - (x2 + 1);*/0;
			l.clear();
			break;
		}
		else {//NON-SOLID
			l.push_back({ (newCol),row });
			std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
		}

	}
}

void FilterGridMotionUp(GridMap* m, const Rectangle& r, int* dy, std::list<Point>* crossedTiles)
{
	if (r.y<0) {
		*dy = 0;
		return;
	}

	std::list<Point> l;
	auto y2 = r.y;
	auto y2_next = r.y + *dy;
	auto newRow = DIV_TILE_HEIGHT(y2_next);
	auto currRow = DIV_TILE_HEIGHT(y2);
	auto startCol = DIV_TILE_WIDTH(r.x);
	auto endCol = DIV_TILE_WIDTH(r.x + r.width - 1);
	for (auto col = startCol; col < endCol + 1; col++) {
		auto temp = GetGridTile(&grid,col, newRow) && GRID_SOLID_TILE;
		if (temp) {//SOLID
			*dy = MUL_TILE_HEIGHT(newRow - *dy) - (y2 + 1);
			l.clear();
			break;
		}
		else {//NON-SOLID
			l.push_back({ col,newRow });
			std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
		}
	}

}

void FilterGridMotionDown(GridMap* m, const Rectangle& r, int* dy, std::list<Point>* crossedTiles)
{
	if (r.y > SCREEN_HEIGHT) {
		*dy = 0;
		return;
	}

	std::list<Point> l;
	auto y2 = r.y;
	auto y2_next = r.y + *dy;
	auto newRow = DIV_TILE_HEIGHT(y2_next);
	auto currRow = DIV_TILE_HEIGHT(y2);
	auto startCol = DIV_TILE_WIDTH(r.x);
	auto endCol = DIV_TILE_WIDTH(r.x + r.width - 1);
	for (auto col = startCol; col < endCol + 1; col++) {
		auto temp = GetGridTile(&grid, col, newRow + 1) && GRID_SOLID_TILE;
		if (temp) {//SOLID
			*dy = /*MUL_TILE_HEIGHT(newRow + *dy) - (y2 + 1)*/0;
			l.clear();
			break;
		}
		else {//NON-SOLID
			l.push_back({ newRow,col });
			std::copy(l.begin(), l.end(), std::back_inserter(*crossedTiles));
		}
	}
}


void FilterGridMotion(GridMap* m, const Rectangle& r, int* dx, int* dy)
{
	/*assert(
		abs(*dx) <= GRID_ELEMENT_WIDTH && abs(*dy) <= GRID_ELEMENT_HEIGHT
	);*/

	std::list<Point> croossedTiles;

	// try horizontal move
	if (*dx < 0) {
		FilterGridMotionLeft(m, r, dx, &croossedTiles);
	}
	else if (*dx > 0) {
		FilterGridMotionRight(m, r, dx, &croossedTiles);
	}
	// try vertical move
	if (*dy < 0)
		FilterGridMotionUp(m, r, dy, &croossedTiles);
	else
		if (*dy > 0)
		FilterGridMotionDown(m, r, dy,&croossedTiles);

	for (auto& i : croossedTiles) {
		TileActions::GetSingleton().Trigger(i.x, i.y);
	}
}