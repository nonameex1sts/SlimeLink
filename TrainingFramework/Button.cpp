#include "stdafx.h"
#include "Button.h"
#include "GameStateMachine.h"
#include "AudioManager.h"
#include "SceneManager.h"

Button::Button() {}

Button::Button(Model* pModel, Texture* pTexture, Camera* pCamera, Shaders* pShader, Vector3 position, Vector3 rotation, Vector3 scale, int iType, int isActive) 
	: Object(pModel, pTexture, pCamera, pShader, position, rotation, scale)
{
	this->iType = iType;
	//Active to know when we init it, it show the button or not
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
		switch (iType)
		{
		case LEVEL_SELECT:
			GameStateMachine::GetInstance()->PushState(StateType::STATE_LEVEL_SELECT, 1);
			break;
		case HELP:
			GameStateMachine::GetInstance()->PushState(StateType::STATE_HELP, 1);
			break;
		case CREDIT:
			GameStateMachine::GetInstance()->PushState(StateType::STATE_CREDIT, 1);
			break;
		case RESUME:
			GameStateMachine::GetInstance()->PopState();
			break;
		case MENU:
			AudioManager::GetInstance()->GetAudioById(0)->PlayMusic();
			GameStateMachine::GetInstance()->PopState(StateType::STATE_MENU);
			break;
		case PAUSE_TO_SELECT:
			GameStateMachine::GetInstance()->PopState(StateType::STATE_LEVEL_SELECT);
			break;
		case EXIT:
			exit(1);
			break;
		case BACK:
			GameStateMachine::GetInstance()->PopState();
			break;
		case BGM:
			isActive = !isActive;
			if (isActive)
			{
				AudioManager::GetInstance()->setBGM(true);
				AudioManager::GetInstance()->setBGMOn(true);
			}
		case NOBGM:
			isActive = !isActive;
			if (isActive)
			{
				AudioManager::GetInstance()->setBGM(false);
				AudioManager::GetInstance()->setBGMOn(false);
			}
			break;
		case SFX:
			isActive = !isActive;
			if (isActive)
			{
				AudioManager::GetInstance()->setSFX(true);
				AudioManager::GetInstance()->setSFXOn(true);
			}
		case NOSFX:
			isActive = !isActive;
			if (isActive)
			{
				AudioManager::GetInstance()->setSFX(false);
				AudioManager::GetInstance()->setSFXOn(false);
			}
			break;
		}
	}
}

// This is for reset
void Button::MouseClickReset(int x, int y, int iLevel, bool* isReset)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		AudioManager::GetInstance()->GetAudioById(2)->PlayMusic();
		switch (iType)
		{
		case RESET:
			SceneManager::DestroyInstance();
			SceneManager::CreateInstance(iLevel);
			*isReset = true;
			break;
		case PAUSE:
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE, 1);
			break;
		case PAUSE_TO_SELECT:
			GameStateMachine::GetInstance()->PopState(StateType::STATE_LEVEL_SELECT);
			break;
		case NEXT_LEVEL:
			GameStateMachine::GetInstance()->PopState();
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, iLevel + 1);
			break;
		}
	}
}

void Button::MouseClickResetGame(int x, int y, int* typeButton)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		switch (iType)
		{
		case RESET_GAME:
			*typeButton = 1;
			break;
		case YES:
			ResetGame();

			*typeButton = 2;
			break;
		case NO:
			*typeButton = 3;
			break;
		}
	}
}

void Button::ResetGame()
{
	FILE* writePoiter = fopen("../Resources/Level/Level.txt", "w");

	for (int i = 1; i <= NUM_OF_LEVELS; i++) {
		fprintf(writePoiter, "%d\n", 0);
	}

	fclose(writePoiter);
}

// This is for the prev page and next page button
// index is for what page is it, and sum is for how many pages there is on that state
void Button::MouseClick(int x, int y, int* index, int sum)
{
	// Check if the x, y area that mouse click in is in the area of the button
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		AudioManager::GetInstance()->GetAudioById(2)->PlayMusic();
		switch (iType)
		{
		case BACK:
			GameStateMachine::GetInstance()->PopState();
			break;
		case PREV_PAGE:
			if ((*index) == 0)
			{
				(*index) = sum - 1;
			}
			else
			{
				(*index)--;
			}
			break;
		case NEXT_PAGE:
			if ((*index) == sum - 1)
			{
				(*index) = 0;
			}
			else
			{
				(*index)++;
			}
			break;
		}
	}
}

// This is for the on and off button effect when the mouse hover in
void Button::MouseMove(int x, int y)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		switch (iType)
		{
		case LEVEL_SELECT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(45));
			break;
		case HELP:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(48));
			break;
		case CREDIT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(49));
			break;
		case RESUME:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(58));
			break;
		case MENU:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(57));
			break;
		case PAUSE_TO_SELECT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(47));
			break;
		case EXIT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(46));
			break;
		case BGM:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(50));
			break;
		case NOBGM:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(51));
			break;
		case SFX:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(81));
			break;
		case NOSFX:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(84));
			break;
		case BACK:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(52));
			break;
		case PREV_PAGE:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(53));
			break;
		case NEXT_PAGE:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(54));
			break;
		case PAUSE:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(55));
			break;
		case RESET:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(56));
			break;
		case NEXT_LEVEL:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(78));
			break;
		case RESET_GAME:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(93));
			break;
		case YES:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(95));
			break;
		case NO:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(97));
			break;
		}
	}
	else
	{
		switch (iType)
		{
		case LEVEL_SELECT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(5));
			break;
		case HELP:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(14));
			break;
		case CREDIT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(15));
			break;
		case RESUME:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(30));
			break;
		case MENU:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(29));
			break;
		case PAUSE_TO_SELECT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(12));
			break;
		case EXIT:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(4));
			break;
		case BGM:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(16));
			break;
		case NOBGM:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(17));
			break;
		case SFX:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(80));
			break;
		case NOSFX:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(83));
			break;
		case BACK:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(19));
			break;
		case PREV_PAGE:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(20));
			break;
		case NEXT_PAGE:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(21));
			break;
		case PAUSE:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(26));
			break;
		case RESET:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(27));
			break;
		case NEXT_LEVEL:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(77));
			break;
		case RESET_GAME:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(92));
			break;
		case YES:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(94));
			break;
		case NO:
			Object::SetTexture(ResourceManager::GetInstance()->GetTextureById(96));
			break;
		}
	}
}

Button::~Button() {}