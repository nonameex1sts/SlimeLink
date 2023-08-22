#include "stdafx.h"
#include "Button.h"
#include "GameStateMachine.h"

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
		if (iType == PLAY) 
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, 1);
		}
		if (iType == HELP)
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_HELP, 1);
		}
		if (iType == CREDIT)
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_CREDIT, 1);
		}
		if (iType == EXIT)
		{
			exit(1);
		}
		if (iType == BGM)
		{
			isActive = !isActive;
		}
		if (iType == NOBGM)
		{
			isActive = !isActive;
		}
	}
}

void Button::MouseMove()
{
}


Button::~Button() {}