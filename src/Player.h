#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "basic_includes.h"
#include "AnimatorManager.h"
#include "Animator_Moving.h"
#include "Animation_Moving.h"
#include "Animation_FrameRange.h"
#include "Animation_Flash.h"
#include "SpriteManager.h"
#include "FrameRangeAnimator.h"
#include "Animation.h"
#include "Rectangle.h"
#include "ViewData.h"
#include "FlashingAnimator.h"

enum playerState {
	IDLE, RUNNING, MOVING
};

static string playerStateString[3] = {
	"IDLE",
	"RUNNING",
	"MOVING"
};

enum class p_direction {
	LEFT, RIGHT, UP, DOWN
};

static string playerDirectionString[4] = {
	"LEFT",
	"RIGHT",
	"UP",
	"DOWN"
};

enum class mario_size {
	SMALL, SUPER, INVINCIBLE
};

static string playerSizeString[3] = {
	"SMALL",
	"SUPER",
	"INVINCIBLE",
};

class Player :public Sprite

{
private:
	bool StartedAnimation;
	int HighScore;
	int Coins;
	int Lives;
	bool isJumping = false;
	bool isFalling = false;
	playerState p_State;
	p_direction d_State;
	mario_size size_state;
	int indiTime = 0;
	bool isINDESTRUCTIBLE = false;
	mario_size previousState;
	/*---------------------------------*/

	/*FrameRangeAnimator/Animation left-right*/
	FrameRangeAnimator* frameRangeAnimator;
	FrameRangeAnimation* frameRLeftAnimation;
	FrameRangeAnimation* frameRRightAnimation;
	/*---------------------------------------*/

	/*Moving Animator/Animation up-down*/
	MovingAnimator* JumpUpAnimator;
	MovingAnimator* JumpDownAnimator;
	MovingAnimation* jumpRightAnimation;
	MovingAnimation* jumpLeftAnimation;
	bool startedMovingAnimator;

	/*Flash Animation*/
	FlashAnimator* flashAnimator;
	FlashAnimation* flashAnimation;
	bool startedFlashAnimation;
	bool playFlashAnimaton = false;
	/*------------------------------*/
public:
	Player(int x, int y);
	~Player();

	void setDirection(p_direction d);
	void setState(playerState state);
	void setMarioSize(mario_size s);
	void setFrameRangeAnimator(FrameRangeAnimator* fra);
	void setFrameRangeRightAnimation(FrameRangeAnimation* anim);
	void setFrameRangeLeftAnimation(FrameRangeAnimation* anim);
	void setFlashAnimation(FlashAnimation* anim);
	void setAnimationStarted(const bool s);
	void setHighScore(int HighScore);
	void setCoins(int Coins);
	void setLives(int Lives);
	void setIsJumping(const bool& b);
	void setIsFalling(const bool& b);
	void setJumpRightAnimation(MovingAnimation* anim);
	void setJumpLeftAnimation(MovingAnimation* anim);
	void setStartedMovingAnim(bool b);
	void setStartedFlashAnimaton(bool b);
	void setPlayFlashAnimation(bool b);

	virtual void Display(ALLEGRO_BITMAP* bitmap, const struct ViewData);
	void bounceEffect();
	void IncreaseCoins(int coins);
	void IncreaseHighScore(int highScore);
	void IncreaseLives(int _lives);
	void DecreaseSize();
	void IncreaseIniTime(int _time);
	void makeIndi();
	void resetIndi();
	void removeLife(const int number);

	bool getIsIndi() const;
	int getIniTime() const;
	int getHighScore() const;
	int getCoins() const;
	int GetLives() const;
	playerState getState();
	p_direction getDirection() const;
	mario_size getMarioSize() const;
	FrameRangeAnimator* getFrameRangeAnimator() const;
	FrameRangeAnimation* getRightFrameRangeAnimation() const;
	FrameRangeAnimation* getLeftFrameRangeAnimation() const;
	FlashAnimation* getFlashAnimation() const;
	FlashAnimator* getFlashAnimator() const;
	bool getAnimationStarted() const;
	bool getIsJumping() const;
	bool getIsFalling() const;
	MovingAnimation* getJumpRightAnimation() const;
	MovingAnimation* getJumpLeftAnimation() const;
	MovingAnimator* getJumpUpAnimator() const;
	MovingAnimator* getJumpDownAnimator() const;
	bool getStartedMovingAnimator() const;
	Sprite* getCurrentSprite() const;
	bool getStartedFlashAnimaton() const;
	bool getPlayFlashAnimation() const;
};
#endif // !PLAYER_H