#include "Sprites.h"
#include "SpriteManager.h"
#include "Player.h"

const Rectangle Sprite::GetBox(void) const
{
	return { x, y, 15, 10 };
}

void Sprite::Move(int dx, int dy)
{
	x += dx, y += dy;
}

void Sprite::SetPos(int _x, int _y)
{
	x = _x; y = _y;
}

void Sprite::SetZorder(unsigned z)
{
	zorder = z;
}

void Sprite::setDrawing(int _x, int _y)
{
	drawingxplayer = _x;
	drawingyplayer = _y;
}

void Sprite::moveDrawing(int _x, int _y)
{
	drawingxplayer += _x;
	drawingyplayer += _y;
}

unsigned Sprite::GetZorder(void)
{
	return zorder;
}

void Sprite::SetFrame(unsigned char i)
{
	if (i != frameNo) {
		//assert(i < currFilm->GetToalFrames());
		frameBox = currFilm->GetFrameBox(i);
	}
}

unsigned char Sprite::GetFrame(void) const
{
	return frameNo;
}

string Sprite::GetTypeId(void)
{
	return typeId;
}

int Sprite::GetDrawingX() const
{
	return drawingxplayer;
}

int Sprite::GetDrawingY() const
{
	return drawingyplayer;
}

void Sprite::SetVisibility(bool v)
{
	isVisible = v;
}

void Sprite::SetWidth(int width)
{
	frameBox.width = width;
}

void Sprite::SetHeight(int height)
{
	frameBox.height = height;
}

void Sprite::SetX(int _x)
{
	x = _x;
}

void Sprite::SetY(int _y)
{
	y = _y;
}

void Sprite::SetDrawingX(int _x)
{
	drawingxplayer = _x;
}

void Sprite::SetDrawingY(int _y)
{
	drawingyplayer = _y;
}

void Sprite::SetDirectMotion(bool b)
{
	directMotion = b;
}

int Sprite::GetX() const
{
	return x;
}

int Sprite::GetY() const
{
	return y;
}

bool Sprite::IsVisible(void) const
{
	return isVisible;
}

bool Sprite::CollisionCheck(const Sprite* s) const
{
	//assert(s);
	int x1 = x;
	int y1 = y;
	int width1 = 15;
	int height1 = 10;
	
	int x2 = s->x;
	int y2 = s->y;
	int width2 = 15;
	int height2 = 10;
	/*if (this->x >= 0 && s->typeId == "Coin") {
		string tempName = this->typeId;
		string s2 = "MARIO";
		if (tempName.find(s2) != std::string::npos) {
			Player* player = (Player*)(this);
			if (player->getMarioSize() == mario_size::SMALL) {
				height2 = 10;
			}
			else {
				height2 = 29;
			}
		}
	}*/

	if (
		(x1 < x2 + width2) &&
		(x1 + width1 > x2) &&
		(y1 < y2 + height2) &&
		(y1 + height1 > y2)
		) 
	{
  		return true;
	}

	return false;
}

Sprite::Sprite(int _x, int _y, AnimationFilm* film, const string& _typeId) : x(_x), y(_y), currFilm(film), typeId(_typeId), drawingxplayer(_x), drawingyplayer(_y)
{
	if (_typeId != "1MARIO_PLAYER") {
		frameNo = currFilm->GetToalFrames();
		SetFrame(0);
		SpriteManager::GetInstance().Add(this);
	}
}

Sprite::~Sprite()
{
	SpriteManager::GetInstance().Remove(this);
	dying = true;
}

void Sprite::Display(ALLEGRO_BITMAP* dest, const struct ViewData* viewdata) const
{
	if (isVisible) {
		al_draw_bitmap_region(currFilm->GetBitmap(),
			frameBox.x * frameBox.width, frameBox.y * frameBox.height,
			frameBox.width, frameBox.height, x - viewdata->x, y - viewdata->y, 0);
	}
}

void Sprite::DisplayPlayer()
{
	if (isVisible) {
		al_draw_bitmap_region(currFilm->GetBitmap(),
			frameBox.x * frameBox.width, frameBox.y * frameBox.height,
			frameBox.width, frameBox.height, drawingxplayer, drawingyplayer, 0);
	}
}
