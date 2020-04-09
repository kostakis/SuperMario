#pragma once
#ifndef  ANIMATIONFILMHOLDER_H
#define ANIMATIONFILMHOLDER_H

#include"basic_includes.h"
#include"AnimationFilm.h"
#include <map>
#include "Rectangle.h"
class AnimationFilmHolder
{
private:
	
	AnimationFilmHolder(void) = default;
	~AnimationFilmHolder(void);
	AnimationFilmHolder(const AnimationFilmHolder&) = delete;
	AnimationFilmHolder(AnimationFilmHolder&&) = delete;
	vector< ALLEGRO_CONFIG* >myFilm;
	using Films = std::map<string, AnimationFilm*>;
	Films films;
	std::list<ALLEGRO_BITMAP*> bitmaps;
public:
	
	static AnimationFilmHolder &GetInstance(void);
	
	void LoadAll(const string& text);
	void CleanUp(void);
	AnimationFilm* GetFilm(const string& id);

};
#endif // ! ANIMATIONFILMHOLDER_H
