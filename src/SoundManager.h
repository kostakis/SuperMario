#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "basic_includes.h"

class SoundManager
{
private:
	SoundManager(void) = default;
	~SoundManager(void);
	SoundManager(const SoundManager&) = delete;
	SoundManager(SoundManager&&) = delete;
	std::map<string, ALLEGRO_SAMPLE_INSTANCE*> sounds;
	std::list<ALLEGRO_SAMPLE*> samples;
public:
	void CleanUp();
	static SoundManager& GetInstance();
	void AddSound(const string state,const std::string& path);
	void PlaySound(const string state, ALLEGRO_PLAYMODE mode);
	void EditSoundSpeed(const string& sound, float speed);
	void EditSoundGain(const string& sound, float gain);
	void StopSound(const string state);
};
#endif // !SOUNDMANAGER_H