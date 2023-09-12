#include "stdafx.h"
#include "GSMenu.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"
#include "GameStateBase.h"

GSMenu::GSMenu()
{
	Init("../TrainingFramework/GSMenu.txt", StateType::STATE_MENU);
	AudioManager::GetInstance()->GetAudioById(0)->PlayMusic();
	AudioManager::GetInstance()->GetAudioById(1)->StopMusic();
	slime = new Animation(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(12), pCamera,
		ResourceManager::GetInstance()->GetShaderById(1), Vector3(674.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(45.0f, 45.0f, 0.0f), 6, 1, 0, 0.1);
}

GSMenu::~GSMenu()
{
	Exit();
	delete slime;
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
	slime->Update(deltatime);
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
			pButtons[i]->MouseClick(x, y, isPressed);

			if (pButtons == nullptr)
			{
				break;
			}
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

void GSMenu::Draw()
{
	for (int i = 0; i < inumPics; i++)
	{
		if (pPictures[i]->getActive())
		{
			pPictures[i]->Draw();
		}
	}
	// BGM and SFX button switch to on and off
	for (int i = 0; i < inumButtons; i++)
	{
		if (AudioManager::GetInstance()->getBGMStatus())
		{
			if (pButtons[i]->getType() == 4) pButtons[i]->setActive(true);
			if (pButtons[i]->getType() == 5) pButtons[i]->setActive(false);
		}
		else
		{
			if (pButtons[i]->getType() == 5) pButtons[i]->setActive(true);
			if (pButtons[i]->getType() == 4) pButtons[i]->setActive(false);
		}
		if (AudioManager::GetInstance()->getSFXStatus())
		{
			if (pButtons[i]->getType() == 16) pButtons[i]->setActive(true);
			if (pButtons[i]->getType() == 17) pButtons[i]->setActive(false);
		}
		else
		{
			if (pButtons[i]->getType() == 17) pButtons[i]->setActive(true);
			if (pButtons[i]->getType() == 16) pButtons[i]->setActive(false);
		}
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
	slime->Draw();
}