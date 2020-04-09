#include "Coin.h"

Coin::Coin(int _x, int _y, AnimationFilm* film):
	GameObject(_x, _y, film, "COIN")
{
	frAnimation = new FrameRangeAnimation("COIN", 0, 2, 0, _x, _y, delayCoin);
	mvAnimation = new MovingAnimation("COIN", 0, _x, _y, upDelay);
	CreateStartfr();
	OnActionfr();
	OnFinishfr();
	CreateStartmv();
	CreateOnActionmv();
	CreateOnEndmv();
}

Coin::~Coin()
{
	delete mvAnimation;
	delete frAnimation;
}

void Coin::CreateStartfr()
{
	frAnimator->SetOnStart([&](Animator*)->void {
		startedAnimation = true;
		});
}

void Coin::OnActionfr()
{
	frAnimator->SetOnAction([&](Animator* a, const Animation& anim) -> void {
		FrameRangeAnimator* fr = (FrameRangeAnimator*)a;
		SetFrame(fr->GetCurrFrame());
		});
}

void Coin::OnFinishfr()
{
	frAnimator->SetOnFinish([&](Animator*)->void {
		startedAnimation = false;
		});
}

void Coin::CreateStartmv()
{
	mvAnimator->SetOnStart([&](Animator*)->void {
		startedmvAnimation = true;
		});
}

void Coin::CreateOnActionmv()
{
	mvAnimator->SetOnAction([&](Animator* a, const Animation& anim) -> void {
		y -= 10;
		if (y <= 10) {
			mvAnimator->Stop();
			Destroy();
		}
		});
}

void Coin::CreateOnEndmv()
{
	mvAnimator->SetOnFinish([&](Animator*)->void {
		startedmvAnimation = false;
		});
}


void Coin::setCoinGather(bool b)
{
	coinGathered = b;
}

void Coin::setPlayMVAnimation(bool b)
{
	playMVAnimation = b;
}

bool Coin::getPlayMVAnimation() const
{
	return playMVAnimation;
}

int Coin::getCoinValue() const
{
	return value;
}

bool Coin::getGatherCoin() const
{
	return coinGathered;
}

void Coin::Display(ALLEGRO_BITMAP* dest, const ViewData* viewdata) const
{
	if (isVisible && !startedmvAnimation) {
		al_draw_bitmap_region(currFilm->GetBitmap(),
			frameBox.x * frameBox.width, frameBox.y * frameBox.height,
			frameBox.width, frameBox.height, x - viewdata->x, y - viewdata->y, 0);
	}
	else if (isVisible && startedmvAnimation) {
		Rectangle temp = AnimationFilmHolder::GetInstance().GetFilm("COIN_GOLD")->GetFrameBox(0);
		al_draw_bitmap_region(currFilm->GetBitmap(),
			temp.x * temp.width, temp.y * temp.height,
			temp.width, temp.height, x - viewdata->x, (y - viewdata->y), 0);
	}
}