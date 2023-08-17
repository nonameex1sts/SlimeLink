#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"

class GSCredit : public GameStateBase
{
private:
	// image
	// backgroundImage
	// backButton
public:
	GSCredit();
	~GSCredit();
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