#pragma once
#ifndef ANIMATIONFILM_H
#define ANIMATIONFILM_H
#include"basic_includes.h"

/*Animation film holds all the frames for a charcter actions/movement/etc...*/
class AnimationFilm
{
private:
	vector<Rectangle> boxes;
	ALLEGRO_BITMAP *bitmap= nullptr; //Bitmap that contains all the frames
	string id;
public:
	unsigned int GetToalFrames() const {
		return boxes.size();
	}

	ALLEGRO_BITMAP* GetBitmap() const {
		return bitmap;
	}

	string GetId() const {
		return id;
	}

	Rectangle GetFrameBox(unsigned int frameNo) {
		//assert(boxes.size() > frameNo);
		return boxes[frameNo];
	}

	void SetBitmap(ALLEGRO_BITMAP* b) {
		//assert(b);
		bitmap = b;
	}


	AnimationFilm(const string& _id) : id(_id) {};
	AnimationFilm(ALLEGRO_BITMAP* b, const std::vector<Rectangle>& box, const std::string& _id) {
		bitmap = b;
		boxes = box;
		id = _id;
	}

	~AnimationFilm() = default;
};
#endif // !ANIMATIONFILM_H