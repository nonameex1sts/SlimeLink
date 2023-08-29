#include "stdafx.h"
#include "Button.h"
#include "GameStateMachine.h"
#include "AudioManager.h"

Button::Button() {}

Button::Button(Model* pModel, Texture* pTexture, Camera* pCamera, Shaders* pShader, Vector3 position, Vector3 rotation, Vector3 scale, int iType, int isActive) 
	: Object(pModel, pTexture, pCamera, pShader, position, rotation, scale)
{
	this->iType = iType;
	if (isActive == 1)
	{
		this->isActive = true;
	}
	else 
	{
		this->isActive = false;
	}
}

void Button::Update()
{
}


void Button::Key()
{
}

void Button::Move()
{
}

void Button::Rotate()
{
}

bool Button::getActive()
{
	return isActive;
}

// If that button is click, check what type is it to do the right job
void Button::MouseClick(int x, int y)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2)) 
	{
		AudioManager::GetInstance()->GetAudioById(2)->PlayMusic();
		if (iType == PLAY) 
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, 1);
		}
		if (iType == LEVEL_SELECT)
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_LEVEL_SELECT, 1);
		}
		if (iType == HELP)
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_HELP, 1);
		}
		if (iType == CREDIT)
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_CREDIT, 1);
		}
		if (iType == RESUME)
		{
			GameStateMachine::GetInstance()->PopState();
		}
		if (iType == MENU)
		{
			// BUGFIX: Stop when its menu state
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PopState();
		}
		if (iType == PAUSE_TO_SELECT)
		{
			// BUGFIX: Stop when its pause to select state
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PopState();
		}
		if (iType == EXIT)
		{
			exit(1);
		}
		if (iType == BGM)
		{
			isActive = !isActive;
			if (isActive)
			{
				AudioManager::GetInstance()->GetAudioById(0)->SetVolume(30);
			}
		}
		if (iType == NOBGM)
		{
			isActive = !isActive;
			if (isActive)
			{
				AudioManager::GetInstance()->GetAudioById(0)->SetVolume(0);
			}
		}
		if (iType == BACK)
		{
			GameStateMachine::GetInstance()->PopState();
		}
	}
}

void Button::MouseClickReset(int x, int y, int iLevel)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		AudioManager::GetInstance()->GetAudioById(2)->PlayMusic();
		if (iType == RESET)
		{
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, iLevel);
		}
		else if (iType == PAUSE)
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE, 1);
		}
	}
}

// This is for the prev page and next page button
// index is for what page is it, and sum is for how many pages there is on that state
void Button::MouseClick(int x, int y, int* index, int sum)
{
	// Check if the x, y area that mouse click in is in the area of the button
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		AudioManager::GetInstance()->GetAudioById(2)->PlayMusic();
		if (iType == BACK)
		{
			GameStateMachine::GetInstance()->PopState();
		}
		if (iType == PREV_PAGE)
		{
			if ((*index) == 0) 
			{
				(*index) = sum - 1;
			}
			else
			{
				(*index)--;
			}
			printf("prev click\n");
		}
		if (iType == NEXT_PAGE)
		{
			if ((*index) == sum - 1)
			{
				(*index) = 0;
			}
			else 
			{
				(*index)++;
			}
			printf("next click\n");
		}
	}
}

void Button::MouseMove()
{
}


Button::~Button() {}