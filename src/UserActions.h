#pragma once
#ifndef USERACTIONS_H
#define USERACTIONS_H

#include "Game.h"

extern int jump_counter;

void Game::UserActions() {

	int flag = 1;
	int temp1 = 1;

	while (flag)
	{
		al_wait_for_event(event_queue, &ev);

		/*Close game conditions*/
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			this->finished = true;
			flag = 0;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				this->finished = true;
				flag = 0;
			default:
				break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			currTime = GetSystemTime();
		}
		if (al_is_event_queue_empty(event_queue)) {
			flag = 0;
		}
		/*---------------------*/

		if (this->state == gameState::mainGame) {
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				/*if (key[KEY_RIGHT]) {
					viewData->x += 2;
				}

				if (key[KEY_LEFT]) {
					if (viewData->x > 2) {
						viewData->x -= 2;
					}
				}

				if (key[KEY_HOME]) {
					yoffset = 0;
					xoffset = 0;
				}

				if (key[KEY_END]) {
					yoffset = MAX_MAPHEIGHT / 2;
					xoffset = 0;
				}*/

				if (key[KEY_G]) {
					this->gridDisplay = true;
				}
				/*
				if (key[MOUSE_LEFT_BUTTON]) {

					ALLEGRO_MOUSE_STATE state;

					al_get_mouse_state(&state);
					if (state.buttons & 1) {

						if ((state.x <= (MAX_MAPWIDTH / 2) - SCALED_WIDTH) && state.x > 0)
						{
							xoffset = state.x;
						}

						if ((state.y <= (MAX_MAPHEIGHT / 2) - SCALED_HEIGHT) && state.y > 0)
						{
							yoffset = 4 * state.y;
						}
					}
				}*/
				/*	if (key[KEY_W]) {
						int dx = 0;
						int dy = -1;
						FilterGridMotion(&grid, player->GetBox(), &dx, &dy);
						player->Move(dx, dy);
						player->moveDrawing(dx, dy);
					}*/
					/*if (key[KEY_S]) {
						int dx = 0;
						int dy = +1;
						FilterGridMotion(&grid, player->GetBox(), &dx, &dy);
						player->Move(dx, dy);
						player->moveDrawing(dx, dy);
					}*/

				if (key[KEY_A]) {
					int dx = -1;
					int dy = 0;
					int num_loops = 1;
					if (key[LSHIFT]) {
						num_loops = 2;
					}
					player->setState(MOVING);
					player->setDirection(p_direction::LEFT);
					for (int i = 0; i < num_loops; i++) {
						if (player->GetDrawingX() > 0) {
							FilterGridMotion(&grid, player->GetBox(), &dx, &dy);
							player->moveDrawing(dx, dy);
							player->Move(dx, dy);
						}
					}
				}
				if (key[KEY_D]) {
					int dx = 1;
					int dy = 0;
					int num_loops = 1;
					if (key[LSHIFT]) {
						num_loops = 2;
					}
					player->setState(MOVING);
					player->setDirection(p_direction::RIGHT);
					for (int i = 0; i < num_loops; i++) {
						FilterGridMotion(&grid, player->GetBox(), &dx, &dy);
						player->Move(dx, dy);

						if (player->GetDrawingX() < MAX_MAPWIDTH / 2) {
							player->moveDrawing(dx, dy);
						}
						else {
							if (viewData->x >= 7996)
							{//No map scrolling for bonus stage we scroll mario
								player->moveDrawing(dx, dy);
							}
							else if (viewData->x < 7996) {
								passed_half = true;
								viewData->x += dx;
								backgroundLayer->MoveXoff(dx);
							}
						}
					}

				}
				if (key[SPACEBAR]) {
					if (player->getIsFalling() == false && (pressed_once == false)) {
						pressed_once = true;
						player->setIsJumping(true);
					}
				}
				if (key[LSHIFT]) {
				}
				if (key[KEY_Z]) {
					//player->resetXY();
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;

				case ALLEGRO_KEY_HOME:
					key[KEY_HOME] = true;
					break;

				case ALLEGRO_KEY_END:
					key[KEY_END] = true;
					break;
				case ALLEGRO_KEY_G:
					key[KEY_G] = true;
					break;
				case ALLEGRO_KEY_W:
					key[KEY_W] = true;
					break;
				case ALLEGRO_KEY_S:
					key[KEY_S] = true;
					break;
				case ALLEGRO_KEY_A:
					key[KEY_A] = true;
					break;
				case ALLEGRO_KEY_D:
					key[KEY_D] = true;
					break;
				case ALLEGRO_KEY_Z:
					key[KEY_Z] = true;
					break;
				case ALLEGRO_KEY_ESCAPE:
					break;
				case ALLEGRO_KEY_SPACE:
					key[SPACEBAR] = true;
					break;
				case ALLEGRO_KEY_F1:
					this->state = gameState::pauseScreen;
					pauseTime = currTime;
					break;
				case ALLEGRO_KEY_LSHIFT:
					if (player->getIsFalling() == false && player->getIsJumping() == false) {
						key[LSHIFT] = true;
					}
					break;
				}

			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
					player->setState(IDLE);
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					this->finished = true;
					flag = 0;

				case ALLEGRO_KEY_END:
					key[KEY_END] = false;
					break;

				case ALLEGRO_KEY_HOME:
					key[KEY_HOME] = false;
					break;
				case ALLEGRO_KEY_G:
					key[KEY_G] = false;
					this->gridDisplay = false;
					break;
				case ALLEGRO_KEY_W:
					key[KEY_W] = false;
					break;
				case ALLEGRO_KEY_S:
					key[KEY_S] = false;
					player->setState(IDLE);
					break;
				case ALLEGRO_KEY_A:
					key[KEY_A] = false;
					player->setState(IDLE);
					break;
				case ALLEGRO_KEY_D:
					key[KEY_D] = false;
					player->setState(IDLE);
					break;
				case ALLEGRO_KEY_Z:
					key[KEY_Z] = false;
					player->setState(IDLE);
					break;
				case ALLEGRO_KEY_SPACE:
					pressed_once = false;
					key[SPACEBAR] = false;
					left_once = false;
					player->getJumpUpAnimator()->Stop();
					player->setIsJumping(false);
					player->setIsFalling(true);
					break;
				case ALLEGRO_KEY_F1:
					key[F1_KEY] = false;
					SoundManager::GetInstance().PlaySound("MainSound", ALLEGRO_PLAYMODE_LOOP);
					break;
				case ALLEGRO_KEY_LSHIFT:
					key[LSHIFT] = false;
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
			}
			else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				key[MOUSE_LEFT_BUTTON] = true;
			}
			else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				key[MOUSE_LEFT_BUTTON] = false;
			}
			if (al_is_event_queue_empty(event_queue)) {
				//player->setState(IDLE);
				flag = 0;
			}

		}
		else if (this->state == gameState::startScreen) {
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (key[ENTER]) {
					this->state = gameState::mainGame;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ENTER:
					key[ENTER] = true;
					break;

				default:
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_ENTER:
					key[ENTER] = false;
					break;
				default:
					break;
				}
			}

			if (al_is_event_queue_empty(event_queue)) {
				flag = 0;
			}
		}
		else if (this->state == gameState::pauseScreen) {
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (key[F1_KEY]) {
					AnimatorManager::GetInstance().Timeshift(GetSystemTime() - pauseTime);
					player->setState(IDLE);
					this->state = gameState::mainGame;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_F1:
					key[F1_KEY] = true;
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_F1:
					key[F1_KEY] = false;
					break;
				default:
					break;
				}
			}
			if (al_is_event_queue_empty(event_queue)) {
				flag = 0;
			}
		}
	}
}
#endif // !USERACTIONS_H