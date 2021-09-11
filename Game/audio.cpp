#include "Audio.h"

void Audio::initializeAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
}

void Audio::playSound1()
{
	result = system->playSound(sound1, 0, false, &channel);
}

void Audio::playSoundtrack()
{
	result = system->playSound(sound2, 0, false, &channel);
}

void Audio::loadSounds(std::string soundeffect, std::string soundtrack)
{
	const char* effectc = soundeffect.c_str();
	result = system->createSound(effectc, FMOD_DEFAULT, 0, &sound1);
	result = sound1->setMode(FMOD_LOOP_OFF);

	const char* trackc = soundtrack.c_str();
	result = system->createStream(trackc, FMOD_DEFAULT, 0, &sound2);
	result = sound2->setMode(FMOD_LOOP_OFF);
}

void Audio::updateSounds()
{
	result = system->update();
}

Audio::Audio()
{
}

Audio::~Audio()
{
}