#ifndef MUSHROOM_H
#define MUSHROOM_H
#include "GameObject.h"
#include "AnimationFilmHolder.h"
#include "Player.h"

enum class MUSHROOM_DIRECTION
{
	LEFT, RIGHT
};

class PowerUp :
	public GameObject
{
protected:
	int intialUpDelay = 40;
	int movingDelay = 15;
	int maxInitialDy = 16;
	int howmuchDY = 0;
	bool changed = false;
	bool tookIt = false;
	MUSHROOM_DIRECTION direction;
	void CreateStartfr();
	void OnActionfr();
	void OnFinishfr();
	virtual void OnStartMV();
	virtual void OnActionMV();
	virtual void OnFinishMV();
public:
	PowerUp(int _x, int _y, AnimationFilm* film, const string& type) :
		GameObject(_x, _y, film, type)
	{
		CreateStartfr();
		OnActionfr();
		OnFinishfr();
		OnStartMV();
		OnActionMV();
		OnFinishMV();
		int range = 2 - 1 + 1;
		double random = getRandom(1,2);
		//Random direction for mush room
		if (random == 1) {
			direction = MUSHROOM_DIRECTION::LEFT;
		}
		else {
			direction = MUSHROOM_DIRECTION::RIGHT;
		}
	}

	virtual ~PowerUp() {

	}

	void setDirection(MUSHROOM_DIRECTION dir) {
		direction = dir;
	}

	virtual void Collision(Player* p) = 0;

	MUSHROOM_DIRECTION getDirection() const {
		return direction;
	}

	bool getTookit()
	{
		return tookIt;
	}
};

/*
Gives mario an extra size and 1000 points
*/
class GreenMushroom :
	public PowerUp
{
private:
	int points = 1000;
public:
	GreenMushroom(int _x, int _y, Player* p);
	~GreenMushroom();

	void Collision(Player* p);
};


class RedMushroom :
	public PowerUp
{
private:
	int points = 1000;
public:
	RedMushroom(int _x, int _y, Player* p);
	~RedMushroom();

	void Collision(Player* p);
};
#endif // !MUSHROOM_H