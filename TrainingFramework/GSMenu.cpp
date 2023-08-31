#include "stdafx.h"
#include "GSMenu.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "GameStateBase.h"

GSMenu::GSMenu()
{
	Init("../TrainingFramework/GSMenu.txt", StateType::STATE_MENU);
}

GSMenu::~GSMenu()
{
	Exit();
}

void GSMenu::Pause()
{
	// NOTE: blank
}

void GSMenu::Resume()
{
	
}

void GSMenu::Update(GLfloat deltatime)
{
}

void GSMenu::Key(int iKeyPressed)
{
	if (iKeyPressed == KEY_MOVE_RIGHT) {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, 1);
	}
}

void GSMenu::MouseClick(int x, int y, bool isPressed)
{
	if (isPressed && pButtons != nullptr)
	{

		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y, isPressed);
		}
	}
}

void GSMenu::MouseMove(int x, int y)
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->MouseMove(x, y);
	}
}