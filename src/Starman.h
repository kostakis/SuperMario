#pragma once
#ifndef STARMAN_H
#define STARMAN_H
#include "GameObject.h"
#include "AnimationFilmHolder.h"
#include "Animation_Flash.h"
#include "FlashingAnimator.h"
#include "SpriteManager.h"
#include "PowerUp.h"
#include "Player.h"

class Starman :
	public PowerUp
{
private:
	FlashAnimation* flashanimation;
	FlashAnimator* flashanimator;
	bool toplayflashanimation = false;
	bool startedflashanimation = false;
	void OnStartflash();
	void OnActionflash();
	void OnFinishflash();
public:
	Starman(int _x, int _y, Player* p);
	~Starman();

	virtual void Collision(Player* p);

	bool getToplayflashanimation()
	{
		return toplayflashanimation;
	}

	bool getStartedFlashAnimation()
	{
		return startedflashanimation;
	}

	FlashAnimation* getflashanimation() {
		return flashanimation;
	}
	FlashAnimator* getflashanimator(){
		return flashanimator;
	}

	void setstartedflashanimation(bool b) {
		toplayflashanimation = b;
	}
};
#endif // ! STARMAN_H