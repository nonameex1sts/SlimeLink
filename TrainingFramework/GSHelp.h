#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"
#include "Button.h"
#include "Picture.h"

class GSHelp : public GameStateBase
{
private:
	int iCurrentPic = 0;
	int iHelpPic = 4;
public:
	GSHelp();
	~GSHelp();
	void Pause();
	void Resume();
	void Update(GLfloat deltatime);
	void Key(int keyPressed);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
};