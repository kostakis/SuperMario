#pragma once
#ifndef AI_INITIALIZATION_H
#define AI_INITIALIZATION_H
#include "Enemy.h"
#include "CollisionChecker.h"
#include "Game.h"
#include "SoundManager.h"

int whatCollision(const Sprite* s1, const Sprite* s2);
void CreateTurtles(const Game& game);
void CreateGoomba(const Game& game);
void CreateBricks(const Game& game);
void CreateCoins(const Game& game);
void CreateQuestionBricks(const Game& game);

namespace Init {
	namespace AI {
		inline void EnemyAI(const Game& game) {
			CreateGoomba(game);
			CreateTurtles(game);
		}

		inline void Bricks(const Game& game) {
			CreateBricks(game);
			CreateQuestionBricks(game);
		}

		inline void Coins(const Game& game) {
			CreateCoins(game);
		}
	}
}
#endif // !AI_INITIALIZATION_H