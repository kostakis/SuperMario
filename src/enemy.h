#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Sprites.h"
#include "Animator.h"
#include "Animator_Moving.h"
#include "FrameRangeAnimator.h"
#include "Animation_FrameRange.h"

enum class ENEMY_DIRECTION {
	LEFT, RIGHT
};

enum class KOOPA_STATE {
	MOVING, KICK, STUNNED
};

class Enemy :
	public Sprite
{
protected:
	/*Moving animations*/
	MovingAnimator* movingAnimator;
	MovingAnimation* movingAnimation;
	bool startedMoving = false;
	bool forceStop = false;
	bool changedDelay = false;
	int dealyMove = 20;
	int delayGravity = 10;
	bool destroyed = false;
	int destroyTime = 0;
	bool destroyedByBrick = false;

	virtual void CreateMovingAnimation() = 0;
	virtual void OnStartMoving() = 0;
	virtual void OnFinishMoving() = 0;
	virtual void OnActionMoving() = 0;

	/*General variables*/
	ENEMY_DIRECTION direction;
public:
	Enemy(void) = default;
	Enemy(ENEMY_DIRECTION dir, int _x, int _y, AnimationFilm* film, const string& type)
		:Sprite(_x, _y, film, type) {
		isVisible = true;
		movingAnimator = new MovingAnimator();
		movingAnimation = NULL;
		direction = dir;
	}

	virtual ~Enemy() {
		movingAnimator->Stop();
		delete movingAnimator;
	}

	void setEnemyDirection(const ENEMY_DIRECTION& dir) {
		direction = dir;
	}

	void setForceStop(bool b) {
		forceStop = b;
	}

	void setMovingAnimation(MovingAnimation* mv) {
		movingAnimation = mv;
	}

	void setDestroyedByBrick(int b) {
		destroyedByBrick = b;
	}

	void setDestroyed(bool b);

	void increaseDestroyTime(int time);
	void changeDirection() {
		if (direction == ENEMY_DIRECTION::LEFT) direction = ENEMY_DIRECTION::RIGHT;
		else direction = ENEMY_DIRECTION::LEFT;
	}

	int getDestroyTime() const;
	MovingAnimator* getMovingAnimator() const {
		return movingAnimator;
	}

	MovingAnimation* getMovingAnimation() const {
		return movingAnimation;
	}

	bool getIsMoving() const {
		return startedMoving;
	}
	ENEMY_DIRECTION getDirection() const {
		return direction;
	}

	bool getForceStop() const {
		return forceStop;
	}

	bool getDestroyeByBrick() const {
		return destroyedByBrick;
	}

	bool getDestroyed() const;
};

class KOOPA_TROOPA : public Enemy {
private:
	KOOPA_STATE koopa_state;
	bool startedKick = false;
	int timeStunned = 0;
	int kickDealy = 4;
	int how_much_moved = 0;

	void CreateMovingAnimation();
	void OnStartMoving();
	void OnFinishMoving();
	void OnActionMoving();
public:
	KOOPA_TROOPA(ENEMY_DIRECTION dir, int _x, int _y, AnimationFilm* film)
		:Enemy(dir, _x, _y, film, "KOOPA_TROOPA")
	{
		CreateMovingAnimation();
		OnStartMoving();
		OnFinishMoving();
		OnActionMoving();
		koopa_state = KOOPA_STATE::MOVING;
	}

	~KOOPA_TROOPA() {
		delete movingAnimation;
	}

	void setStartedKicked(bool b) {
		startedKick = b;
	}

	void increasteTimeStunned() {
		timeStunned++;
	}

	void resetStunTime() {
		timeStunned = 0;
	}

	void setState(KOOPA_STATE state) {
		koopa_state = state;
	}

	void increaseHowMuchMove(int i) {
		how_much_moved += i;
	}

	void setHowMuchMove(int i) {
		how_much_moved = i;
	}

	int getStunTime() const {
		return timeStunned;
	}

	int getStartedKick() const {
		return startedKick;
	}

	KOOPA_STATE getState() const {
		return koopa_state;
	}

	int getHowMuchMove() const {
		return how_much_moved;
	}

	MovingAnimation* getMovingAnimation() const {
		return movingAnimation;
	}

	virtual void Display(ALLEGRO_BITMAP* dest, const struct ViewData* viewdata) const;
};

class Goomba :public Enemy {
private:
	int frameRangeDelay = 120;
	int downdelay = 20;

	FrameRangeAnimation* framerangeanimation;
	FrameRangeAnimator* framerangeAnimator;

	void CreateMovingAnimation();
	void OnStartMoving();
	void OnFinishMoving();
	void OnActionMoving();
public:
	Goomba(ENEMY_DIRECTION dir, int _x, int _y, AnimationFilm* film)
		:Enemy(dir, _x, _y, film, "GOOMBA_BROWN")
	{
		framerangeAnimator = new FrameRangeAnimator();
		CreateMovingAnimation();
		OnStartMoving();
		OnFinishMoving();
		OnActionMoving();
	}

	~Goomba() {
		framerangeAnimator->Stop();
		delete framerangeanimation;
		delete framerangeAnimator;
	}

	FrameRangeAnimation* getFrameRangeAnimation() const;
	FrameRangeAnimator* getFrameRangeAnimator() const;

	virtual void Display(ALLEGRO_BITMAP* dest, const struct ViewData* viewdata) const;
};
#endif // !ENEMY_H
