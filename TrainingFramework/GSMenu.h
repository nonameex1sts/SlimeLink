#pragma once
#include "GameStateBase.h"
#include "../Utilities/utilities.h"
#include "Button.h"
#include <vector>

enum class MenuButtonType {
	PLAY				= 0,
	HELP				= 1,
	CREDIT				= 2,
	SFX					= 3,
	BGMUSIC				= 4,
	EXIT				= 5,
	NUMBER_OF_BUTTONS	= 6
};

class GSMenu : public GameStateBase
{
private:
	Button** pButtons;
	Camera* pCamera;
	int inumButtons;
	Button** buttonTest;
	// Image
	// Sound setting (SFX, Background music)
public:
	GSMenu();
	~GSMenu();
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