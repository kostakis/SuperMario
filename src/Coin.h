#pragma once
#ifndef COIN_H
#define COIN_H
#include "GameObject.h"

class Coin :
	public GameObject {

private:
	int value = 200;
	int delayCoin = 160;
	int upDelay = 10;
	bool playMVAnimation = false;
	bool coinGathered = false;
	void CreateStartfr();
	void OnActionfr();
	void OnFinishfr();

	void CreateStartmv();
	void CreateOnActionmv();
	void CreateOnEndmv();
public:
	Coin(int _x, int _y, AnimationFilm* film);
	~Coin();

	void setCoinGather(bool b);
	void setPlayMVAnimation(bool b);

	bool getPlayMVAnimation() const;
	int getCoinValue() const;
	bool getGatherCoin() const;

	virtual void Display(ALLEGRO_BITMAP* dest, const struct ViewData* viewdata) const;
};
#endif // !COIN_H
