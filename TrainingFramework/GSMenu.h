#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "Button.h"
#include "Picture.h"
#include "AudioManager.h"

class GSMenu : public GameStateBase
{
private:
	// Image
	// Sound setting (SFX, Background music)
public:
	GSMenu();
	~GSMenu();
	void Pause();
	void Resume();
	void Update(GLfloat deltatime);
	void Key(int keyPressed);
	void MouseClick(int x, int y, bool isPressed);
	void MouseMove(int x, int y);
};