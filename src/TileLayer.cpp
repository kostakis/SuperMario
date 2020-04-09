#include "TileLayer.h"
using namespace std;

TileLayer::TileLayer()
{
	TileSet = NULL;
	bitmap = NULL;
	total = 0;
	rows = 0;
	colums = 0;
	TileHeight = -1;
	TileWidth = -1;
}

TileLayer::~TileLayer()
{
	al_destroy_bitmap(bitmap);
	al_destroy_bitmap(TileSet);
}

void TileLayer::Init(int tileW, int tileH, const string& bitmappath)
{
	TileWidth = tileW;
	TileHeight = tileH;
	TileSet = al_load_bitmap(bitmappath.c_str());
	if (!TileSet) {
		cerr << "Can not load tileset for tile layer" << endl;
		exit(EXIT_FAILURE);
	}
}

void TileLayer::ReadTextMap(string path)
{
	ifstream file(path);
	string line;

	int temprows = 0;
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
	bitmap = al_create_bitmap(colums * TileWidth, rows * TileHeight);
	if (!bitmap) {
		cerr << "Can not create bitmap for tile layer" << endl;
		exit(EXIT_FAILURE);
	}
	CreateDivMod();

	vector<bool> temp(colums, true);
	vector < vector<bool> > lala(rows, temp);
	toShow = lala;
	//toShow[40][0] = false;
	toShow[32][12] = false;
	toShow[32][13] = false;
	toShow[32][14] = false;

	toShow[32][50] = false;
	toShow[32][51] = false;
	toShow[32][52] = false;
	toShow[32][53] = false;
	toShow[32][54] = false;
	toShow[32][55] = false;

	toShow[32][105] = false;
	toShow[32][106] = false;
	toShow[32][107] = false;
	toShow[32][108] = false;

	toShow[29][113] = false;
	toShow[29][114] = false;
	toShow[29][115] = false;
	toShow[29][116] = false;
	toShow[29][117] = false;
	toShow[29][118] = false;
	toShow[29][119] = false;
	toShow[29][120] = false;
	toShow[29][121] = false;
	toShow[29][122] = false;
	toShow[29][123] = false;
	toShow[29][124] = false;
	toShow[29][125] = false;
	toShow[29][126] = false;

	toShow[30][167] = false;
	toShow[30][168] = false;
	toShow[30][169] = false;
	toShow[30][170] = false;
	toShow[30][171] = false;
	toShow[30][172] = false;
	toShow[30][173] = false;
	toShow[30][174] = false;
	toShow[30][175] = false;
	toShow[30][176] = false;
	toShow[30][177] = false;
	toShow[30][178] = false;
	toShow[30][179] = false;
	toShow[30][180] = false;
	toShow[30][181] = false;
	toShow[30][182] = false;
	toShow[30][183] = false;
	toShow[30][184] = false;
	toShow[30][185] = false;

	toShow[26][171] = false;
	toShow[26][172] = false;
	toShow[26][173] = false;
	toShow[26][174] = false;

	toShow[23][176] = false;
	toShow[23][177] = false;
	toShow[23][178] = false;
	toShow[23][179] = false;
	toShow[23][180] = false;
	toShow[23][181] = false;

	toShow[25][183] = false;
	toShow[25][184] = false;
	toShow[25][185] = false;

	toShow[23][186] = false;
	toShow[23][187] = false;
	toShow[23][188] = false;

	toShow[21][190] = false;
	toShow[21][191] = false;
	toShow[21][192] = false;

	toShow[32][187] = false;
	toShow[32][188] = false;
	toShow[32][189] = false;
	toShow[32][190] = false;
	toShow[32][191] = false;
	toShow[32][192] = false;
	toShow[32][193] = false;
	toShow[32][194] = false;
	toShow[31][191] = false;
	toShow[31][192] = false;
	toShow[31][193] = false;
	toShow[31][194] = false;

	toShow[19][193] = false;
	toShow[19][194] = false;
	toShow[19][195] = false;
	toShow[19][196] = false;
	toShow[19][197] = false;
	toShow[19][198] = false;
	toShow[19][199] = false;
	toShow[19][200] = false;
	toShow[19][201] = false;
	toShow[19][202] = false;
	toShow[19][203] = false;
	toShow[18][201] = false;
	toShow[18][202] = false;
	toShow[18][203] = false;

	toShow[16][205] = false;
	toShow[16][206] = false;
	toShow[16][207] = false;
	toShow[16][208] = false;
	toShow[16][209] = false;

	toShow[30][237] = false;
	toShow[30][238] = false;
	toShow[30][239] = false;
	toShow[30][240] = false;
	toShow[30][241] = false;
	toShow[30][242] = false;
	toShow[30][243] = false;
	toShow[30][244] = false;
	toShow[30][245] = false;
	toShow[30][246] = false;
	toShow[30][247] = false;
	toShow[30][248] = false;
	toShow[30][249] = false;

	toShow[31][288] = false;
	toShow[31][289] = false;
	toShow[31][290] = false;
	toShow[31][291] = false;
	toShow[31][292] = false;
	toShow[31][293] = false;
	toShow[31][294] = false;
	toShow[31][295] = false;
	toShow[31][296] = false;
	toShow[31][297] = false;
	toShow[31][298] = false;
	toShow[31][299] = false;
	toShow[28][291] = false;
	toShow[28][295] = false;
	toShow[19][334] = false;

	toShow[29][302] = false;
	toShow[29][303] = false;

	toShow[28][303] = false;
	toShow[28][304] = false;

	toShow[27][304] = false;
	toShow[27][305] = false;

	toShow[26][305] = false;
	toShow[26][306] = false;

	toShow[28][256] = false;
	toShow[19][204] = false;
	toShow[18][204] = false;

	for (int i = 306; i <= 328; i++)
	{
		toShow[25][i] = false;
	}
	toShow[24][307] = false;
	toShow[24][308] = false;

	for (int i = 331; i <= 338; i++)
	{
		toShow[23][i] = false;
	}
	toShow[22][331] = false;
	toShow[22][338] = false;

	toShow[32][109] = false;
	toShow[26][175] = false;

	toShow[13][206] = false;
	toShow[13][207] = false;
}

void TileLayer::Render(ALLEGRO_BITMAP* buffer, const struct ViewData* viewdata)
{
	al_hold_bitmap_drawing(1);

	auto startRow = DIV_TILE_HEIGHT(viewdata->y);
	auto endRow = DIV_TILE_HEIGHT(viewdata->y + viewdata->y - 1);
	auto startCol = DIV_TILE_WIDTH(viewdata->x);
	auto endCol = DIV_TILE_WIDTH(viewdata->x + viewdata->width - 1);

	for (auto i = 0; i < TileIndexes.size(); ++i) {
		for (auto j = startCol; j <endCol + 1; ++j) {
			if ((TileIndexes[i][j] >= 0) && (endCol <= TileIndexes[0].size()) && (toShow[i][j] == true)) {
				int x = divIndex[TileIndexes[i][j]];
				int y = modIndex[TileIndexes[i][j]];
				al_draw_bitmap_region(TileSet, x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH,
					(j * SCALED_WIDTH) - viewdata->x, (i * SCALED_HEIGHT) - viewdata->y, 0);
			}
		}
	}

	al_hold_bitmap_drawing(0); //optimization for allegro.
}

void TileLayer::CreateDivMod()
{
	for (int i = 0; i < total; ++i) {
		divIndex.push_back(i % NUM_COLUMS); // X
		modIndex.push_back(i / NUM_COLUMS); // Y
	}
}

int TileLayer::GetRows() const
{
	return rows;
}

int TileLayer::GetColumns() const
{
	return colums;
}

int TileLayer::GetTotal() const
{
	return total;
}

int TileLayer::GetTileWidth() const
{
	return TILE_WIDTH;
}

int TileLayer::GetTileHeight() const
{
	return TILE_HEIGHT;
}

ALLEGRO_BITMAP* TileLayer::GetTileSet() const
{
	return TileSet;
}

ALLEGRO_BITMAP* TileLayer::getBitmap() const
{
	return this->bitmap;
}

vector<vector<int>> TileLayer::GetTileIndexes() const
{
	return TileIndexes;
}