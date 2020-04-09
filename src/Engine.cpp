#include "Engine.h"
#include <fstream>
#include "basic_includes.h"
#include <sstream>
#include "TileActions.h"

#define NUM_AUDIO_FILES 21

void Engine::Initialise()
{

	//Initilations
	if (!al_init()) {
		cerr << "Can't init allegro exiting" << endl;
		exit(EXIT_FAILURE);
	}

	if (!al_install_keyboard()) {
		cerr << "Can't init allegro keyboard exiting" << endl;
		exit(EXIT_FAILURE);
	}

	if (!al_install_mouse()) {
		cerr << "Can't init allegro mouse exiting" << endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_font_addon()) {
		cerr << "Can't init allegro font" << endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_image_addon()) {
		cerr << "Can't init allegro image" << endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_primitives_addon()) {
		cerr << "Can't init allegro primitives" << endl;
		exit(EXIT_FAILURE);
	}
	if (!al_install_audio()) {
		cerr << "Can't install allegro audio" << endl;
		exit(EXIT_FAILURE);
	}
	if (!al_init_acodec_addon()) {
		cerr << "Can't init allegro acodec" << endl;
		exit(EXIT_FAILURE);
	}
	if (!al_reserve_samples(NUM_AUDIO_FILES)) {
		cerr << "failed to reserve samples" << endl;
		exit(EXIT_FAILURE);
	}
	if (!al_init_ttf_addon()) {
		cerr << "failed to init font adodn" << endl;
		exit(EXIT_FAILURE);
	}
	/////////////////////


	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	map = al_create_bitmap(MAX_MAPWIDTH, MAX_MAPHEIGHT);

	if (!display) {
		cerr << "Can not create display" << endl;
		exit(EXIT_FAILURE);
	}

	if (!map) {
		cerr << "Can not create map" << endl;
		exit(EXIT_FAILURE);
	}

	tileLayer->Init(TILE_WIDTH, TILE_HEIGHT, bitMapPath);
	backgroundLayer->Init(TILE_WIDTH, TILE_HEIGHT, tileLayer->GetTileSet());
}

void Engine::Load()
{
	tileLayer->ReadTextMap(filePath); //Csv for the tile layer
	backgroundLayer->ReadText(backGroundPath);//Csv for background layer
	ComputeTileGridBlocks1(tileLayer->GetTileIndexes(), *grid);//Compute grid
}

void Engine::Clear()
{
	al_destroy_display(this->display);
	al_destroy_bitmap(this->map);
	delete tileLayer;
	delete backgroundLayer;

	al_shutdown_ttf_addon();
	al_shutdown_font_addon();
	al_shutdown_image_addon();
	al_shutdown_primitives_addon();
	al_uninstall_audio();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_system();
}

ALLEGRO_DISPLAY* Engine::getDisplay() const
{
	return display;
}

TileLayer* Engine::getTileLayer() const
{
	return tileLayer;
}

BackgroundLayer* Engine::getBackgroundLayer() const
{
	return backgroundLayer;
}

Engine::Engine(const string& filePathCsv, const string& bitMapPath, const string& backPath)
{
	this->filePath = filePathCsv;
	this->bitMapPath = bitMapPath;
	this->backGroundPath = backPath;
	this->tileLayer = new TileLayer();
	this->backgroundLayer = new BackgroundLayer();
}