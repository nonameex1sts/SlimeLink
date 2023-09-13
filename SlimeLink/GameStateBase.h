#pragma once
#include "../Utilities/utilities.h"
#include "Globals.h"
#include "ResourceManager.h"
#include "Button.h"
#include "Picture.h"
#include <stdlib.h>

enum class StateType
{
	STATE_INVALID = 0,
	STATE_INTRO = 1,
	STATE_MENU = 2,
	STATE_LEVEL_SELECT = 3,
	STATE_HELP = 4,
	STATE_CREDIT = 5,
	STATE_PLAY = 6,
	STATE_PAUSE = 7,
};

class GameStateBase
{
protected:
	StateType e_type;
	Camera* pCamera;
	int inumButtons;
	int inumPics;
	Button** pButtons;
	Picture** pPictures;

public:
	GameStateBase();
	virtual ~GameStateBase();
	virtual void Init(char* file, StateType e_type);
	virtual void Exit();
	virtual void Pause();
	virtual void Resume();
	virtual void Update(GLfloat deltatime);
	virtual void Key(int iKeyPressed);
	virtual void MouseClick(int x, int y, bool isPressed);
	virtual void MouseMove(int x, int y);
	virtual void Draw();
	StateType GetStateType();
	GameStateBase* CreateState(StateType type);
	GameStateBase* CreateStatePlay(int ilevelNumber);
};