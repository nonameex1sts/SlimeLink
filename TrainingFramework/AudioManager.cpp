#include "stdafx.h"
#include "AudioManager.h"

AudioManager* AudioManager::ms_pInstance = nullptr;

AudioManager::AudioManager()
{
	isMusicOn = true;
	FILE* filePointer = fopen("../TrainingFramework/Audio.txt", "r");
	char* filePath = new char[50];
	int id;
	int isLoop;
	fscanf(filePointer, "#Musics: %d\n", &iNumOfMusic);
	music = new Audio * [iNumOfMusic];
	for (int i = 0; i < iNumOfMusic; i++) {
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);
		fscanf(filePointer, "LOOP %d\n", &isLoop);
		music[i] = new Audio(filePath, isLoop);
	}
	delete filePath;
	fclose(filePointer);
}

AudioManager::~AudioManager()
{
	for (int i = 0; i < iNumOfMusic; i++) {
		delete music[i];
	}
	delete music;
}

Audio* AudioManager::GetAudioById(int id)
{
	return music[id];
}

void AudioManager::setAudioOn(bool isMusicOn)
{
	this->isMusicOn = isMusicOn;
}

bool AudioManager::getAudioStatus()
{
	return isMusicOn;
}