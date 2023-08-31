#pragma once
#include "SFML/Audio.hpp"

class Audio {
private:
	sf::Music music;
	bool isSfx;
	int volume;
public:
	Audio(char* file, int isLoop, int isSfx);
	~Audio();
	void PlayMusic();
	void StopMusic();
	void SetVolume(float volume);
	bool GetIsSfx();
};