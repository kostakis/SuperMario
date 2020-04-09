#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <functional>
#include "basic_includes.h"
#include "Keys.h"
#include "GridMap.h"
#include "Player.h"
#include "TileLayer.h"
#include "BackgroundLayer.h"
#include "SystemClock.h"
#include "ViewData.h"
#include "AnimatorManager.h"
#include "Animator_Moving.h"
#include "Animation_Moving.h"
#include "Sprites.h"
#include "SpriteManager.h"
#include "PowerUp.h"
#include "Engine.h"

static int jump_counter = 0;
static bool left_once = false;
static bool pressed_once = false;

enum class active_player {
	MARIO, LUIGI
};

enum class gameState
{
	startScreen,
	mainGame,
	endGame,
	pauseScreen,
};

static bool enter_bonus_scene = false;

class Game
{
private:
	/*Layers*/
	TileLayer* tileLayer;
	BackgroundLayer* backgroundLayer;
	/*Display*/
	ALLEGRO_DISPLAY* display;
	/*Bitmap we draw to the screen*/
	ALLEGRO_BITMAP* buffer;
	/*Player*/
	Player* player;
	/*Bitmap for the start screen*/
	ALLEGRO_BITMAP* startBitmap;
	/*Bitmap for the pause screen*/
	ALLEGRO_BITMAP* pauseBitmap;
	/*General variables*/
	struct ViewData* viewData;
	bool finished;
	/*Current game state*/
	gameState state;
	active_player active;

	/*For allegro events/buttons/timers*/
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TIMER* timer;
	/*Text fonts*/
	ALLEGRO_FONT* textFont;
	/*General config file*/
	ALLEGRO_CONFIG* generalcfg;
	/* Timer events */
	int startTimer; //Seconds for the game to end
	uint64_t prevTime;
	uint64_t currTime;
	uint64_t pauseTime;
	string StartScreenPath;
	int xoffset;
	int yoffset;
	bool passed_half;
	bool gridDisplay;
	bool displayBackground = true;
	const float FPS = 140.0;
	float frameCounter = 0;
	void DisplayStartScreen();
	void DisplayPauseScreen();
	void DisplayEndScreen();
	void ProgressAnimations();
	void DisplayStats();
	void CheckConditions();
	const char* GetGeneralConfigValue(const string& text);
	bool playedGameOver = false;
	bool pauseSound = false;
	bool changedSoundSpeed = false;
	string to_display;
public:
	Game();
	~Game();

	void Init(const Engine&);
	void setState(gameState newstate);
	void setDisplay(ALLEGRO_DISPLAY* display);
	void setTileLayer(TileLayer* tl);
	void setBackgroundLayer(BackgroundLayer* bl);
	void setStartScreenPath(const std::string& path);
	void setTextFont(ALLEGRO_FONT* f);
	void setActivePlayer(active_player p);
	gameState getState() const;
	const char* player_to_string(const active_player value);
	void setViewData(int x, int y);
	void setDisplayBackground(bool b);

	void mainLoop();
	void mainLoopIteration();
	void Render();
	void AI();
	void UserActions();

	bool isFinished() const;
	ALLEGRO_DISPLAY* getDisplay() const;
	ALLEGRO_FONT* getTextFont() const;
	Player* getPlayer() const;
	active_player getActivePlayer() const;
	uint64_t getPrevTime();
	uint64_t getCurrentTime() const;
	struct  ViewData* getView() const;
};
#endif // ! GAME_H