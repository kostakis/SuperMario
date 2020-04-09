#include "Player.h"
#include "Initialization.h"

Player::Player(int x, int y) :
	Sprite(x, y, nullptr, "1MARIO_PLAYER")
{
	this->HighScore = 0;
	this->Coins = 0;
	this->Lives = 5;
	this->p_State = IDLE;
	this->StartedAnimation = false;
	this->startedMovingAnimator = false;
	this->startedFlashAnimation = false;
	this->d_State = p_direction::RIGHT;
	this->frameRangeAnimator = new FrameRangeAnimator();
	this->flashAnimator = new FlashAnimator();
	this->frameRLeftAnimation = new FrameRangeAnimation();
	this->frameRRightAnimation = new FrameRangeAnimation();
	this->JumpUpAnimator = new MovingAnimator();
	this->JumpDownAnimator = new MovingAnimator();
	this->jumpRightAnimation = new MovingAnimation();
	this->jumpLeftAnimation = new MovingAnimation();
	this->flashAnimation = new FlashAnimation();
	Init::AnimatorActions::FrameRangePlayer(this);
	Init::AnimatorActions::JumpUpPlayer(this);
	Init::AnimatorActions::JumpDownPlayer(this);
	Init::AnimatorActions::FlashAnimatorPlayer(this);
}

void Player::setDirection(p_direction d)
{
	this->d_State = d;
}

bool Player::getIsIndi() const
{
	return isINDESTRUCTIBLE;
}

int Player::getIniTime() const
{
	return indiTime;
}

int Player::getHighScore() const
{
	return this->HighScore;
}

int Player::getCoins() const
{
	return this->Coins;
}

int Player::GetLives() const
{
	return this->Lives;
}

void Player::setState(playerState state)
{
	this->p_State = state;
}

void Player::setHighScore(int HighScore)
{
	this->HighScore = HighScore;
}

void Player::setCoins(int Coins)
{
	this->Coins = Coins;
}

void Player::setLives(int Lives)
{
	this->Lives = Lives;
}

void Player::setIsJumping(const bool& b)
{
	isJumping = b;
}

void Player::setIsFalling(const bool& b)
{
	isFalling = b;
}

void Player::setJumpRightAnimation(MovingAnimation* anim)
{
	this->jumpRightAnimation = anim;
}

void Player::setJumpLeftAnimation(MovingAnimation* anim)
{
	this->jumpLeftAnimation = anim;
}

void Player::setStartedMovingAnim(bool b)
{
	this->startedMovingAnimator = b;
}

void Player::setStartedFlashAnimaton(bool b)
{
	startedFlashAnimation = b;
}

void Player::setPlayFlashAnimation(bool b)
{
	playFlashAnimaton = b;
}

void Player::Display(ALLEGRO_BITMAP* bitmap, const ViewData)
{
	string size = playerSizeString[static_cast<int>(size_state)];
	string direction = playerDirectionString[static_cast<int>(d_State)];

	if (startedFlashAnimation) {
		Sprite* temp = getCurrentSprite();
		temp->setDrawing(drawingxplayer - 3, drawingyplayer - 5);
		temp->SetPos(x, y);
		temp->DisplayPlayer();
	}
	else if (isJumping || isFalling) {
		string to_change("MARIO_" + size + "_JUMP_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		if (direction == "LEFT") {
			temp.front()->setDrawing(drawingxplayer + 4, drawingyplayer - 5);
		}
		else {
			temp.front()->setDrawing(drawingxplayer - 3, drawingyplayer - 5);
		}

		temp.front()->SetPos(x, y);
		temp.front()->SetVisibility(true);
		temp.front()->DisplayPlayer();
	}
	else if (p_State == IDLE) {
		string to_change("MARIO_" + size + "_IDLE_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		temp.front()->setDrawing(drawingxplayer - 3, drawingyplayer - 5);
		if (size == "INVINCIBLE") {
			temp.front()->setDrawing(drawingxplayer - 3, drawingyplayer - 3);
		}
		temp.front()->SetPos(x, y);
		temp.front()->SetVisibility(true);
		temp.front()->DisplayPlayer();
	}

	else if (p_State == MOVING) {
		string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		if (d_State == p_direction::LEFT) {
			temp.front()->setDrawing(drawingxplayer - 3, drawingyplayer - 3);
		}
		else {
			temp.front()->setDrawing(drawingxplayer - 3, drawingyplayer - 5);
		}
		if (size == "INVINCIBLE") {
			temp.front()->setDrawing(drawingxplayer - 3, drawingyplayer - 3);
		}
		temp.front()->SetPos(x, y);
		temp.front()->SetVisibility(true);
		temp.front()->DisplayPlayer();
	}
}

void Player::bounceEffect()
{
	for (int i = 0; i < 20; i++) {
		int dy = -1;
		int dx = 0;
		FilterGridMotion(&grid, frameBox, &dx, &dy);
		Move(0, dy);
		moveDrawing(0, dy);
	}
}

void Player::IncreaseCoins(int coins)
{
	Coins += coins;
	if (Coins == 100) {
		Coins = 0;
		SoundManager::GetInstance().PlaySound("1-up", ALLEGRO_PLAYMODE_ONCE);
		Lives += 1;
	}
}

void Player::IncreaseHighScore(int highScore)
{
	HighScore += highScore;
}

void Player::IncreaseLives(int _lives)
{
	Lives += _lives;
	SoundManager::GetInstance().PlaySound("1-up", ALLEGRO_PLAYMODE_ONCE);
}

void Player::DecreaseSize()
{
	if (!playFlashAnimaton) {
		if (size_state == mario_size::SMALL) {
				removeLife(1);
		}
		else if (size_state == mario_size::SUPER) {
			playFlashAnimaton = true;
			setMarioSize(mario_size::SMALL);
		}
		else if (size_state == mario_size::INVINCIBLE) {
			playFlashAnimaton = true;
			size_state = mario_size::SUPER;
		}
	}
}

void Player::IncreaseIniTime(int _time)
{
	indiTime += _time;
}

void Player::makeIndi()
{
	previousState = size_state;
	if (size_state == mario_size::SMALL) {
		size_state = mario_size::INVINCIBLE;
		drawingyplayer -= 13;
	}
	else {
		size_state = mario_size::INVINCIBLE;
	}
	playFlashAnimaton = true;
	isINDESTRUCTIBLE = true;
}

void Player::resetIndi()
{
	if (previousState == mario_size::SMALL) {
		drawingyplayer += 15;
		size_state = previousState;
	}
	else {
		size_state = previousState;
	}
	indiTime = 0;
	isINDESTRUCTIBLE = false;
	playFlashAnimaton = true;
	SoundManager::GetInstance().StopSound("Starman");
	SoundManager::GetInstance().PlaySound("MainSound",ALLEGRO_PLAYMODE_LOOP);
}

void Player::setMarioSize(mario_size s)
{
	if (s == mario_size::SUPER) {
		drawingyplayer -= 14;
	}
	else if (s == mario_size::SMALL) {
		drawingyplayer += 15;
	}
	else if(s == mario_size::INVINCIBLE && size_state != mario_size::SUPER) {
		drawingyplayer -= 12;
	}
	this->size_state = s;
}

void Player::setFrameRangeAnimator(FrameRangeAnimator* fra)
{
	this->frameRangeAnimator = fra;
}

void Player::setFrameRangeRightAnimation(FrameRangeAnimation* anim)
{
	this->frameRRightAnimation = anim;
}

void Player::setFrameRangeLeftAnimation(FrameRangeAnimation* anim)
{
	this->frameRLeftAnimation = anim;
}

void Player::setFlashAnimation(FlashAnimation* anim)
{
	this->flashAnimation = anim;
}

void Player::setAnimationStarted(const bool s)
{
	this->StartedAnimation = s;
}

playerState Player::getState()
{
	return this->p_State;
}

p_direction Player::getDirection() const
{
	return this->d_State;
}

mario_size Player::getMarioSize() const
{
	return this->size_state;
}

FrameRangeAnimator* Player::getFrameRangeAnimator() const
{
	return this->frameRangeAnimator;
}

FrameRangeAnimation* Player::getRightFrameRangeAnimation() const
{
	return this->frameRRightAnimation;
}

FrameRangeAnimation* Player::getLeftFrameRangeAnimation() const
{
	return this->frameRLeftAnimation;
}

FlashAnimation* Player::getFlashAnimation() const
{
	return flashAnimation;
}

FlashAnimator* Player::getFlashAnimator() const
{
	return flashAnimator;
}

bool Player::getAnimationStarted() const
{
	return this->StartedAnimation;
}

bool Player::getIsJumping() const
{
	return isJumping;
}

bool Player::getIsFalling() const
{
	return isFalling;
}

MovingAnimation* Player::getJumpRightAnimation() const
{
	return this->jumpRightAnimation;
}

MovingAnimation* Player::getJumpLeftAnimation() const
{
	return this->jumpLeftAnimation;
}

MovingAnimator* Player::getJumpUpAnimator() const
{
	return this->JumpUpAnimator;
}

MovingAnimator* Player::getJumpDownAnimator() const
{
	return JumpDownAnimator;
}

bool Player::getStartedMovingAnimator() const
{
	return this->startedMovingAnimator;
}

void Player::removeLife(const int number)
{
	Lives = Lives - number;
	if (Lives > 0) SoundManager::GetInstance().PlaySound("LoseLife", ALLEGRO_PLAYMODE_ONCE);
	playFlashAnimaton = true;
}

Sprite* Player::getCurrentSprite() const
{
	string size = playerSizeString[static_cast<int>(size_state)];
	string direction = playerDirectionString[static_cast<int>(d_State)];

	if (isJumping || isFalling) {
		string to_change("MARIO_" + size + "_JUMP_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		return temp.front();
	}
	else if (p_State == IDLE) {
		string to_change("MARIO_" + size + "_IDLE_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		return temp.front();
	}

	else if (p_State == MOVING) {
		string to_change("MARIO_" + size + "_MOVING_SLOW_" + direction);
		std::list<Sprite*> temp = SpriteManager::GetInstance().getTypeList(to_change);
		return temp.front();
	}

	return NULL;
}

bool Player::getStartedFlashAnimaton() const
{
	return startedFlashAnimation;
}

bool Player::getPlayFlashAnimation() const
{
	return playFlashAnimaton;
}

Player::~Player()
{
	frameRangeAnimator->Stop();
	JumpUpAnimator->Stop();
	JumpDownAnimator->Stop();
	flashAnimator->Stop();
	delete frameRangeAnimator;
	delete JumpUpAnimator;
	delete JumpDownAnimator;
	delete flashAnimator;
	delete frameRLeftAnimation;
	delete frameRRightAnimation;
	delete jumpRightAnimation;
	delete jumpLeftAnimation;
	delete flashAnimation;
}