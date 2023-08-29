#pragma once
#include "Audio.h"

class AudioManager
{
private:
	Audio** music;
	static AudioManager* ms_pInstance;
	int iNumOfMusic;
	AudioManager();
	~AudioManager();
	bool isMusicOn;
public:
	static void CreateInstance()
	{
		if (ms_pInstance == nullptr)
			ms_pInstance = new AudioManager();
	};

	static AudioManager* GetInstance()
	{
		return ms_pInstance;
	};

	static void DestroyInstance()
	{
		if (ms_pInstance != nullptr)
		{
			delete ms_pInstance;
			ms_pInstance = nullptr;
		}
	};
	Audio* GetAudioById(int id);
	void setAudioOn(bool isMusicOn);
	bool getAudioStatus();
};