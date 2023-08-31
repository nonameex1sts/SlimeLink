#include "stdafx.h"
#include "GSPause.h"

GSPause::GSPause()
{
	Init("../TrainingFramework/GSPause.txt", StateType::STATE_PAUSE);
}

GSPause::~GSPause()
{
	Exit();
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
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y, isPressed);
		}
	}
}

void GSPause::MouseMove(int x, int y)
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->MouseMove(x, y);
	}
}