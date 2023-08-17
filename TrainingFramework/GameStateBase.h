#pragma once
#pragma once
#include "../Utilities/utilities.h"

enum class StateType
{
	STATE_INVALID = 0,
	STATE_INTRO = 1,
	STATE_MENU = 2,
	STATE_LEVEL_SELECT = 3,
	STATE_HELP = 4,
	STATE_CREDIT = 5,
	STATE_PLAY = 6,
	STATE_PAUSE = 7
};

class GameStateBase
{
private:
	StateType e_type;

public:
	GameStateBase();
	GameStateBase(StateType e_type);
	virtual ~GameStateBase();
	virtual void Init();
	virtual void Exit();
	virtual void Pause();
	virtual void Resume();
	virtual void Update(GLfloat deltatime);
	virtual void Draw();
	StateType GetStateType();
	GameStateBase* CreateState(StateType type);
};