#include "stdafx.h"
#include "Button.h"
#include "GameStateMachine.h"

Button::Button() {}

Button::Button(Model* pModel, Texture* pTexture, Camera* pCamera, Shaders* pShader, Vector3 position, Vector3 rotation, Vector3 scale, int iType) 
	: Object(pModel, pTexture, pCamera, pShader, position, rotation, scale)
{
	this->iType = iType;
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

void Button::MouseClick(int x, int y)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2)) 
	{
		if (iType == PLAY) 
		{
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, 1);
		}
	}
}

void Button::MouseMove()
{
}


Button::~Button() {}