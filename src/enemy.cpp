#include "Enemy.h"
#include "GridMap.h"
#include "AnimatorManager.h"
#include "CollisionChecker.h"


void KOOPA_TROOPA::CreateMovingAnimation()
{
	movingAnimation = new MovingAnimation("KOOPA_TROPA", 0, 1, 1, dealyMove);
}

void KOOPA_TROOPA::OnStartMoving()
{
	movingAnimator->SetOnStart([&](Animator*)->void {
		startedMoving = true;
		startedKick = false;
		});
}

void KOOPA_TROOPA::OnFinishMoving()
{
	movingAnimator->SetOnFinish([&](Animator*)->void {
		startedMoving = false;
		how_much_moved = 0;
		});
}

void KOOPA_TROOPA::OnActionMoving()
{
	movingAnimator->SetOnAction([&](Animator* animator, const Animation& animation)->void {
		int dx;
		MovingAnimation anim = (MovingAnimation&)(animation);
		if (direction == ENEMY_DIRECTION::LEFT) {
			dx = -anim.GetDx();
		}
		else {
			dx = anim.GetDx();
		}
		int dy = anim.GetDy();

		if (!directMotion) {
			FilterGridMotion(&grid, { x,y,15,10 }, &dx, &dy);
		}
		
		if (dy && directMotion == false) {//We can fall down
			movingAnimation->SetDelay(delayGravity);
			changedDelay = true;
		}

		if (y >= 598) { // Too dawn so object is dead
			movingAnimator->Stop();
			Destroy();
			return;
		}

		if (!dy && changedDelay && directMotion == false) {
			if (koopa_state == KOOPA_STATE::MOVING) {
				movingAnimation->SetDelay(dealyMove);
			}
			else {
				movingAnimation->SetDelay(kickDealy);
			}
		}
		x += dx;
		y += dy;
		how_much_moved += 1;
		if (dx == 0 && directMotion == false) {
			if (direction == ENEMY_DIRECTION::LEFT) {
				direction = ENEMY_DIRECTION::RIGHT;
			}
			else {
				direction = ENEMY_DIRECTION::LEFT;
			}
		}

		});
}

void KOOPA_TROOPA::Display(ALLEGRO_BITMAP* dest, const ViewData* viewdata) const
{
	if (isVisible && koopa_state == KOOPA_STATE::MOVING && (!destroyed)) {
		int to_flip = 0;
		if (direction == ENEMY_DIRECTION::RIGHT) {
			to_flip = ALLEGRO_FLIP_HORIZONTAL;
		}
		al_hold_bitmap_drawing(1);
		al_draw_bitmap_region(currFilm->GetBitmap(),
			frameBox.x * frameBox.width, frameBox.y * frameBox.height,
			frameBox.width, frameBox.height, x - viewdata->x, (y - viewdata->y) - 15, to_flip);
		al_hold_bitmap_drawing(0);
	}
	else if (isVisible && (koopa_state == KOOPA_STATE::STUNNED || koopa_state == KOOPA_STATE::KICK || destroyed)) {
		Rectangle temp = AnimationFilmHolder::GetInstance().GetFilm("KOOPA_TROOPA_STUNNED")->GetFrameBox(0);
		al_hold_bitmap_drawing(1);
		al_draw_bitmap_region(currFilm->GetBitmap(),
			temp.x * temp.width, temp.y * temp.height,
			temp.width, temp.height, x - viewdata->x, (y - viewdata->y) - 15, 0);
		al_hold_bitmap_drawing(0);
	}
}

void Goomba::CreateMovingAnimation()
{
	framerangeanimation = new FrameRangeAnimation("GOOMBA_BROWN", 0, 1, 0, 1, 1, frameRangeDelay);
}

void Goomba::OnStartMoving()
{
	framerangeAnimator->SetOnStart([&](Animator*)->void {
		startedMoving = true;
		isVisible = true;
		});
}

void Goomba::OnFinishMoving()
{
	framerangeAnimator->SetOnFinish([&](Animator*)->void {
		startedMoving = false;
		isVisible = false;
		});
}

void Goomba::OnActionMoving()
{
	framerangeAnimator->SetOnAction([&](Animator* animator, const Animation& animation)->void {
		FrameRangeAnimator* fr = (FrameRangeAnimator*)animator;
		MovingAnimation& anim = (MovingAnimation&)(animation);
		for (int i = 0; i < 2; i++) {
			int dx;
			if (direction == ENEMY_DIRECTION::LEFT) {
				dx = -anim.GetDx();
			}
			else {
				dx = anim.GetDx();
			}

			int dy = anim.GetDy();
			if (!directMotion) {
				FilterGridMotion(&grid, { x,y,15,10 }, &dx, &dy);
			}
			


			if (dy && directMotion == false) {//We can fall down
				framerangeanimation->SetDelay(downdelay);
				changedDelay = true;
			}

			if (y >= 598) { // Too dawn so object is dead
				Destroy();
				return;
			}

			if (!dy && changedDelay && directMotion == false) {
				framerangeanimation->SetDelay(frameRangeDelay);
			}
			x += dx;
			y += dy;
			if (dx == 0) {
				if (direction == ENEMY_DIRECTION::LEFT) {
					direction = ENEMY_DIRECTION::RIGHT;
				}
				else {
					direction = ENEMY_DIRECTION::LEFT;
				}
			}
		}

		SetFrame(fr->GetCurrFrame());

		});
}

FrameRangeAnimation* Goomba::getFrameRangeAnimation() const
{
	return framerangeanimation;
}

FrameRangeAnimator* Goomba::getFrameRangeAnimator() const
{
	return framerangeAnimator;
}

void Goomba::Display(ALLEGRO_BITMAP* dest, const ViewData* viewdata) const
{

	if (isVisible && !destroyed) {
		int to_flip = 0;
		if (direction == ENEMY_DIRECTION::RIGHT) {
			to_flip = ALLEGRO_FLIP_HORIZONTAL;
		}
		//	al_hold_bitmap_drawing(1);
		al_draw_bitmap_region(currFilm->GetBitmap(),
			frameBox.x * frameBox.width, frameBox.y * frameBox.height,
			frameBox.width, frameBox.height, x - viewdata->x, (y - viewdata->y) - 15, to_flip);
		//al_hold_bitmap_drawing(0);
	}
	else if (isVisible && destroyed) {
		Rectangle temp = AnimationFilmHolder::GetInstance().GetFilm("GOOMBA_BROWN_STUNNED")->GetFrameBox(0);
		//	al_hold_bitmap_drawing(1);
		al_draw_bitmap_region(currFilm->GetBitmap(),
			temp.x * temp.width, temp.y * temp.height,
			temp.width, temp.height, x - viewdata->x, (y - viewdata->y) - 15, 0);
		//	al_hold_bitmap_drawing(0);
	}
}

void Enemy::setDestroyed(bool b)
{
	destroyed = b;
}

void Enemy::increaseDestroyTime(int time)
{
	destroyTime += time;
}

int Enemy::getDestroyTime() const
{
	return destroyTime;
}

bool Enemy::getDestroyed() const
{
	return destroyed;
}
