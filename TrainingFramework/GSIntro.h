#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"

class GSIntro : public GameStateBase 
{
private:
	// image
	const float DELAY_TIME = 2.0f;
	float fTime = 0.0f;
public:
	GSIntro();
	~GSIntro();
	void Init();
	void Exit();
	void Pause();
	void Resume();
	void Update(GLfloat deltatime);
	void Key(int keyPressed);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
	void Draw();
};