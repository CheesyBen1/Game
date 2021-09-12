#pragma once
#include "fmod.hpp"
#include <string>

class Audio
{
public:
	FMOD::System* system;
	FMOD::Sound* sound1, * sound2;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extradriverdata = 0;

	void initializeAudio();
	void playSound1(bool pause, float pan, float pitch, float vol, FMOD_MODE loop);
	void playSoundtrack(bool pause, float pan, float pitch, float vol, FMOD_MODE loop);
	void loadSounds(std::string soundeffect, std::string soundtrack);
	void updateSounds();

	Audio();
	~Audio();
};
