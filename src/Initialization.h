#pragma once
#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "SoundManager.h"
#include "Game.h"
#include "Enemy.h"
#include "TileActions.h"
#include "CollisionChecker.h"

#define FALL_DEALY 6
#define UP_DEALY 6

static int dy_fall_counter = 0;
#define MAX_JUMP_COUNTER 70 //PEKSE ME AFTO
extern int jump_counter;

inline unsigned en(int a, int b) { //No idea just dont care
	return a * NUM_COLUMS + b;
}

namespace Init {

	void TileActions(Game& game);

	void Sounds(Game& game);

	void Fonts(Game& game);

	void Animations(Game& game);

	void Sprites(Player* p);



	namespace AnimatorActions {
		void FrameRangePlayer(Player* p);

		void JumpUpPlayer(Player* p);

		void JumpDownPlayer(Player* p);

		void FlashAnimatorPlayer(Player* p);
	}

}
#endif