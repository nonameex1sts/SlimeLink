#include "stdafx.h"
#include "GSCredit.h"

GSCredit::GSCredit()
{
	Init("../TrainingFramework/GSCredit.txt", StateType::STATE_CREDIT);
}

GSCredit::~GSCredit()
{
	Exit();
}

void GSCredit::Pause()
{
	// NOTE: blank
}

void GSCredit::Resume()
{
	// NOTE: blank
}

void GSCredit::Update(GLfloat deltatime)
{
	//NOTE: blank
}

void GSCredit::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSCredit::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check all button if it got click or not
	if (isPressed && pButtons != nullptr)
	{
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y, isPressed);
		}
	}
}

void GSCredit::MouseMove(int x, int y)
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->MouseMove(x, y);
	}
}