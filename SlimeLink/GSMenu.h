#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "Button.h"
#include "Picture.h"
#include "AudioManager.h"
#include "Animation.h"

class GSMenu : public GameStateBase
{
private:
	Animation *slime;
public:
	GSMenu();
	~GSMenu();
	void Resume();
	void Update(GLfloat deltatime);
	void Key(int keyPressed);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
	void Draw();
};