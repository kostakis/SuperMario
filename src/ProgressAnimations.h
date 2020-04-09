#pragma once
#ifndef PROGRESSANIMATIONS_H
#define PROGRESSANIMATIONS_H

#include "Game.h"
#include "Animation_FrameRange.h"
#include "FrameRangeAnimator.h"
#include "Player.h"
#include "GameObject.h"
#include "Starman.h"
#include "Coin.h"

#define drawing_offset 5

namespace Progress {
	namespace Player_p {
		void Moving(Game& game) {
			string size = playerSizeString[static_cast<int>(game.getPlayer()->getMarioSize())];
			string direction = playerDirectionString[static_cast<int>(game.getPlayer()->getDirection())];
			string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
			std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
			bool started = game.getPlayer()->getAnimationStarted();
			if (direction == "LEFT") {
				int dx = -1;
				int dy = 1;
				FilterGridMotion(&grid, game.getPlayer()->GetBox(), &dx, &dy);
				if (dy) {//We can move down so we start fall dawn animator
					game.getPlayer()->getFrameRangeAnimator()->Stop();
					game.getPlayer()->setIsFalling(true);
					game.getPlayer()->getJumpDownAnimator()->Start(game.getPlayer()->getJumpLeftAnimation(), game.getCurrentTime());
					return;
				}
				temp.front()->setDrawing(game.getPlayer()->GetDrawingX() - 3, game.getPlayer()->GetDrawingY() - drawing_offset + 2);
				temp.front()->SetPos(game.getPlayer()->GetX(), game.getPlayer()->GetY());
				if (!started) {
					game.getPlayer()->getFrameRangeAnimator()->Start(game.getPlayer()->getLeftFrameRangeAnimation(), game.getCurrentTime());
				}
			}
			else if (direction == "RIGHT") {
				int dx = 1;
				int dy = 1;
				FilterGridMotion(&grid, game.getPlayer()->GetBox(), &dx, &dy);
				if (dy) {//We can move down so we start fall dawn animator
					game.getPlayer()->getFrameRangeAnimator()->Stop();
					game.getPlayer()->setIsFalling(true);
					game.getPlayer()->getJumpDownAnimator()->Start(game.getPlayer()->getJumpRightAnimation(), game.getCurrentTime());
					return;
				}
				temp.front()->setDrawing(game.getPlayer()->GetDrawingX() - 3, game.getPlayer()->GetDrawingY() - drawing_offset);
				temp.front()->SetPos(game.getPlayer()->GetX(), game.getPlayer()->GetY());
				if (!started) {
					game.getPlayer()->getFrameRangeAnimator()->Start(game.getPlayer()->getRightFrameRangeAnimation(), game.getCurrentTime());
				}
			}

		}

		void JumpUp(Game& game) {
			game.getPlayer()->getFrameRangeAnimator()->Stop();

			string size = playerSizeString[static_cast<int>(game.getPlayer()->getMarioSize())];
			string direction = playerDirectionString[static_cast<int>(game.getPlayer()->getDirection())];
			string to_change("MARIO_" + size + "_JUMP_" + direction);
			std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
			bool started = game.getPlayer()->getStartedMovingAnimator();
			if (direction == "RIGHT") {
				if (!started) {
					game.getPlayer()->getJumpUpAnimator()->Start(game.getPlayer()->getJumpRightAnimation(), game.getCurrentTime());
				}
			}
			else if (direction == "LEFT") {
				if (!started) {
					game.getPlayer()->getJumpUpAnimator()->Start(game.getPlayer()->getJumpLeftAnimation(), game.getCurrentTime());
				}
			}
		}

		void JumpDown(Game& game) {
			game.getPlayer()->getFrameRangeAnimator()->Stop();

			string size = playerSizeString[static_cast<int>(game.getPlayer()->getMarioSize())];
			string direction = playerDirectionString[static_cast<int>(game.getPlayer()->getDirection())];
			string to_change("MARIO_" + size + "_JUMP_" + direction);
			std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
			bool started = game.getPlayer()->getStartedMovingAnimator();
			if (direction == "RIGHT") {
				if (!started) {
					game.getPlayer()->getJumpDownAnimator()->Start(game.getPlayer()->getJumpRightAnimation(), game.getCurrentTime());
				}
			}
			else if (direction == "LEFT") {
				if (!started) {
					game.getPlayer()->getJumpDownAnimator()->Start(game.getPlayer()->getJumpLeftAnimation(), game.getCurrentTime());
				}
			}
		}

		void FlashAnimation(Game& game) {
			bool started = game.getPlayer()->getStartedFlashAnimaton();

			if (!started) {
				game.getPlayer()->getFlashAnimator()->Start(game.getPlayer()->getFlashAnimation(), game.getCurrentTime());
			}
		}
	}

	namespace AI {
		void Moving(Game& game) {
			auto& koopa_enemys = SpriteManager::GetInstance().getTypeList("KOOPA_TROOPA");
			auto viewdata = game.getView();
			auto max = DIV_TILE_WIDTH(viewdata->x + viewdata->width - 1);
			for (auto& i : koopa_enemys) {
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low < max) {
					KOOPA_TROOPA* temp = dynamic_cast<KOOPA_TROOPA*>(i);
					bool startedMoving = temp->getIsMoving();
					KOOPA_STATE state = temp->getState();
					temp->Display(NULL, viewdata);
					if (!startedMoving && state == KOOPA_STATE::MOVING) {
						temp->getMovingAnimator()->Start(temp->getMovingAnimation(), game.getCurrentTime());
					}

					if (state == KOOPA_STATE::KICK) {
						bool started = temp->getStartedKick();
						if (started) {
							temp->getMovingAnimation()->SetDelay(4);
							temp->getMovingAnimator()->Start(temp->getMovingAnimation(), game.getCurrentTime());
						}
					}
				}
			}

			auto& goomba_enemys = SpriteManager::GetInstance().getTypeList("GOOMBA_BROWN");
			for (auto& i : goomba_enemys) {
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low < max) {
					Goomba* temp = dynamic_cast<Goomba*>(i);
					bool started = temp->getIsMoving();
					bool destoyed = temp->getDestroyed();
					temp->Display(NULL, viewdata);
					if (!started && !destoyed) {
						temp->getFrameRangeAnimator()->Start(temp->getFrameRangeAnimation(), game.getCurrentTime());
					}
				}
			}


		}

		void Bricks(Game& game) {
			auto& bricks = SpriteManager::GetInstance().getTypeList("QUESTION_BRICK");
			auto viewdata = game.getView();
			auto max = DIV_TILE_WIDTH(viewdata->x + viewdata->width - 1);
			for (auto* i : bricks)
			{
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low <= max && (low >= DIV_TILE_WIDTH(viewdata->x))) {
					
					QuestionBrick* temp = static_cast<QuestionBrick*>(i);
					int timetouch = temp->getTimesTouched();
					int max = temp->getMaxTouches();
					bool started = temp->getStartedAnimation();
					temp->Display(NULL, viewdata);
					if (!started) {
						temp->getfrAnimator()->Start(temp->getfrAnimation(), game.getCurrentTime());
					}
					bool toplaymvanimation = temp->getToPlayMVAnimation();
					bool startedmvanimatoin = temp->getStartedmvAnimation();
					if (timetouch < max) {
						if (toplaymvanimation && !startedmvanimatoin) {
							temp->getmvAnimator()->Start(temp->getmvAnimation(), game.getCurrentTime());
						}
					}
				}
			}
			auto& simpleBricks = SpriteManager::GetInstance().getTypeList("SIMPLE_BRICK");
			for (auto* i : simpleBricks) {
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low <= max && (low + 10 >= DIV_TILE_WIDTH (viewdata->x)) ) {
					Brick* temp = static_cast<Brick*>(i);
					temp->Display(NULL, viewdata);
					bool toplaymvanimation = temp->getToPlayMVAnimation();
					bool startedmvanimatoin = temp->getStartedmvAnimation();
					if (toplaymvanimation && !startedmvanimatoin) {
						temp->getmvAnimator()->Start(temp->getmvAnimation(), game.getCurrentTime());
					}
				}
			}
		}

		void Coins(Game& game) {
			auto& coins = SpriteManager::GetInstance().getTypeList("COIN");
			auto viewdata = game.getView();
			auto max = DIV_TILE_WIDTH(viewdata->x + viewdata->width - 1);
			int temptime = game.getCurrentTime();
			for (auto* i : coins)
			{
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low < max && (low > DIV_TILE_WIDTH(viewdata->x))) {
					Coin* temp = static_cast<Coin*>(i);
					temp->Display(NULL, viewdata);
					bool started = temp->getStartedAnimation();
					bool upAnimation = temp->getPlayMVAnimation();
					bool startedMVAnim = temp->getStartedmvAnimation();
					if (!started && !upAnimation) {
						temp->getfrAnimator()->Start(temp->getfrAnimation(),temptime);
					}
					else if (upAnimation && !startedMVAnim) {
						temp->getmvAnimator()->Start(temp->getmvAnimation(), temptime);
					}
				}
			}
		}

		void GreenMush(Game& game) {
			auto& mush = SpriteManager::GetInstance().getTypeList("MUSHROOM_POWERUP_GREEN");
			auto viewdata = game.getView();
			auto max = DIV_TILE_WIDTH(viewdata->x + viewdata->width - 1);
			for (auto* i : mush)
			{
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low < max) {
					GreenMushroom* temp = static_cast<GreenMushroom*>(i);
					temp->Display(NULL, viewdata);
					bool started = temp->getStartedAnimation();
					bool startedMVAnim = temp->getStartedmvAnimation();
					if (!startedMVAnim) {
						temp->getmvAnimator()->Start(temp->getmvAnimation(), game.getCurrentTime());
					}
				}
			}

			auto& Redmush = SpriteManager::GetInstance().getTypeList("MUSHROOM_POWERUP_RED");
			for (auto* i : Redmush)
			{
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low < max) {
					RedMushroom* temp = static_cast<RedMushroom*>(i);
					temp->Display(NULL, viewdata);
					bool started = temp->getStartedAnimation();
					bool startedMVAnim = temp->getStartedmvAnimation();
					if (!startedMVAnim) {
						temp->getmvAnimator()->Start(temp->getmvAnimation(), game.getCurrentTime());
					}
				}
			}

			auto& starmans = SpriteManager::GetInstance().getTypeList("STARMAN");
			for (auto* i : starmans)
			{
				auto low = DIV_TILE_WIDTH(i->GetBox().x);
				if (low < max) {
					Starman* temp = static_cast<Starman*>(i);
					temp->Display(NULL, viewdata);
					bool started = temp->getStartedAnimation();
					bool startedMVAnim = temp->getStartedmvAnimation();
					if (!startedMVAnim) {
						temp->getmvAnimator()->Start(temp->getmvAnimation(), game.getCurrentTime());
					}

					bool startedFlash = temp->getStartedFlashAnimation();
					bool toplayFlash = temp->getToplayflashanimation();

					if (toplayFlash && !startedFlash) {
						temp->getflashanimator()->Start(temp->getflashanimation(), game.getCurrentTime());
					}

					if (toplayFlash == false && temp->getTookit() == false) temp->setstartedflashanimation(true);
				}
			}
		}
	}
}
#endif // !PROGRESSANIMATIONS_H