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
	if (isPressed)
	{
		for (int i = 0; i < static_cast<int>(PauseButtonType::NUMBER_OF_BUTTONS); i++)
		{
			// NOTE:: Check if that button is clicked
		}
	}
}

void GSPause::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSPause::Draw()
{
	// NOTE: Draw button
}