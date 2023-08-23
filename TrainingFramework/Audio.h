#pragma once
#include "SFML/Audio.hpp"

class Audio {
private:
	sf::Music music;
public:
	Audio(char* file, int isLoop);
	~Audio();
	void PlayMusic();
	void StopMusic();
	void SetVolume(float volume);
};