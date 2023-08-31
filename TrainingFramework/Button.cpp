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

void Button::setActive(bool isActive)
{
	this->isActive = isActive;
}

int Button::getType()
{
	return iType;
}

// If that button is click, check what type is it to do the right job
void Button::MouseClick(int x, int y, bool isPressed)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2)) 
	{
		AudioManager::GetInstance()->GetAudioById(2)->PlayMusic();
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
			// BUGFIX: Stop when its menu 
			GameStateMachine::GetInstance()->PopState(StateType::STATE_MENU);
		}
		if (iType == PAUSE_TO_SELECT)
		{
			// BUGFIX: Stop when its pause to select state
			GameStateMachine::GetInstance()->PopState(StateType::STATE_LEVEL_SELECT);
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
				AudioManager::GetInstance()->setAudioOn(true);
			}
		}
		if (iType == NOBGM)
		{
			isActive = !isActive;
			if (isActive)
			{
				AudioManager::GetInstance()->GetAudioById(0)->SetVolume(0);
				AudioManager::GetInstance()->setAudioOn(false);
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
		if (iType == RESET) {
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, iLevel);
		}
		else if (iType == PAUSE) {
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE, 1);
		}
		else if (iType == PAUSE_TO_SELECT)
		{	
			GameStateMachine::GetInstance()->PopState(StateType::STATE_LEVEL_SELECT);
		}
		else if (iType == NEXT_LEVEL)
		{
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, iLevel + 1);
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

void Button::MouseMove(int x, int y)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		if (iType == LEVEL_SELECT)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(45));
		}
		if (iType == HELP)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(48));
		}
		if (iType == CREDIT)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(49));
		}
		if (iType == RESUME)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(58));
		}
		if (iType == MENU)
		{
			// BUGFIX: Stop when its menu 
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(57));
		}
		if (iType == PAUSE_TO_SELECT)
		{
			// BUGFIX: Stop when its pause to select state
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(47));
		}
		if (iType == EXIT)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(46));
		}
		if (iType == BGM)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(50));
		}
		if (iType == NOBGM)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(51));
		}
		if (iType == BACK)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(52));
		}
		if (iType == PREV_PAGE)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(53));
		}
		if (iType == NEXT_PAGE)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(54));
		}
		if (iType == PAUSE)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(55));
		}
		if (iType == RESET)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(56));
		}
		if (iType == NEXT_LEVEL)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(78));
		}
	}
	else
	{
		if (iType == LEVEL_SELECT)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(5));
		}
		if (iType == HELP)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(14));
		}
		if (iType == CREDIT)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(15));
		}
		if (iType == RESUME)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(30));
		}
		if (iType == MENU)
		{
			// BUGFIX: Stop when its menu 
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(29));
		}
		if (iType == PAUSE_TO_SELECT)
		{
			// BUGFIX: Stop when its pause to select state
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(12));
		}
		if (iType == EXIT)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(4));
		}
		if (iType == BGM)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(16));
		}
		if (iType == NOBGM)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(17));
		}
		if (iType == BACK)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(19));
		}
		if (iType == PREV_PAGE)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(20));
		}
		if (iType == NEXT_PAGE)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(21));
		}
		if (iType == PAUSE)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(26));
		}
		if (iType == RESET)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(27));
		}
		if (iType == NEXT_LEVEL)
		{
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(77));
		}
	}
}

Button::~Button() {}