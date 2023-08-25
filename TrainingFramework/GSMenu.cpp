#include "stdafx.h"
#include "GSMenu.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "GameStateBase.h"

GSMenu::GSMenu()
{
	Init("../TrainingFramework/GSMenu.txt", "GSMenu");
	GameStateBase::GameStateBase(StateType::STATE_MENU);
}

GSMenu::~GSMenu()
{
	Exit("GSMenu");
}

void GSMenu::Pause()
{
	// NOTE: blank
	printf("GSMenu pause\n");
}

void GSMenu::Resume()
{
	// NOTE: blank
	AudioManager::GetInstance()->GetAudioById(0)->PlayMusic();
	printf("GSMenu resume\n");
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
	if (isPressed)
	{
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y);
		}
	}
}

void GSMenu::MouseMove(int x, int y)
{
	// NOTE: blank
}