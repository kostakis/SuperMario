#include "SoundManager.h"

SoundManager::~SoundManager()
{
	CleanUp();
}

void SoundManager::CleanUp()
{
	for (auto it = sounds.begin(); it != sounds.end(); it++) {
		al_destroy_sample_instance(it->second);
	}
	sounds.clear();

	for (auto* i : samples) {
		al_destroy_sample(i);
	}
	samples.clear();
}

SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;

	return instance;
}

void SoundManager::AddSound(const string state, const std::string& path)
{
	ALLEGRO_SAMPLE* mySample = al_load_sample(path.c_str());
	if (!mySample) {
		cerr << "Can not load allegro sample" << endl;
		exit(EXIT_FAILURE);
	}
	ALLEGRO_SAMPLE_INSTANCE* sample = al_create_sample_instance(mySample);
	if (!sample) {
		cerr << "Can not load allegro sample instance" << endl;
		exit(EXIT_FAILURE);
	}
	sounds[state] = sample;
	samples.push_back(mySample);
}

void SoundManager::PlaySound(const string state, ALLEGRO_PLAYMODE mode)
{
	al_attach_sample_instance_to_mixer(sounds[state], al_get_default_mixer());
	bool temp = al_set_sample_instance_playing(sounds[state], true);
}

void SoundManager::EditSoundSpeed(const string& sound, float speed)
{
	al_set_sample_instance_speed(sounds[sound], speed);
}

void SoundManager::EditSoundGain(const string& sound, float gain)
{
	al_set_sample_instance_gain(sounds[sound], gain);
}

void SoundManager::StopSound(const string state)
{
	al_set_sample_instance_playing(sounds[state],false);
}
