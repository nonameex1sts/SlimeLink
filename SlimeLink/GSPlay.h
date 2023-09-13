#pragma once
#include "GameStateBase.h"

class GSPlay : public GameStateBase
{
private:
	int ilevelNumber;
	// NOTE: if fcheckKeyTime > DELAY_KEY_TIME, the key can be pressed and fcheckKeyTime is set to 0
	//		 if fcheckKeyTime < DELAY_KEY_TIME, each update fcheckKeyTime += deltaTime
	float fcheckKeyTime = DELAY_KEY_TIME + DELAY_STATE_PLAYER + 0.1f;
	int check = 0;

	Picture** pDigit;
	int iNumOfDigit;

public:
	GSPlay(int ilevelNumber);
	~GSPlay();
	int GetLevelNumber();
	void Init(int ilevelNumber);
	void Exit();
	void Update(GLfloat deltaTime);
	void Key(int iKeyPressed);
	void MouseClick(int x, int y, bool isPressed);
	void ResetGameScreen();
	void MouseMove(int x, int y);
	void Draw();
};