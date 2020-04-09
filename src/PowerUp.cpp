#include "PowerUp.h"
#include "CollisionChecker.h"
#include "CollisionFunctions.h"

void PowerUp::CreateStartfr()
{
}

void PowerUp::OnActionfr()
{
}

void PowerUp::OnFinishfr()
{
}

void PowerUp::OnStartMV()
{
	mvAnimator->SetOnStart([&](Animator*)->void {
		startedmvAnimation = true;
		});
}

void PowerUp::OnActionMV()
{
	mvAnimator->SetOnAction([&](Animator* a, const Animation& anim) -> void {
		MovingAnimation& animation = (MovingAnimation&)anim;
		int dx = animation.GetDx();
		int dy = animation.GetDy();
		if (!changed) {
			y += dy;
			howmuchDY++;
		}
		if (howmuchDY == maxInitialDy && !changed) {
			animation.SetDelay(20);
			animation.SetDy(2);
			changed = true;
		}
		else if (changed) {
			if (direction == MUSHROOM_DIRECTION::RIGHT) {
				dx = animation.GetDx();
			}
			else {
				dx = -animation.GetDx();
			}
			FilterGridMotion(&grid, GetBox(), &dx, &dy);
			x += dx;
			y += dy;

			if (dx == 0) {
				if (direction == MUSHROOM_DIRECTION::RIGHT) direction = MUSHROOM_DIRECTION::LEFT;
				else direction = MUSHROOM_DIRECTION::RIGHT;
			}
		}
		});
}

void PowerUp::OnFinishMV()
{
	mvAnimator->SetOnFinish([&](Animator*)->void {
		startedmvAnimation = false;
		});
}

GreenMushroom::GreenMushroom(int _x, int _y, Player* p) :
	PowerUp(_x, _y, AnimationFilmHolder::GetInstance().GetFilm("MUSHROOM_POWERUP_GREEN"), "MUSHROOM_POWERUP_GREEN")
{
	CollisionChecker::GetInstance().Register(p, (Sprite*)this, function_collision_player_powerUp);
	mvAnimation = new MovingAnimation("MUSHROOM_POWERUP_GREEN", 0, 1, -1, intialUpDelay);
}

GreenMushroom::~GreenMushroom()
{
	delete mvAnimation;
}

void GreenMushroom::Collision(Player* p)
{
	if (!tookIt) {
		tookIt = true;
		p->IncreaseLives(1);
		p->IncreaseHighScore(points);
		frAnimator->Stop();
		mvAnimator->Stop();
		Destroy();
	}
}

RedMushroom::RedMushroom(int _x, int _y, Player* p) :
	PowerUp(_x, _y, AnimationFilmHolder::GetInstance().GetFilm("MUSHROOM_POWERUP_RED"), "MUSHROOM_POWERUP_RED")
{
	CollisionChecker::GetInstance().Register(p, (Sprite*)this, function_collision_player_powerUp);
	mvAnimation = new MovingAnimation("MUSHROOM_POWERUP_RED", 0, 1, -1, intialUpDelay);
}

RedMushroom::~RedMushroom()
{
	delete mvAnimation;
}

void RedMushroom::Collision(Player* p)
{
	if (!tookIt) {
		tookIt = true;
		string size = playerSizeString[static_cast<int>(p->getMarioSize())];
		if (size == "SMALL") {
			SoundManager::GetInstance().PlaySound("Powerup", ALLEGRO_PLAYMODE_ONCE);
			p->setPlayFlashAnimation(true);
			p->setMarioSize(mario_size::SUPER);
		}if (size == "SUPER") {
			SoundManager::GetInstance().PlaySound("Powerup", ALLEGRO_PLAYMODE_ONCE);
			p->setMarioSize(mario_size::INVINCIBLE);
			p->setPlayFlashAnimation(true);
		}
		p->IncreaseHighScore(points);
		frAnimator->Stop();
		mvAnimator->Stop();
		Destroy();
	}
}