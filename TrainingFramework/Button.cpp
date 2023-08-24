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
		if (iType == PAUSE)
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE, 1);
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

void Button::MouseClick(int x, int y, int* index, int sumPicture)
{
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
				(*index) = sumPicture - 1;
			}
			else
			{
				(*index)--;
			}
			printf("prev click\n");
		}
		if (iType == NEXT_PAGE)
		{
			if ((*index) == sumPicture - 1)
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