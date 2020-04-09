#include "Initialization.h"
#define SMALL_MARIO_BONUS_Y_OFFEST 4
#define SUPER_MARIO_BONUS_Y_OFFEST -10

void Init::TileActions(Game& game)
{
	TileActions::GetSingleton().SetEnumerator(en);//Dont care about this line

	/*For each tile type we want we define a function*/
	TileActions::GetSingleton().Install("Flagpole", [&](int r, int col) -> void {
		//cout << "telos_pistas" << endl;
		SoundManager::GetInstance().PlaySound("Flagpole", ALLEGRO_PLAYMODE_ONCE);
		});


	TileActions::GetSingleton().Install("telos_pistas", [&](int r, int col) -> void {
		//cout << "telos_pistas" << endl;
		SoundManager::GetInstance().PlaySound("Stage_clear", ALLEGRO_PLAYMODE_ONCE);
		game.setState(gameState::endGame);
		});

	TileActions::GetSingleton().Install("metavasi_skinis", [&](int r, int col) -> void {
		if (!enter_bonus_scene) {
			game.setDisplayBackground(false);
			SoundManager::GetInstance().StopSound("MainSound");
			SoundManager::GetInstance().PlaySound("BonusRoom", ALLEGRO_PLAYMODE_LOOP);
			string size = playerSizeString[static_cast<int>(game.getPlayer()->getMarioSize())];
			string direction = playerDirectionString[static_cast<int>(game.getPlayer()->getDirection())];
			string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
			std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
			game.setViewData(8000, 0);
			game.getPlayer()->SetX((8100));
			game.getPlayer()->SetY(5);
			game.getPlayer()->SetDrawingX(90);
			game.getPlayer()->SetDrawingY(-10);
			if (game.getPlayer()->getMarioSize() == mario_size::SMALL)
			{
				game.getPlayer()->SetDrawingX(90);
				game.getPlayer()->SetDrawingY(SMALL_MARIO_BONUS_Y_OFFEST);
			}
			else if (game.getPlayer()->getMarioSize() == mario_size::SUPER) {
				game.getPlayer()->SetDrawingX(90);
				game.getPlayer()->SetDrawingY(SUPER_MARIO_BONUS_Y_OFFEST);
			}
			else if (game.getPlayer()->getMarioSize() == mario_size::INVINCIBLE) {
				game.getPlayer()->SetDrawingX(90);
				game.getPlayer()->SetDrawingY(SUPER_MARIO_BONUS_Y_OFFEST);
			}
			temp.front()->SetPos(game.getPlayer()->GetX(), game.getPlayer()->GetY());
			temp.front()->setDrawing(game.getPlayer()->GetDrawingX(), game.getPlayer()->GetDrawingY());
			enter_bonus_scene = true;
		}
		});

	TileActions::GetSingleton().Install("epanafora_skinis", [&](int r, int col) -> void {
		SoundManager::GetInstance().StopSound("BonusRoom");
		SoundManager::GetInstance().PlaySound("MainSound", ALLEGRO_PLAYMODE_LOOP);
		string size = playerSizeString[static_cast<int>(game.getPlayer()->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(game.getPlayer()->getDirection())];
		string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		game.setDisplayBackground(true);
		game.setViewData(2070, 0);
		game.getPlayer()->SetX((2140));
		game.getPlayer()->SetY(500);
		if (game.getPlayer()->getMarioSize() == mario_size::SMALL)
		{
			game.getPlayer()->SetDrawingX(65);
			game.getPlayer()->SetDrawingY(500);
		}
		else if (game.getPlayer()->getMarioSize() == mario_size::SUPER) {
			game.getPlayer()->SetDrawingX(65);
			game.getPlayer()->SetDrawingY(485);
		}
		else if (game.getPlayer()->getMarioSize() == mario_size::INVINCIBLE) {
			game.getPlayer()->SetDrawingX(65);
			game.getPlayer()->SetDrawingY(485);
		}
		game.getPlayer()->setState(IDLE);
		});

	/*We define what tile are the type want*/
	/*The type must be installed first*/
	TileActions::GetSingleton().SetTag(432, 34, "telos_pistas");
	TileActions::GetSingleton().SetTag(432, 33, "telos_pistas");

	/*TileActions::GetSingleton().SetTag(120, 31, "metavasi_skinis");
	TileActions::GetSingleton().SetTag(120, 32, "metavasi_skinis");*/
	TileActions::GetSingleton().SetTag(120, 33, "metavasi_skinis");
	TileActions::GetSingleton().SetTag(120, 34, "metavasi_skinis");

	TileActions::GetSingleton().SetTag(545, 33, "epanafora_skinis");
	TileActions::GetSingleton().SetTag(545, 34, "epanafora_skinis");
	TileActions::GetSingleton().SetTag(545, 32, "epanafora_skinis");

	TileActions::GetSingleton().SetTag(6545, 32, "Flagpole");
	TileActions::GetSingleton().SetTag(6545, 33, "Flagpole");
	TileActions::GetSingleton().SetTag(6545, 34, "Flagpole");
}

void Init::Sounds(Game& game)
{
	SoundManager::GetInstance().AddSound("MainSound", "media/sounds/Overworld.ogg");
	SoundManager::GetInstance().AddSound("LoseLife", "media/sounds/Lose a Life.ogg");
	SoundManager::GetInstance().AddSound("BonusRoom", "media/sounds/BonusRoom.ogg");
	SoundManager::GetInstance().AddSound("jumpSMALL", "media/sounds/mario_jump_small.ogg");
	SoundManager::GetInstance().EditSoundGain("jumpSMALL", 0.5);
	SoundManager::GetInstance().AddSound("jumpSUPER", "media/sounds/mario_jump-super.ogg");
	SoundManager::GetInstance().AddSound("Pause", "media/sounds/Pause.ogg");
	SoundManager::GetInstance().AddSound("Coin", "media/sounds/Coin.ogg");
	SoundManager::GetInstance().AddSound("Pipe", "media/sounds/Pipe.ogg");
	SoundManager::GetInstance().AddSound("Powerup", "media/sounds/Powerup.ogg");
	SoundManager::GetInstance().AddSound("Powerup_appears", "media/sounds/Powerup_appears.ogg");
	SoundManager::GetInstance().AddSound("Worldclear", "media/sounds/World_clear.ogg");
	SoundManager::GetInstance().AddSound("Gameover", "media/sounds/Gameover.ogg");
	SoundManager::GetInstance().AddSound("1-up", "media/sounds/1-up.ogg");
	SoundManager::GetInstance().AddSound("Bump", "media/sounds/Bump.ogg");
	SoundManager::GetInstance().AddSound("Kick", "media/sounds/Kick.ogg");
	SoundManager::GetInstance().AddSound("Stage_clear", "media/sounds/Stage_clear.ogg");
	SoundManager::GetInstance().AddSound("Flagpole", "media/sounds/Flagpole.ogg");
	SoundManager::GetInstance().AddSound("Stomp", "media/sounds/Stomp.ogg");
	SoundManager::GetInstance().AddSound("Blockhit", "media/sounds/blockhit.ogg");
	SoundManager::GetInstance().AddSound("Starman", "media/sounds/Starman.ogg");
	SoundManager::GetInstance().EditSoundGain("Blockhit", 1.5);
}

void Init::Fonts(Game& game)
{
	game.setTextFont(al_load_ttf_font("media/fonts/SuperMario256.ttf", 12, 0));
	if (game.getTextFont() == NULL) {
		cerr << "Can not load font" << endl;
		exit(EXIT_FAILURE);
	}
}

void Init::Animations(Game& game)
{
	/*Loading the films for all animations*/
	AnimationFilmHolder::GetInstance().LoadAll("config/mario_moves.cfg");
	AnimationFilmHolder::GetInstance().LoadAll("config/Enemys.cfg");
	AnimationFilmHolder::GetInstance().LoadAll("config/new_mario_moves.cfg");
	/*---------------------------------*/

	/*Frame range animations left-right*/
	FrameRangeAnimation* frameright = new FrameRangeAnimation("MARIO_SMALL_MOVING_SLOW_RIGHT",
		0, 2, 0, game.getPlayer()->GetDrawingX(), game.getPlayer()->GetDrawingY(), 100);
	FrameRangeAnimation* frameleft = new FrameRangeAnimation("MARIO_SMALL_MOVING_SLOW_LEFT",
		0, 2, 0, game.getPlayer()->GetDrawingX(), game.getPlayer()->GetDrawingY(), 100);
	game.getPlayer()->setFrameRangeRightAnimation(frameright);
	game.getPlayer()->setFrameRangeLeftAnimation(frameleft);
	/*---------------------------------*/

	/*Jumping animations*/
	MovingAnimation* jumpright = new MovingAnimation("MARIO_SMALL_JUMP_RIGHT", 0, game.getPlayer()->GetDrawingX(), game.getPlayer()->GetDrawingY(), UP_DEALY);
	MovingAnimation* jumpleft = new MovingAnimation("MARIO_SMALL_JUMP_LEFT", 0, game.getPlayer()->GetDrawingX(), game.getPlayer()->GetDrawingY(), UP_DEALY);
	game.getPlayer()->setJumpRightAnimation(jumpright);
	game.getPlayer()->setJumpLeftAnimation(jumpleft);
	/*-----------------*/

	/*Flashing animations*/
	FlashAnimation* flashAnimation = new FlashAnimation("MARIO_FLASH", 8, 120, 120);
	game.getPlayer()->setFlashAnimation(flashAnimation);
	/*------------------*/
}

void Init::Sprites(Player* p)
{
	/*MARIO SMALL*/
	AnimationFilm* temp = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SMALL_IDLE_RIGHT");
	Sprite* temp1 = new Sprite(0, 0, temp, "MARIO_SMALL_IDLE_RIGHT");

	AnimationFilm* temp2 = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SMALL_IDLE_LEFT");
	Sprite* temp3 = new Sprite(0, 0, temp2, "MARIO_SMALL_IDLE_LEFT");

	AnimationFilm* filmrightslow = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SMALL_MOVING_SLOW_RIGHT");
	Sprite* smallslowright = new Sprite(p->GetX(), p->GetY(), filmrightslow, "MARIO_SMALL_MOVING_SLOW_RIGHT");

	AnimationFilm* filmleftslow = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SMALL_MOVING_SLOW_LEFT");
	Sprite* smallslowleft = new Sprite(p->GetX(), p->GetY(), filmleftslow, "MARIO_SMALL_MOVING_SLOW_LEFT");

	AnimationFilm* filmjumpright = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SMALL_JUMP_RIGHT");
	Sprite* smalljumpright = new Sprite(p->GetX(), p->GetY(), filmjumpright, "MARIO_SMALL_JUMP_RIGHT");

	AnimationFilm* filmjumpleft = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SMALL_JUMP_LEFT");
	Sprite* smalljumpleft = new Sprite(p->GetX(), p->GetY(), filmjumpleft, "MARIO_SMALL_JUMP_LEFT");;
	/*---------------*/

	/*MARIO SUPER*/
	AnimationFilm* superidleright = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SUPER_IDLE_RIGHT");
	Sprite* superidlerightsprite = new Sprite(0, 0, superidleright, "MARIO_SUPER_IDLE_RIGHT");

	AnimationFilm* superidleleft = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SUPER_IDLE_LEFT");
	Sprite* superidleleftsprite = new Sprite(0, 0, superidleleft, "MARIO_SUPER_IDLE_LEFT");

	AnimationFilm* filmsuperightslow = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SUPER_MOVING_SLOW_RIGHT");
	Sprite* superslowright = new Sprite(p->GetX(), p->GetY(), filmsuperightslow, "MARIO_SUPER_MOVING_SLOW_RIGHT");

	AnimationFilm* filmsuperleftslow = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SUPER_MOVING_SLOW_LEFT");
	Sprite* superslowleft = new Sprite(p->GetX(), p->GetY(), filmsuperleftslow, "MARIO_SUPER_MOVING_SLOW_LEFT");

	AnimationFilm* filmjumpsuperight = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SUPER_JUMP_RIGHT");
	Sprite* superjumpright = new Sprite(p->GetX(), p->GetY(), filmjumpsuperight, "MARIO_SUPER_JUMP_RIGHT");

	AnimationFilm* filmsuperjumpleft = AnimationFilmHolder::GetInstance().GetFilm("MARIO_SUPER_JUMP_LEFT");
	Sprite* superjumpleft = new Sprite(p->GetX(), p->GetY(), filmsuperjumpleft, "MARIO_SUPER_JUMP_LEFT");
	/*---------------------------*/

	/*MARIO INVICIBLE */
	AnimationFilm* invmvright = AnimationFilmHolder::GetInstance().GetFilm("MARIO_INVINCIBLE_MOVING_SLOW_RIGHT");
	Sprite* invmvrightsprite = new Sprite(0, 0, invmvright, "MARIO_INVINCIBLE_MOVING_SLOW_RIGHT");

	AnimationFilm* invmvleft = AnimationFilmHolder::GetInstance().GetFilm("MARIO_INVINCIBLE_MOVING_SLOW_LEFT");
	Sprite* invmvleftsprite = new Sprite(0, 0, invmvleft, "MARIO_INVINCIBLE_MOVING_SLOW_LEFT");

	AnimationFilm* filmjumpleftinv = AnimationFilmHolder::GetInstance().GetFilm("MARIO_INVINCIBLE_JUMP_LEFT");
	Sprite* invjumpleft = new Sprite(p->GetX(), p->GetY(), filmjumpleftinv, "MARIO_INVINCIBLE_JUMP_LEFT");

	AnimationFilm* filmjumpinvight = AnimationFilmHolder::GetInstance().GetFilm("MARIO_INVINCIBLE_JUMP_RIGHT");
	Sprite* invjumpright = new Sprite(p->GetX(), p->GetY(), filmjumpinvight, "MARIO_INVINCIBLE_JUMP_RIGHT");

	AnimationFilm* invidleright = AnimationFilmHolder::GetInstance().GetFilm("MARIO_INVINCIBLE_IDLE_RIGHT");
	Sprite* invidlerightsprite = new Sprite(0, 0, invidleright, "MARIO_INVINCIBLE_IDLE_RIGHT");

	AnimationFilm* invidleleft = AnimationFilmHolder::GetInstance().GetFilm("MARIO_INVINCIBLE_IDLE_LEFT");
	Sprite* invidleleftsprite = new Sprite(0, 0, invidleleft, "MARIO_INVINCIBLE_IDLE_LEFT");
	/*---------------------------*/
}

void Init::AnimatorActions::FrameRangePlayer(Player* p)
{
	p->getFrameRangeAnimator()->SetOnStart([p](Animator*) -> void {
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->SetVisibility(true);
		p->setAnimationStarted(true);
		});

	p->getFrameRangeAnimator()->SetOnAction([p](Animator* a, const Animation& anim) -> void {
		FrameRangeAnimator* fr = (FrameRangeAnimator*)a;
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->SetFrame(fr->GetCurrFrame());
		});

	p->getFrameRangeAnimator()->SetOnFinish([p](Animator* a) ->void {
		p->setAnimationStarted(false);
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->SetVisibility(false);
		});
}

void Init::AnimatorActions::JumpUpPlayer(Player* p)
{
	p->getJumpUpAnimator()->SetOnStart([p](Animator*) -> void {
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_JUMP_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->SetVisibility(true);
		jump_counter = 0;
		p->setStartedMovingAnim(true);
		if (size == "SMALL") {
			SoundManager::GetInstance().PlaySound("jumpSMALL", ALLEGRO_PLAYMODE_ONCE);
		}
		else if (size == "SUPER") {
			SoundManager::GetInstance().PlaySound("jumpSUPER", ALLEGRO_PLAYMODE_ONCE);
		}
		else if (size == "INVINCIBLE") {
			SoundManager::GetInstance().PlaySound("jumpSUPER", ALLEGRO_PLAYMODE_ONCE);
		}
		});

	p->getJumpUpAnimator()->SetOnAction([p](Animator*, const Animation&) -> void {
		++jump_counter;
		if (p->getState() == IDLE || p->getState() == MOVING) {
			int dx = 0;
			int dy = -1;
			FilterGridMotion(&grid, p->GetBox(), &dx, &dy);
			if (dy == 0 || jump_counter >= MAX_JUMP_COUNTER) {
				p->getJumpUpAnimator()->Stop();
				p->setIsFalling(true);
				p->setIsJumping(false);
			}
			if (p->GetX() < MAX_MAPWIDTH / 2) {
				p->moveDrawing(dx, 0);
			}
			p->moveDrawing(0, dy);
			p->Move(dx, dy);
		}
		});

	p->getJumpUpAnimator()->SetOnFinish([p](Animator*) -> void {
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_JUMP_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->SetVisibility(false);
		p->setStartedMovingAnim(false);
		});
}

void Init::AnimatorActions::JumpDownPlayer(Player* p)
{
	p->getJumpDownAnimator()->SetOnStart([p](Animator*) -> void {
		jump_counter = 0;
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_JUMP_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->SetVisibility(true);
		p->setStartedMovingAnim(true);
		p->getJumpRightAnimation()->SetDelay(FALL_DEALY);
		p->getJumpLeftAnimation()->SetDelay(FALL_DEALY);
		});

	p->getJumpDownAnimator()->SetOnAction([p](Animator*, const Animation&) -> void {
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_JUMP_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		if (p->getState() == IDLE || p->getState() == MOVING) {
			int dx = 0;
			int dy = +1;
			FilterGridMotion(&grid, p->GetBox(), &dx, &dy);
			if (dy == 0) {
				p->getJumpDownAnimator()->Stop();
				p->setIsFalling(false);
				p->setIsJumping(false);
			}
			++dy_fall_counter;
			if (p->GetX() < MAX_MAPWIDTH / 2) {
				p->moveDrawing(dx, 0);
			}
			p->moveDrawing(0, dy);
			p->Move(dx, dy);
		}
		});

	p->getJumpDownAnimator()->SetOnFinish([p](Animator*) -> void {
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		string direction = playerDirectionString[static_cast<int>(p->getDirection())];
		string to_change("MARIO_" + size + "_JUMP_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->SetVisibility(false);
		jump_counter = 0;
		p->setIsFalling(false);
		p->setState(IDLE);
		p->setStartedMovingAnim(false);
		p->getJumpRightAnimation()->SetDelay(UP_DEALY);
		p->getJumpLeftAnimation()->SetDelay(UP_DEALY);
		});
}

void Init::AnimatorActions::FlashAnimatorPlayer(Player* p)
{
	p->getFlashAnimator()->SetOnStart([p](Animator*)->void {
		p->setStartedFlashAnimaton(true);
		p->setPlayFlashAnimation(true);
		});

	p->getFlashAnimator()->SetOnAction([p](Animator* a, const Animation&)->void {
		bool show = p->getFlashAnimator()->getCurrentState();
		if (!show) {
			Sprite* temp = p->getCurrentSprite();
			temp->SetVisibility(false);
		}
		else {
			Sprite* temp = p->getCurrentSprite();
			temp->SetVisibility(true);
		}
		});

	p->getFlashAnimator()->SetOnFinish([p](Animator*)->void {
		p->setStartedFlashAnimaton(false);
		p->setPlayFlashAnimation(false);
		p->getFlashAnimator()->setCount(0);
		});
}