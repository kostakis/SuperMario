#include "Starman.h"
#include "CollisionChecker.h"
#include "CollisionFunctions.h"
#include "SoundManager.h"

void Starman::OnStartflash()
{
	flashanimator->SetOnStart([&](Animator*)->void {
		toplayflashanimation = true;
		startedflashanimation = true;
		});
}

void Starman::OnActionflash()
{

	flashanimator->SetOnAction([&](Animator* a, const Animation&)->void {
		bool show = flashanimator->getCurrentState();
		if (!show) {
			SpriteManager::GetInstance().getTypeList("STARMAN").front()->SetVisibility(false);
		}
		else {
			SpriteManager::GetInstance().getTypeList("STARMAN").front()->SetVisibility(true);
		}
		});
}

void Starman::OnFinishflash()
{
	flashanimator->SetOnFinish([&](Animator*)->void {
		toplayflashanimation = false;
		startedflashanimation = false;
		flashanimator->setCount(0);
		});
}

Starman::Starman(int _x, int _y, Player* p) :PowerUp(_x, _y, AnimationFilmHolder::GetInstance().GetFilm("STARMAN"), "STARMAN") {
	flashanimator = new FlashAnimator();
	flashanimation = new FlashAnimation("STARMAN_FLASH", 8, 120, 120);
	mvAnimation = new MovingAnimation("STARMAN", 0, 2, -1, intialUpDelay);
	toplayflashanimation = true;
	CollisionChecker::GetInstance().Register(p, (Sprite*)this, function_collision_player_powerUp);

	OnStartflash();
	OnActionflash();
	OnFinishflash();
}
Starman::~Starman()
{
	delete flashanimator;
	delete mvAnimation;
	delete flashanimation;
}
void Starman::Collision(Player* p)
{
	if (!tookIt) {
		SoundManager::GetInstance().PlaySound("Starman", ALLEGRO_PLAYMODE_ONCE);
		SoundManager::GetInstance().StopSound("MainSound");
		SoundManager::GetInstance().StopSound("BonusRoom");
		p->makeIndi();
		p->IncreaseHighScore(1000);
		tookIt = true;
		flashanimator->Stop();
		Destroy();
	}
}
