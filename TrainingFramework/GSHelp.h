#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"
#include "Button.h"
#include "Picture.h"
#include "Animation.h"

class GSHelp : public GameStateBase
{
private:
	int iCurrentPic = 0;
	int iHelpPic;
	int numOfSlime;
	int numOfTorch;
	int* startSlime;
	int* endSlime;
	int* startTorch;
	int* endTorch;
	Animation** slime;
	Animation** torch;
public:
	GSHelp();
	~GSHelp();
	void ReadAnimation();
	void Update(GLfloat deltatime);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
	void Draw();
};