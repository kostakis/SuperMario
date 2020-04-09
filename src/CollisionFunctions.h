#ifndef COLLISIONFUNCTIONS_H
#define COLLISIONFUNCTIONS_H
#include "Game.h"
#include "Enemy.h"
#include "AI_Initialization.h"
#include <string.h>
#include "GameObject.h"
#include "PowerUp.h"
#include "Starman.h"
#include "Coin.h"

//Collision between player and turtle
auto function_collision_turtle = [&](Sprite* player, Sprite* turtle) {
	KOOPA_TROOPA* kp = static_cast<KOOPA_TROOPA*>(turtle);
	Player* tempP = static_cast<Player*>(player);
	int sideCollision = whatCollision(player, turtle);

	if (tempP->getIsIndi()) {
		kp->Destroy();
		return;
	}

	if (sideCollision == 1 && (kp->getState() == KOOPA_STATE::MOVING
		|| (kp->getState() == KOOPA_STATE::KICK) && kp->getHowMuchMove() >= 10)) {
		tempP->DecreaseSize();
		return;
	}

	if (sideCollision == 0 && kp->getState() == KOOPA_STATE::MOVING) {
		SoundManager::GetInstance().PlaySound("Stomp", ALLEGRO_PLAYMODE_ONCE);
		kp->setState(KOOPA_STATE::STUNNED);
		kp->getMovingAnimator()->Stop();
		tempP->IncreaseHighScore(100);
		tempP->bounceEffect();
	}

	if (sideCollision == 1 && kp->getState() == KOOPA_STATE::STUNNED) {
		SoundManager::GetInstance().PlaySound("Kick", ALLEGRO_PLAYMODE_ONCE);
		kp->setState(KOOPA_STATE::KICK);
		if (tempP->GetX() > kp->GetX()) {
			kp->setEnemyDirection(ENEMY_DIRECTION::LEFT);
		}
		else {
			kp->setEnemyDirection(ENEMY_DIRECTION::RIGHT);
		}
		kp->setStartedKicked(true);
	}
};

//Collision beetween goomba and player
auto function_collision_goomba = [&](Sprite* player, Sprite* goomba) {
	Goomba* kp = dynamic_cast<Goomba*>(goomba);
	Player* tempP = static_cast<Player*>(player);
	int sideCollision = whatCollision(player, goomba);

	if (tempP->getIsIndi()) {
		kp->Destroy();
		return;
	}

	if (sideCollision == 1 && !kp->getDestroyed()) {
		string size = playerSizeString[static_cast<int>(tempP->getMarioSize())];
		tempP->DecreaseSize();
	}
	else if (sideCollision == 0 && !kp->getDestroyed()) {
		SoundManager::GetInstance().PlaySound("Stomp", ALLEGRO_PLAYMODE_ONCE);
		bool stunned = kp->getDestroyed();
		if (!stunned) {
			tempP->IncreaseHighScore(100);
			kp->setDestroyed(true);
			kp->getMovingAnimator()->Stop();
			kp->SetVisibility(true);
			tempP->bounceEffect();
		}
	}
};

//Collision beetween two gombas
auto function_collicion_two_goom = ([&](Sprite* goomba1, Sprite* goomba2) {

	Goomba* g1 = static_cast<Goomba*>(goomba1);
	Goomba* g2 = static_cast<Goomba*>(goomba2);

	if (g1->getDirection() == ENEMY_DIRECTION::LEFT && g2->getDirection() == ENEMY_DIRECTION::LEFT) {
		g2->setEnemyDirection(ENEMY_DIRECTION::RIGHT);
	}
	else if (g1->getDirection() == ENEMY_DIRECTION::RIGHT && g2->getDirection() == ENEMY_DIRECTION::RIGHT) {
		g1->setEnemyDirection(ENEMY_DIRECTION::LEFT);
	}
	else {
		g1->changeDirection();
		g2->changeDirection();
	}

	});

//Collision between Turtle and goomba
auto function_collision_turtle_goomba = ([&](Sprite* _turtle, Sprite* goomba) {
	KOOPA_TROOPA* turtle = static_cast<KOOPA_TROOPA*>(_turtle);
	Goomba* gom = static_cast<Goomba*>(goomba);
	if (turtle->getState() == KOOPA_STATE::KICK) {
		goomba->Destroy();
		return;
	}

	if (turtle->getState() == KOOPA_STATE::MOVING && turtle->getDirection() == ENEMY_DIRECTION::LEFT && gom->getDirection() == ENEMY_DIRECTION::LEFT)
	{
		turtle->changeDirection();
	}
	else if (turtle->getState() == KOOPA_STATE::MOVING && turtle->getDirection() == ENEMY_DIRECTION::LEFT && gom->getDirection() == ENEMY_DIRECTION::RIGHT)
	{
		gom->changeDirection();
		turtle->changeDirection();
	}
	else if (turtle->getState() == KOOPA_STATE::MOVING && turtle->getDirection() == ENEMY_DIRECTION::RIGHT && gom->getDirection() == ENEMY_DIRECTION::RIGHT)
	{
		gom->changeDirection();
	}
	else if (turtle->getState() == KOOPA_STATE::MOVING && turtle->getDirection() == ENEMY_DIRECTION::RIGHT && gom->getDirection() == ENEMY_DIRECTION::LEFT)
	{
		gom->changeDirection();
		turtle->changeDirection();
	}

	if (turtle->getState() == KOOPA_STATE::STUNNED) {
		gom->changeDirection();
	}

	});

//Collision beetween player and coin
auto function_collision_player_coin = ([&](Sprite* player1, Sprite* coin1) {
	Player* tempP = static_cast<Player*> (player1);
	Coin* coin = static_cast<Coin*>(coin1);
	if (coin->getGatherCoin() == false) {
		SoundManager::GetInstance().StopSound("Coin");
		SoundManager::GetInstance().PlaySound("Coin", ALLEGRO_PLAYMODE_ONCE);
		tempP->IncreaseCoins(1);
		tempP->IncreaseHighScore(coin->getCoinValue());
		coin->setCoinGather(true);
	}
	coin->getfrAnimator()->Stop();
	coin->setPlayMVAnimation(true);
	});

//Collision player and question brick
auto function_collision_player_questionBrick = ([&](Sprite* player1, Sprite* brick1) {
	Player* tempP = static_cast<Player*> (player1);
	QuestionBrick* question = static_cast<QuestionBrick*>(brick1);
	int timesTouched = question->getTimesTouched();
	int max = question->getMaxTouches();
	bool playingAnimation = question->getStartedmvAnimation();
	if (!playingAnimation) {
		int what = question->produce();
		question->setToPlayMVAnimation(true);
		if (what == 1) {
			AnimationFilm* coinFilm = AnimationFilmHolder::GetInstance().GetFilm("COIN");
			Coin* coin = new Coin(question->GetX(), question->GetY() - 18, coinFilm);
			tempP->IncreaseCoins(1);
			tempP->IncreaseHighScore(coin->getCoinValue());
			coin->setPlayMVAnimation(true);
			SoundManager::GetInstance().StopSound("Coin");
			SoundManager::GetInstance().PlaySound("Coin", ALLEGRO_PLAYMODE_ONCE);
		}
		else if (what == 2) {
			GreenMushroom* green = new GreenMushroom(question->GetX(), question->GetY() - 10, tempP);
			SoundManager::GetInstance().PlaySound("Powerup_appears", ALLEGRO_PLAYMODE_ONCE);
		}
		else if (what == 3) {
			RedMushroom *red = new RedMushroom(question->GetX(), question->GetY() - 10, tempP);
			SoundManager::GetInstance().PlaySound("Powerup_appears", ALLEGRO_PLAYMODE_ONCE);
		}
		else if (what == 6) {
			Starman* red = new Starman(question->GetX(), question->GetY() - 10,tempP);
			red->setstartedflashanimation(true);
			SoundManager::GetInstance().PlaySound("Powerup_appears", ALLEGRO_PLAYMODE_ONCE);
		}
	}
	});

//Collision player and simple brick
auto function_collision_player_simpleBrick = ([&](Sprite* player1, Sprite* brick1) {
	//assert(player1);
	//assert(brick1);
	Player* tempP = static_cast<Player*> (player1);
	SimpleBrick* brick = static_cast<SimpleBrick*>(brick1);
	brick->setToPlayMVAnimation(true);
	SoundManager::GetInstance().PlaySound("Blockhit", ALLEGRO_PLAYMODE_ONCE);
	});

//Collision player and powerup
auto function_collision_player_powerUp = ([&](Sprite* player1, Sprite* mush) {
	//assert(player1);
	//assert(mush);
	Player* player = static_cast<Player*>(player1);
	PowerUp* temp = static_cast<PowerUp*>(mush);
	temp->Collision(player);
	});

//Collision between Turtle and turtle
auto function_collision_turtle_turtle = ([&](Sprite* _turtle, Sprite* _turtle1) {
	KOOPA_TROOPA* turtle = static_cast<KOOPA_TROOPA*>(_turtle);
	KOOPA_TROOPA* turtle1 = static_cast<KOOPA_TROOPA*>(_turtle1);

	if (turtle->getState() == KOOPA_STATE::MOVING && turtle1->getState() == KOOPA_STATE::STUNNED)
	{
		turtle->changeDirection();
	}
	else if (turtle1->getState() == KOOPA_STATE::MOVING && turtle->getState() == KOOPA_STATE::STUNNED)
	{
		turtle1->changeDirection();
	}

	if (turtle->getState() == KOOPA_STATE::KICK && turtle1->getState() == KOOPA_STATE::KICK)
	{
		if (turtle->getDirection() == ENEMY_DIRECTION::RIGHT && turtle1->getDirection() == ENEMY_DIRECTION::RIGHT)
		{
			turtle->changeDirection();
		}
		else if (turtle1->getDirection() == ENEMY_DIRECTION::LEFT && turtle->getDirection() == ENEMY_DIRECTION::LEFT)
		{
			turtle1->changeDirection();
		}
		else {
			turtle->changeDirection();
			turtle1->changeDirection();
		}
	}

	if (turtle->getState() == KOOPA_STATE::MOVING && turtle1->getState() == KOOPA_STATE::MOVING)
	{
		if (turtle->getDirection() == ENEMY_DIRECTION::RIGHT && turtle1->getDirection() == ENEMY_DIRECTION::RIGHT)
		{
			turtle->changeDirection();
		}
		else if (turtle1->getDirection() == ENEMY_DIRECTION::LEFT && turtle->getDirection() == ENEMY_DIRECTION::LEFT)
		{
			turtle1->changeDirection();
		}
		else {
			turtle->changeDirection();
			turtle1->changeDirection();
		}
	}


	if (turtle->getState() == KOOPA_STATE::KICK && turtle1->getState() == KOOPA_STATE::STUNNED)
	{
		turtle->changeDirection();
		turtle1->setEnemyDirection(ENEMY_DIRECTION::RIGHT);
		turtle1->setState(KOOPA_STATE::KICK);
		turtle1->setStartedKicked(true);
	}
	else if (turtle1->getState() == KOOPA_STATE::KICK && turtle->getState() == KOOPA_STATE::STUNNED)
	{
		turtle1->changeDirection();
		turtle->setEnemyDirection(ENEMY_DIRECTION::RIGHT);
		turtle->setState(KOOPA_STATE::KICK);
		turtle->setStartedKicked(true);
	}

	if (turtle->getState() == KOOPA_STATE::KICK && turtle1->getState() == KOOPA_STATE::MOVING)
	{
		turtle->changeDirection();
		turtle1->changeDirection();
	}
	else if (turtle1->getState() == KOOPA_STATE::KICK && turtle->getState() == KOOPA_STATE::MOVING)
	{
		turtle->changeDirection();
		turtle1->changeDirection();
	}


	});
#endif // !COLLISIONFUNCTIONS_H