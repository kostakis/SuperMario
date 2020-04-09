#pragma once
#ifndef  SPRITES_H
#define SPRITES_H

#include "basic_includes.h"
#include "AnimationFilm.h"
#include "Rectangle.h"
#include "AnimationFilm.h"
#include "Animation.h"
#include "AnimationFilmHolder.h"
#include "ViewData.h"
#include "DestructionManager.h"

class Sprite :
	public LatelyDestroyable {
protected:
	unsigned char frameNo = 0;
	Rectangle frameBox;
	int x = 0;
	int y = 0;
	int drawingxplayer = 0;
	int drawingyplayer = 0;
	bool isVisible = false;
	AnimationFilm* currFilm = nullptr;
	unsigned zorder = 0;
	string typeId, stateId;
	bool directMotion = false;
public:
	Sprite(void) = default;
	Sprite(int _x, int _y, AnimationFilm* film, const string& _typeId = "");

	virtual ~Sprite();

	void SetPos(int _x, int _y);
	void SetZorder(unsigned z);
	void setDrawing(int _x, int _y);
	void SetFrame(unsigned char i);
	void SetVisibility(bool v);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetX(int _x);
	void SetY(int _y);
	void SetDrawingX(int _x);
	void SetDrawingY(int _y);
	void SetDirectMotion(bool b);

	int GetX() const;
	int GetY() const;
	void Move(int dx, int dy);
	void moveDrawing(int _x, int _y);
	bool IsVisible(void) const;
	bool CollisionCheck(const Sprite* s) const;
	virtual void Display(ALLEGRO_BITMAP* dest, const struct ViewData* viewdata) const;
	void DisplayPlayer();
	const Rectangle GetBox(void) const;
	unsigned GetZorder(void);
	unsigned char GetFrame(void) const;
	string GetTypeId(void);
	int GetDrawingX() const;
	int GetDrawingY() const;
	const Rectangle GetBoxProper(void) const;
};
#endif // ! SPRITES_H