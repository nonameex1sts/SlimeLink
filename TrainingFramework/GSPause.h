#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"

enum class ButtonType {
	RESUME				= 0,
	HELP				= 1,
	LEVEL_SELECT		= 2,
	MENU				= 3,
	SFX					= 4,
	BGMUSIC				= 5,
	NUMBER_OF_BUTTONS	= 6
};

class GSPause : public GameStateBase
{
private:
	// Button (resume, help, level select, menu, music, sfx)
public:
	GSPause();
	~GSPause();
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