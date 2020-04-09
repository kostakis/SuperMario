#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Sprites.h"
#include "FrameRangeAnimator.h"
#include "Animation_FrameRange.h"
#include "AnimatorManager.h"
#include "Animation_Moving.h"
#include "Animator_Moving.h"

class GameObject :
	public Sprite
{
protected:
	FrameRangeAnimator* frAnimator;
	FrameRangeAnimation* frAnimation;
	MovingAnimator* mvAnimator;
	MovingAnimation* mvAnimation;
	MovingAnimation* downAnimation;
	bool startedAnimation = false;
	bool startedmvAnimation = false;
	virtual void CreateStartfr() = 0;
	virtual void OnActionfr() = 0;
	virtual void OnFinishfr() = 0;
public:
	GameObject(int _x, int _y, AnimationFilm* film, const string& type)
		:Sprite(_x, _y, film, type)
	{
		isVisible = true;
		frAnimator = new FrameRangeAnimator();
		mvAnimator = new MovingAnimator();
		frAnimation = NULL;
		mvAnimation = NULL;
		downAnimation = NULL;
	}

	virtual ~GameObject() {
		frAnimator->Stop();
		mvAnimator->Stop();
		delete frAnimator;
		delete mvAnimator;
	}

	void setStartedAnimation(bool b)
	{
		startedAnimation = b;
	}

	void setStartedmvAnimation(bool b)
	{
		startedmvAnimation = b;
	}

	void setfrAnimation(FrameRangeAnimation* fr) {
		frAnimation = fr;
	}

	bool getStartedAnimation() const
	{
		return startedAnimation;
	}

	bool getStartedmvAnimation()const {
		return startedmvAnimation;
	}

	MovingAnimation* getmvAnimation() const {
		return mvAnimation;
	}

	FrameRangeAnimation* getfrAnimation()const {
		return frAnimation;
	}

	FrameRangeAnimator* getfrAnimator()const {
		return frAnimator;
	}

	MovingAnimator* getmvAnimator() const {
		return mvAnimator;
	}

};

class Brick :
	public GameObject {
protected:
	int maxDy = 14;
	int howMuchDy = 0;
	int brickUpDealy = 20;
	bool goDown = false;
	bool toPlayMovingAnimation = false;

	void CreateStartfr();
	void OnActionfr();
	void OnFinishfr();

	void CreateStartMV();
	virtual void CreateActionMV();
	void CreateFinishMV();
public:
	Brick(int _x, int _y, AnimationFilm* film, const string& type) :
		GameObject(_x, _y, film, type)
	{
		CreateStartfr();
		OnActionfr();
		OnFinishfr();
		CreateStartMV();
		CreateActionMV();
		CreateFinishMV();
		mvAnimation = new MovingAnimation("Brick_UP", 0, _x, _y, brickUpDealy);
	}

	virtual ~Brick() {
		delete mvAnimation;
	}

	void setToPlayMVAnimation(bool b) {
		toPlayMovingAnimation = b;
	}

	int getMaxDy() const {
		return maxDy;
	}

	bool getToPlayMVAnimation() const {
		return toPlayMovingAnimation;
	}
};

class SimpleBrick :
	public Brick {
private:
	bool isDestroyed = false;
	void CreateActionMV();
public:
	SimpleBrick(int _x, int _y, AnimationFilm* film)
		: Brick(_x, _y, film, "SIMPLE_BRICK") {
		CreateActionMV();
	}

	~SimpleBrick() {
	}

	virtual void Display(ALLEGRO_BITMAP* dest, const struct ViewData* viewdata) const;
};

class QuestionBrick :
	public Brick {

private:
	int delay = 160;
	int maxTouches;
	int maxToGenerate = 5;
	int minTouches = 2;
	int timesTouched = 0;
	bool stopAnimator = false;
	bool showedPowerUp = false;
public:
	QuestionBrick(int _x, int _y, AnimationFilm* film);
	
	~QuestionBrick() {
		delete frAnimation;
	}

	void increaseTimeTouched(int number) {
		timesTouched += number;
	}

	int produce();

	int getTimesTouched()const {
		return timesTouched;
	}

	int getMaxTouches() const {
		return maxTouches;
	}

	bool getStopAnimator()
	{
		return stopAnimator;
	}

	virtual void Display(ALLEGRO_BITMAP* dest, const struct ViewData* viewdata) const;
};
#endif // !GAMEOBJECT_H