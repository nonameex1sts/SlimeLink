#include "stdafx.h"
#include "GSPause.h"

GSPause::GSPause()
{
	GameStateBase::GameStateBase(StateType::STATE_PAUSE);
	Init();
}

GSPause::~GSPause()
{
	Exit();
}

void GSPause::Init()
{
	// NOTE: Load button
	printf("GSPause init\n");
}

void GSPause::Exit()
{
	// NOTE: Delete button
	printf("GSPause exit\n");
}

void GSPause::Pause()
{
	// NOTE: blank
}

void GSPause::Resume()
{
	// NOTE: blank
}

void GSPause::Update(GLfloat deltatime)
{
}

void GSPause::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSPause::MouseClick(int x, int y, bool isPressed)
{
}

void GSPause::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSPause::Draw()
{
	// NOTE: Draw button
}