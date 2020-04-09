#pragma once
#ifndef BASIC_INCLUDES_H
#define BASIC_INCLUDES_H
//#define NDEBUG
#include<allegro5/allegro.h> //Basic allegro library
#include<allegro5/allegro_font.h> //Font library
#include<allegro5/allegro_image.h>//Image library
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
//#include <assert.h>
#include <functional>
#include <set>
#include <map>
#include <algorithm> 

#include "Rectangle.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::function;
using std::set;
using std::map;
using std::min;
using std::cerr;
using namespace std::chrono;
typedef unsigned char byte;

inline int getRandom(int min, int max) {
	int range = max - min + 1;
	return rand() % range + min;
}

static const int MAP_WIDTH = 1000;
static const int MAP_HEIGHT = 1000;

#define MAX_MAPWIDTH 850
#define MAX_MAPHEIGHT 600

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i) ((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i) ((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i) ((i)&15)
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

#define SCALED_WIDTH 16
#define SCALED_HEIGHT 16

#define NUM_COLUMS 19

#define TILE_COUNT 252

#endif // !BASIC_INCLUDES_H