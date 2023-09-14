#include "stdafx.h"
#include "SelectLevelButton.h"
#include "AudioManager.h"
#include "GameStateMachine.h"

SelectLevelButton::SelectLevelButton() 
{
}

SelectLevelButton::~SelectLevelButton() 
{
}

SelectLevelButton::SelectLevelButton(Model* pModel, Texture* pTexture, Camera* pCamera, Shaders* pShader, Vector3 position, Vector3 rotation, Vector3 scale, int iType, int isActive)
	:Button(pModel, pTexture,  pCamera, pShader, position, rotation, scale, iType, isActive) 
{
}

void SelectLevelButton::SetCurrentLevel(int iCurrentLevel)
{
	this->iCurrentLevel = iCurrentLevel;
}

// Init state play of that level
void SelectLevelButton::MouseClick(int x, int y)
{
	if ((position.x - scale.x / 2) < x && x < (position.x + scale.x / 2) && (position.y - scale.y / 2) < y && y < (position.y + scale.y / 2))
	{
		AudioManager::GetInstance()->GetAudioById(2)->PlayMusic();
		if (iCurrentLevel < NUM_OF_LEVELS)
		{
			//Initiate level based on iCurrentLevel
			AudioManager::GetInstance()->GetAudioById(6)->PlayMusic();
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, iCurrentLevel);
		}
	}
}