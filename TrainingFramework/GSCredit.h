#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"
#include "Button.h"

class GSCredit : public GameStateBase
{
private:
	Camera* pCamera;
	int inumButtons;
	Button** pButtons;
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