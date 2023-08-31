#include "stdafx.h"
#include "Audio.h"

Audio::Audio(char* file, int isLoop, int sfxNoti)
{
	volume = 30;
	music.openFromFile(file);
	if (isLoop == 1)
	{
		music.setLoop(true);
	}
	if (sfxNoti == 1)
	{
		isSfx = true;
	}
	else
	{
		isSfx = false;
	}
}

Audio::~Audio() {}

void Audio::PlayMusic()
{
	music.setVolume(volume);
	music.play();
}

void Audio::StopMusic()
{
	music.stop();
}

void Audio::SetVolume(float volume)
{
	music.setVolume(volume);
	this->volume = volume;
}

bool Audio::GetIsSfx()
{
	return isSfx;
}