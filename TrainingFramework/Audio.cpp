#include "stdafx.h"
#include "Audio.h"

Audio::Audio(char* file, int isLoop)
{
	music.openFromFile(file);
	if (isLoop == 1)
	{
		music.setLoop(true);
	}
}

Audio::~Audio() {}

void Audio::PlayMusic()
{
	music.setVolume(30);
	music.play();
}

void Audio::StopMusic()
{
	music.stop();
}

void Audio::SetVolume(float volume)
{
	music.setVolume(volume);
}