#include "stdafx.h"
#include "AudioManager.h"

AudioManager* AudioManager::ms_pInstance = nullptr;

AudioManager::AudioManager()
{
	isSFXOn = true;
	isBGMOn = true;
	// Read audio and create them
	FILE* filePointer;

	try
	{
		filePointer = fopen("../Resources/StateData/Audio.txt", "r");
	}
	catch (...)
	{
		printf("Cannot open audio file");
	}
	
	char* filePath = new char[50];
	int id;
	int isLoop;
	int isSfx;
	fscanf(filePointer, "#Musics: %d\n", &iNumOfMusic);
	music = new Audio * [iNumOfMusic];
	for (int i = 0; i < iNumOfMusic; i++) {
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "FILE %s\n", filePath);
		fscanf(filePointer, "LOOP %d\n", &isLoop);
		fscanf(filePointer, "SFX %d\n", &isSfx);
		music[i] = new Audio(filePath, isLoop, isSfx);
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

void AudioManager::setSFXOn(bool isSFXOn)
{
	this->isSFXOn = isSFXOn;
}

bool AudioManager::getSFXStatus()
{
	return isSFXOn;
}

void AudioManager::setBGMOn(bool isBGMOn)
{
	this->isBGMOn = isBGMOn;
}

bool AudioManager::getBGMStatus()
{
	return isBGMOn;
}

// Set BGM is on or not
void AudioManager::setBGM(bool isOn)
{
	for (int i = 0; i < iNumOfMusic; i++)
	{
		if (!music[i]->GetIsSfx())
		{
			if (isOn)
			{
				music[i]->SetVolume(30);
			}
			else {
				music[i]->SetVolume(0);
			}
		}
	}
}

// Set SFX is on or not
void AudioManager::setSFX(bool isOn)
{
	for (int i = 0; i < iNumOfMusic; i++)
	{
		if (music[i]->GetIsSfx())
		{
			if (isOn)
			{
				music[i]->SetVolume(30);
			}
			else 
			{
				music[i]->SetVolume(0);
			}
		}
	}
}