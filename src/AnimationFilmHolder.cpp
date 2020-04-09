#include "AnimationFilmHolder.h"

AnimationFilmHolder::~AnimationFilmHolder(void)
{
	CleanUp();
}

AnimationFilmHolder& AnimationFilmHolder::GetInstance(void)
{
	static AnimationFilmHolder instance;
	return instance;
}

void AnimationFilmHolder::LoadAll(const string& text) {

	myFilm.push_back( al_load_config_file(text.c_str()));
	if (!myFilm.back()) {
		cerr << "Can not load config file" << endl;
		exit(EXIT_FAILURE);
	}

	const char* bitmap_name = al_get_config_value(myFilm.back(), "", "BITMAP_PATH");
	if (!bitmap_name) {
		cerr << "Cant read config value" << endl;
		exit(EXIT_FAILURE);
	}
	std::string cpp_string_bitmap(bitmap_name);
	std::string fullPath = "media/" + cpp_string_bitmap;

	ALLEGRO_BITMAP* animationBitmap = al_load_bitmap(fullPath.c_str());
	if (!animationBitmap) {
		cerr << "Cant not load bitmap for films" << endl;
		exit(EXIT_FAILURE);
	}
	bitmaps.push_back(animationBitmap);

	const char* id;
	int i = 0;
	int spritecounter = 0;
	const char* name = "ANIMATION ";
	std::string cpp_string_anim(name);
	std::string full_animation_id = cpp_string_anim + std::to_string(i);
	std::vector<Rectangle> myRecs;
	while (id = al_get_config_value(myFilm.back(), full_animation_id.c_str(), "NAME"))
	{
		if (!id) {
			cerr << "Can not load config value" << endl;
			exit(EXIT_FAILURE);
		}
		const char* sprite = al_get_config_value(myFilm.back(), full_animation_id.c_str(), "NUMBER OF SPRITES");
		std::stringstream strValue;
		strValue << sprite;
		int counter = 0;
		strValue >> counter;
		for (spritecounter = 0; spritecounter < counter; spritecounter++)
		{
			std::string cpp_string_x = "X" + std::to_string(spritecounter);
			std::string cpp_string_y = "Y" + std::to_string(spritecounter);
			std::string cpp_string_w = "WIDTH" + std::to_string(spritecounter);
			std::string cpp_string_h = "HEIGHT" + std::to_string(spritecounter);

			const char* x = al_get_config_value(myFilm.back(), full_animation_id.c_str(), cpp_string_x.c_str());
			const char* y = al_get_config_value(myFilm.back(), full_animation_id.c_str(), cpp_string_y.c_str());
			const char* width = al_get_config_value(myFilm.back(), full_animation_id.c_str(), cpp_string_w.c_str());
			const char* heigth = al_get_config_value(myFilm.back(), full_animation_id.c_str(), cpp_string_h.c_str());

			Rectangle tempRec;
			tempRec.x = atoi(x);
			tempRec.y = atoi(y);
			tempRec.width = atoi(width);
			tempRec.height = atoi(heigth);
			myRecs.push_back(tempRec);
		}
		spritecounter = 0;
		films[id] = new AnimationFilm(animationBitmap, myRecs, id);
		i++;
		full_animation_id = cpp_string_anim + std::to_string(i);
		myRecs.clear();
	}
}

void AnimationFilmHolder::CleanUp(void)
{
	for (auto& i : films)
		delete(i.second);
	films.clear();

	for (auto& i : myFilm)
		al_destroy_config(i);
	myFilm.clear();

	for (auto* i : bitmaps)
		al_destroy_bitmap(i);
	bitmaps.clear();
}
AnimationFilm* AnimationFilmHolder::GetFilm(const string& id)
{
	auto i = films.find(id);
	return i != films.end() ? i->second : nullptr;
}
