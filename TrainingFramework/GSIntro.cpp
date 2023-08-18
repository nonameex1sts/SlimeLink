#include "stdafx.h"
#include "GSIntro.h"
#include "GameStateMachine.h"

GSIntro::GSIntro()
{
	GameStateBase::GameStateBase(StateType::STATE_INTRO);
	Init();
}

GSIntro::~GSIntro()
{
	Exit();
}

void GSIntro::Init() 
{
	// NOTE: Load image
	printf("GSIntro init\n");
}

void GSIntro::Exit()
{
	// NOTE: Delete image
	printf("GSIntro exit\n");
}

void GSIntro::Pause()
{
	printf("GSIntro pause\n");
	// NOTE: blank
}

void GSIntro::Resume()
{
	// NOTE: blank
}

void GSIntro::Update(GLfloat deltatime)
{
	if (fTime < DELAY_TIME)
	{
		fTime += deltatime;
	}
	else 
	{
		GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU, 0);
	}
}

void GSIntro::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSIntro::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: blank
}

void GSIntro::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSIntro::Draw()
{
	// NOTE: Draw intro
}