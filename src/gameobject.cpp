#include "GameObject.h"
#include "SpriteManager.h"
#include "Enemy.h"
static bool flagStar = false;

#define YOFFESTBRICKS -6

void Brick::CreateStartfr()
{
	frAnimator->SetOnStart([&](Animator*)->void {
		startedAnimation = true;
		});
}

void Brick::OnActionfr()
{
	frAnimator->SetOnAction([&](Animator* a, const Animation& anim) -> void {
		FrameRangeAnimator* fr = (FrameRangeAnimator*)a;
		SetFrame(fr->GetCurrFrame());
		});
}

void Brick::OnFinishfr()
{
	frAnimator->SetOnFinish([&](Animator*)->void {
		startedAnimation = false;
		});
}

void Brick::CreateStartMV()
{
	mvAnimator->SetOnStart([&](Animator*)->void {
		startedmvAnimation = true;
		howMuchDy = 0;
		});
}

void Brick::CreateActionMV()
{
	mvAnimator->SetOnAction([&](Animator* a, const Animation& anim) -> void {
		MovingAnimation& animation = (MovingAnimation&)anim;
		if (!goDown) {
			y -= 1;
			howMuchDy++;
			if (howMuchDy >= maxDy) {
				/*mvAnimator->Stop();*/
				goDown = true;
				howMuchDy = 0;
			}
		}
		else {
			y += 1;
			howMuchDy++;
			if (howMuchDy >= maxDy) {
				mvAnimator->Stop();
			}

		}
		});
}

void Brick::CreateFinishMV()
{
	mvAnimator->SetOnFinish([&](Animator*)->void {
		startedmvAnimation = false;
		goDown = false;
		toPlayMovingAnimation = false;
		});
}

QuestionBrick::QuestionBrick(int _x, int _y, AnimationFilm* film) :
	Brick(_x, _y, film, "QUESTION_BRICK")
{
	frAnimation = new FrameRangeAnimation("QUESTION_BRICK", 0, 2, 0, _x, _y, delay);
	maxTouches = getRandom(minTouches, maxToGenerate);
}

int  QuestionBrick::produce()
{
	if (timesTouched < maxTouches) {
		timesTouched++;
		int random = getRandom(1, 100);
		if (random <= 60) {//Coin
			return 1;
		}
		else if (random > 60 && random <= 72) { //Green mushroom
			showedPowerUp = true;
			timesTouched = maxTouches;
			return 2;
		}
		else if (random > 72 && random <= 84) {//Red mushroom
			showedPowerUp = true;
			timesTouched = maxTouches;
			return 3;
		}
		else if (random > 84) {//StarMan
			if (!flagStar) {
				showedPowerUp = true;
				timesTouched = maxTouches;
				flagStar = true;
				return 6;
			}
			else {
				return 1;
			}
		}
	}
	return -1;
}

void QuestionBrick::Display(ALLEGRO_BITMAP* dest, const ViewData* viewdata) const
{
	if (isVisible && timesTouched < maxTouches) {
		al_draw_bitmap_region(currFilm->GetBitmap(),
			frameBox.x * frameBox.width, frameBox.y * frameBox.height,
			frameBox.width, frameBox.height, x - viewdata->x, (y + YOFFESTBRICKS) - viewdata->y/*- 15*/, 0);
	}
	else if (isVisible && timesTouched >= maxTouches) {
		Rectangle temp = AnimationFilmHolder::GetInstance().GetFilm("QUESTION_BRICK_DESTROYED")->GetFrameBox(0);
		al_draw_bitmap_region(currFilm->GetBitmap(),
			temp.x * temp.width, temp.y * temp.height,
			temp.width, temp.height, x - viewdata->x, (y + YOFFESTBRICKS) /*- viewdata->y *//*- 15*/, 0);
	}
}

void SimpleBrick::CreateActionMV()
{
	mvAnimator->SetOnAction([&](Animator* a, const Animation& anim) -> void {
		MovingAnimation& animation = (MovingAnimation&)anim;
		if (!goDown) {
			y -= 1;
			howMuchDy++;
			if (howMuchDy >= maxDy) {
				/*mvAnimator->Stop();*/
				goDown = true;
				howMuchDy = 0;
			}
		}
		else {
			y += 1;
			howMuchDy++;
			if (howMuchDy >= maxDy) {
				mvAnimator->Stop();
			}

		}

		auto& koppa = SpriteManager::GetInstance().getTypeList("KOOPA_TROOPA");
		auto& goomba = SpriteManager::GetInstance().getTypeList("GOOMBA_BROWN");
		for (auto* i : koppa) {
			if (CollisionCheck(i)) {
				KOOPA_TROOPA* a = static_cast<KOOPA_TROOPA*>(i);
				a->getMovingAnimation()->SetDx(0);
				a->getMovingAnimation()->SetDy(-1);
				a->getMovingAnimation()->SetDelay(60);
				a->setDestroyed(true);
				a->SetDirectMotion(true);
				a->setDestroyedByBrick(true);
			}
		}
		for (auto* i : goomba) {
			if (CollisionCheck(i)) {
				Goomba* a = static_cast<Goomba*>(i);
				a->getFrameRangeAnimation()->SetDx(0);
				a->getFrameRangeAnimation()->SetDy(-1);
				a->getFrameRangeAnimation()->SetDelay(120);
				a->setDestroyed(true);
				a->SetDirectMotion(true);
				a->setDestroyedByBrick(true);
			}
		}
		});
}

void SimpleBrick::Display(ALLEGRO_BITMAP* dest, const ViewData* viewdata) const
{
	if (isVisible && !isDestroyed) {
		al_draw_bitmap_region(currFilm->GetBitmap(),
			frameBox.x * frameBox.width, frameBox.y * frameBox.height,
			frameBox.width, frameBox.height, x - viewdata->x, (y + YOFFESTBRICKS) - viewdata->y/*- 15*/, 0);
	}
}