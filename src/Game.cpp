#include "Game.h"
#include "App.h"
#include "Player.h"
#include "TileActions.h"
#include "AnimationFilmHolder.h"
#include "SoundManager.h"
#include "Initialization.h"
#include "ProgressAnimations.h"
#include "Animation.h"
#include "UserActions.h"
#include "CollisionChecker.h"
#include "DestructionManager.h"
#include "AI_Initialization.h"
#include "Coin.h"

#define MAX_INI_TIME 12

void Game::DisplayStartScreen()
{
	al_set_target_bitmap(this->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	backgroundLayer->Display(this->buffer,this->viewData);
	tileLayer->Render(this->buffer, viewData);
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 360, 113, ALLEGRO_ALIGN_CENTRE, "University of Crete");
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 360, 126, ALLEGRO_ALIGN_CENTRE, "Department of Computer  Science");
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 360, 139, ALLEGRO_ALIGN_CENTRE, "CS-454 Development of Intelligent Interfaces and Games");
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 360, 153, ALLEGRO_ALIGN_CENTRE, "Term Project, Fall Semester 2019");
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 350, 400, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER TO START");
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 100, 100, ALLEGRO_ALIGN_CENTRE, "MARMARAS KOSTAKIS");
	DisplayStats();
	al_set_target_backbuffer(this->display);
	al_draw_bitmap(this->buffer, 0, 0, 0);
	al_draw_bitmap(this->startBitmap, 200, 200, 0);
	al_flip_display();
}

void Game::DisplayPauseScreen()
{
	Render();
	Progress::AI::Moving(*this);
	Progress::AI::Bricks(*this);
	Progress::AI::Coins(*this);
	Progress::AI::GreenMush(*this);
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 350, 400, ALLEGRO_ALIGN_CENTRE, "PAUSED");
	al_draw_bitmap(this->pauseBitmap, 200, 200, 0);
	al_flip_display();
}

void Game::DisplayEndScreen()
{
	al_set_target_bitmap(this->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	backgroundLayer->Display(this->buffer,this->viewData);
	tileLayer->Render(this->buffer, viewData);
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 350, 400, ALLEGRO_ALIGN_CENTRE, to_display.c_str());
	DisplayStats();
	al_set_target_backbuffer(this->display);
	al_draw_bitmap(this->buffer, 0, 0, 0);
	al_draw_bitmap(this->pauseBitmap, 200, 200, 0);
	al_flip_display();
}

void Game::ProgressAnimations()
{
	if (player->getPlayFlashAnimation()) {
		Progress::Player_p::FlashAnimation(*this);
	}
	
	if (player->getIsJumping()) {
		Progress::Player_p::JumpUp(*this);
	}
	else if (player->getIsFalling()) {
		Progress::Player_p::JumpDown(*this);
	}
	else if (player->getState() == MOVING)
	{
		Progress::Player_p::Moving(*this);
	}

	al_set_target_bitmap(buffer);
	Progress::AI::Moving(*this);
	Progress::AI::Bricks(*this);
	Progress::AI::Coins(*this);
	Progress::AI::GreenMush(*this);

	AnimatorManager::GetInstance().Progress(GetSystemTime());
	al_set_target_backbuffer(this->display);
	al_hold_bitmap_drawing(1);
	al_draw_bitmap(this->buffer, 0, 0, 0);
	al_hold_bitmap_drawing(0);
}

void Game::DisplayStats()
{
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 50, 20, ALLEGRO_ALIGN_CENTRE, player_to_string(active));
	al_draw_textf(this->textFont, al_map_rgb(255, 255, 255), 73, 33, ALLEGRO_ALIGN_RIGHT, "%3d", player->getHighScore());
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 300, 20, ALLEGRO_ALIGN_CENTRE, "COINS");
	al_draw_textf(this->textFont, al_map_rgb(255, 255, 255), 300, 33, ALLEGRO_ALIGN_RIGHT, "%3d", player->getCoins());
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 500, 20, ALLEGRO_ALIGN_CENTRE, "TIME");
	al_draw_textf(this->textFont, al_map_rgb(255, 255, 255), 510, 33, ALLEGRO_ALIGN_RIGHT, "%d", startTimer);
	al_draw_text(this->textFont, al_map_rgb(255, 255, 255), 700, 20, ALLEGRO_ALIGN_CENTRE, "LIVES");
	al_draw_textf(this->textFont, al_map_rgb(255, 255, 255), 700, 33, ALLEGRO_ALIGN_CENTRE, "%3d", player->GetLives());
}

void Game::CheckConditions()
{
	if (startTimer <= 0) {//No more time so game ends
		this->state = gameState::endGame;
		to_display = "Lost from time";
		SoundManager::GetInstance().StopSound("MainSound");
		SoundManager::GetInstance().StopSound("BonusRoom");
	}

	if (startTimer <= 50) {//Play faster sound
		if (!changedSoundSpeed) {
			SoundManager::GetInstance().EditSoundSpeed("MainSound", 1.14);
			SoundManager::GetInstance().EditSoundSpeed("BonusRoom", 1.14);
			changedSoundSpeed = true;
		}
	}

	if (player->GetLives() == 0) {
		this->state = gameState::endGame;
		to_display = "No more lifes";
		SoundManager::GetInstance().StopSound("MainSound");
		SoundManager::GetInstance().StopSound("BonusRoom");
	}

	if (player->GetY() >= 598) {
		this->state = gameState::endGame;
		to_display = "Lost!!!";
		//TODO play ending music
	}
}

Game::Game()
{
	this->buffer = NULL;
	this->backgroundLayer = NULL;
	this->tileLayer = NULL;
	this->display = NULL;
	this->finished = false;
	this->state = gameState::startScreen;
	this->xoffset = 0;
	this->yoffset = 0;
	this->event_queue = NULL;
	this->timer = NULL;
	this->prevTime = 0;
	this->currTime = 0;
	this->gridDisplay = false;
	this->player = new Player(1, 561);
	this->player->setDirection(p_direction::RIGHT);
	this->viewData = new ViewData();
	this->passed_half = false;
	this->startBitmap = NULL;
	this->pauseBitmap = NULL;
	this->textFont = NULL;
	this->active = active_player::MARIO;
	this->generalcfg = NULL;
	this->pauseTime = 0;
	this->startTimer = 0;
	this->ev;
}

void Game::Init(const Engine& engine)
{
	this->buffer = al_create_bitmap(MAP_WIDTH, MAP_HEIGHT);
	if (!buffer) {
		cerr << "Can not create buffer" << endl;
		exit(EXIT_FAILURE);
	}
	viewData->x = 0;
	viewData->y = 0;
	viewData->width = SCREEN_WIDTH;
	viewData->height = SCREEN_HEIGHT;
	setDisplay(engine.getDisplay());
	setTileLayer(engine.getTileLayer());
	setBackgroundLayer(engine.getBackgroundLayer());
	startBitmap = al_load_bitmap(this->StartScreenPath.c_str());
	pauseBitmap = al_load_bitmap(this->StartScreenPath.c_str());
	if (pauseBitmap == NULL || startBitmap == NULL) {
		cerr << "Cant not load pause screen" << endl;
		exit(EXIT_FAILURE);
	}
	generalcfg = al_load_config_file("config/general.cfg");
	if (!generalcfg) {
		cerr << "Can not load general config file" << endl;
		exit(EXIT_FAILURE);
	}
	initKeys();
	player->setLives(atoi(GetGeneralConfigValue("lives"))); //Load all the general stuff.
	const char* tempsize = GetGeneralConfigValue("size");
	string temp_size_cpp(tempsize);
	if (temp_size_cpp == "SMALL") {
		player->setDrawing(0, 544);
		player->setMarioSize(mario_size::SMALL);
	}
	else if (temp_size_cpp == "SUPER") {
		player->setDrawing(0, 557);
		player->setMarioSize(mario_size::SUPER);
	}
	else if (temp_size_cpp == "INVICIBLE") {
		player->setDrawing(0, 555);
		player->setMarioSize(mario_size::INVINCIBLE);
	}
	startTimer = atoi(GetGeneralConfigValue("timeend"));
	Init::TileActions(*this);
	Init::Sounds(*this);
	Init::Fonts(*this);
	Init::Animations(*this);
	Init::Sprites(player);
	Init::AI::EnemyAI(*this);
	Init::AI::Bricks(*this);
	Init::AI::Coins(*this);
	this->player->SetWidth(atoi(GetGeneralConfigValue("WIDTH")));
	this->player->SetHeight(atoi(GetGeneralConfigValue("HEIGHT")));
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		exit(-1);
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		cerr << "Can not create event queue" << endl;
		exit(EXIT_FAILURE);
	}
	al_start_timer(timer);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
}


void Game::setState(gameState newstate)
{
	this->state = newstate;
}

void Game::setDisplay(ALLEGRO_DISPLAY* display)
{
	this->display = display;
}

void Game::setTileLayer(TileLayer* tl)
{
	tileLayer = tl;
}

void Game::setBackgroundLayer(BackgroundLayer* bl)
{
	this->backgroundLayer = bl;
}

void Game::setStartScreenPath(const std::string& path)
{
	this->StartScreenPath = path;
}

void Game::setTextFont(ALLEGRO_FONT* f)
{
	this->textFont = f;
}

void Game::setActivePlayer(active_player p)
{
	this->active = p;
}

gameState Game::getState() const
{
	return this->state;
}

const char* Game::player_to_string(const active_player value)
{
	static const char* LUT[] = { "MARIO", "LUIGI" };
	return LUT[static_cast<int>(value)];
}

void Game::setViewData(int x, int y)
{
	this->viewData->x = x;
	this->viewData->y = y;
}

void Game::setDisplayBackground(bool b)
{
	this->displayBackground = b;
}

void  Game::mainLoop()
{
	while (!isFinished()) {
		mainLoopIteration();
	}

}

void Game::mainLoopIteration()
{
	CheckConditions();
	UserActions();
	if (this->state == gameState::endGame) {
		SoundManager::GetInstance().StopSound("MainSound");
		SoundManager::GetInstance().StopSound("BonusRoom");
		if (!playedGameOver) {
			//SoundManager::GetInstance().PlaySound("Gameover", ALLEGRO_PLAYMODE_ONCE);
			playedGameOver = true;
		}
		DisplayEndScreen();
	}
	else if (this->state == gameState::startScreen) {
		SoundManager::GetInstance().PlaySound("MainSound", ALLEGRO_PLAYMODE_LOOP);
		DisplayStartScreen();
	}
	else if (this->state == gameState::pauseScreen) {
		SoundManager::GetInstance().StopSound("MainSound");
		if (!pauseSound) {
			SoundManager::GetInstance().PlaySound("Pause", ALLEGRO_PLAYMODE_ONCE);
			pauseSound = true;
		}

		DisplayPauseScreen();
	}
	else if (this->state == gameState::mainGame) {
		pauseSound = false;
		prevTime = GetSystemTime();
		Render();
		AI();
		ProgressAnimations();
		CollisionChecker::GetInstance().Check();
		DestructionManager::GetInstance().Commit();

		al_flip_display();

		frameCounter++;
		if (frameCounter == 100) {
			frameCounter = 0;
			startTimer -= 1;
		}
		int temptime = GetSystemTime();
		/*Calculate current fps*/
		double delta = temptime - prevTime;
		double fps1 = (1.0f / delta) * 1400.0f;
		//cout << "FPS are " << fps1 << endl;
	}
}

const char* Game::GetGeneralConfigValue(const string& text)
{
	return al_get_config_value(generalcfg, "GENERAL", text.c_str());
}

bool Game::isFinished() const
{
	return this->finished;
}

void Game::Render()
{

	al_set_target_bitmap(this->buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	if (displayBackground)
		backgroundLayer->Display(this->buffer,this->viewData);
	tileLayer->Render(this->buffer, viewData);
	/*if (this->gridDisplay)
		DisplayGrid(this->buffer, this->display, tileLayer->GetTileIndexes(), *grid, viewData);*/
	DisplayStats();
	player->Display(NULL, *viewData);
	al_set_target_backbuffer(this->display);
	al_hold_bitmap_drawing(1);
	al_draw_bitmap(this->buffer, 0, 0, 0);
	al_hold_bitmap_drawing(0);
}

void Game::AI()
{
	auto& koopa_enemys = SpriteManager::GetInstance().getTypeList("KOOPA_TROOPA");
	auto& goomba_enemys = SpriteManager::GetInstance().getTypeList("GOOMBA_BROWN");
	auto& green_mush = SpriteManager::GetInstance().getTypeList("MUSHROOM_POWERUP_GREEN");

	for (auto* i : koopa_enemys) {
		KOOPA_TROOPA* temp = static_cast<KOOPA_TROOPA*>(i);
		if (frameCounter == 100 - 1) {
			if (temp->getState() == KOOPA_STATE::STUNNED) {
				temp->increasteTimeStunned();
			}

			if (temp->getDestroyed()) {
				temp->increaseDestroyTime(1);
			}
		}

		if (temp->getStunTime() >= 3 && temp->getState() == KOOPA_STATE::STUNNED) {//An h xelwna einai stunned gia 3 deyterolepta
			temp->resetStunTime();
			temp->setState(KOOPA_STATE::MOVING);
			temp->getMovingAnimator()->Start(temp->getMovingAnimation(), currTime);
		}

		if (temp->getDestroyTime() == 1 && temp->getDestroyeByBrick()) {
			temp->getMovingAnimation()->SetDx(0);
			temp->getMovingAnimation()->SetDy(1);
			temp->getMovingAnimation()->SetDelay(60);
			temp->setDestroyed(true);
			temp->SetDirectMotion(true);
		}

		if (temp->getDestroyed() && temp->getDestroyTime() >= 2) {
			temp->Destroy();
		}
	}

	for (auto* i : goomba_enemys) {
		Goomba* temp = static_cast<Goomba*>(i);
		if (frameCounter == 100 - 1) {
			if (temp->getDestroyed()) {
				temp->increaseDestroyTime(1);
			}
		}

		if (temp->getDestroyTime() == 1 && temp->getDestroyeByBrick()) {
			temp->getFrameRangeAnimation()->SetDx(0);
			temp->getFrameRangeAnimation()->SetDy(1);
			temp->getFrameRangeAnimation()->SetDelay(120);
			temp->setDestroyed(true);
			temp->SetDirectMotion(true);
		}

		if (temp->getDestroyed() && temp->getDestroyTime() >= 2) {
			temp->Destroy();
		}
	}

	if (player->getIsIndi()) {
		player->setPlayFlashAnimation(true);
	}

	if (player->getIsIndi() && frameCounter == 100 - 1) {
		player->IncreaseIniTime(1);
		if (player->getIniTime() == MAX_INI_TIME) {
			player->resetIndi();
		}
	}

	for (auto* i : green_mush) {
		GreenMushroom* temp = static_cast<GreenMushroom*>(i);
		int x = temp->GetX();
		if (x < viewData->x + 1) {
			temp->getfrAnimator()->Stop();
			temp->getmvAnimator()->Stop();
			temp->Destroy();
		}

		if (temp->GetY() >= 598) {
			temp->getfrAnimator()->Stop();
			temp->getmvAnimator()->Stop();
			temp->Destroy();
		}

		if (temp->GetY() <= 2) {
			temp->getfrAnimator()->Stop();
			temp->getmvAnimator()->Stop();
			temp->Destroy();
		}
	}
}

ALLEGRO_DISPLAY* Game::getDisplay() const
{
	return this->display;
}

ALLEGRO_FONT* Game::getTextFont() const
{
	return this->textFont;
}

Player* Game::getPlayer() const
{
	return this->player;
}

active_player Game::getActivePlayer() const
{
	return this->active;
}

uint64_t Game::getPrevTime()
{
	return this->prevTime;
}

uint64_t Game::getCurrentTime() const
{
	return this->currTime;
}

ViewData* Game::getView() const
{
	return this->viewData;
}

Game::~Game()
{
	auto& koopa_enemys = SpriteManager::GetInstance().getTypeList("KOOPA_TROOPA");
	for (auto* i : koopa_enemys) {
		i->Destroy();
	}

	auto& goomba_enemys = SpriteManager::GetInstance().getTypeList("GOOMBA_BROWN");
	for (auto* i : goomba_enemys) {
		i->Destroy();
	}

	auto& bricks = SpriteManager::GetInstance().getTypeList("QUESTION_BRICK");
	for (auto* i : bricks) {
		QuestionBrick* temp = static_cast<QuestionBrick*>(i);
		temp->getfrAnimator()->Stop();
		i->Destroy();
	}

	auto& Simplebricks = SpriteManager::GetInstance().getTypeList("SIMPLE_BRICK");
	for (auto* i : Simplebricks) {
		SimpleBrick* temp = static_cast<SimpleBrick*>(i);
		temp->getfrAnimator()->Stop();
		i->Destroy();
	}

	auto& coins = SpriteManager::GetInstance().getTypeList("COIN");
	for (auto* i : coins) {
		Coin* temp = static_cast<Coin*>(i);
		temp->getfrAnimator()->Stop();
		temp->getmvAnimator()->Stop();
		i->Destroy();
	}

	auto& greenmush = SpriteManager::GetInstance().getTypeList("MUSHROOM_POWERUP_GREEN");
	for (auto* i : greenmush) {
		GreenMushroom* temp = static_cast<GreenMushroom*>(i);
		temp->getmvAnimator()->Stop();
		i->Destroy();
	}

	auto& redmush = SpriteManager::GetInstance().getTypeList("MUSHROOM_POWERUP_RED");
	for (auto* i : redmush) {
		RedMushroom* temp = static_cast<RedMushroom*>(i);
		temp->getmvAnimator()->Stop();
		i->Destroy();
	}

	auto& star = SpriteManager::GetInstance().getTypeList("STARMAN");
	for (auto* i : star) {
		RedMushroom* temp = static_cast<RedMushroom*>(i);
		temp->getmvAnimator()->Stop();
		i->Destroy();
	}

	AnimationFilmHolder::GetInstance().CleanUp();
	SoundManager::GetInstance().CleanUp();
	DestructionManager::GetInstance().Commit();

	al_destroy_bitmap(startBitmap);
	al_destroy_bitmap(pauseBitmap);
	al_destroy_bitmap(buffer);
	al_destroy_font(textFont);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_config(generalcfg);
	delete viewData;
	delete player;

	SpriteManager::GetInstance().CleanUp();
	DestructionManager::GetInstance().Commit();
}