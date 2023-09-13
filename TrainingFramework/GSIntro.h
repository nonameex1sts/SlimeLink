#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "AudioManager.h"

class GSIntro : public GameStateBase 
{
private:
	const float DELAY_TIME = 28.0f; // Intro time
	float fTime = 0.0f;
public:
	GSIntro();
	~GSIntro();
	void Exit();
	void Update(GLfloat deltatime);
	void MouseClick(int x, int y, bool isPressed);
};