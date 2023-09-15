#include "stdafx.h"
#include "GSIntro.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"

GSIntro::GSIntro()
{
	AudioManager::GetInstance()->GetAudioById(1)->PlayMusic();
	ResourceManager::CreateInstance();
	Init("../Resources/StateData/GSIntro.txt", StateType::STATE_INTRO);
}

GSIntro::~GSIntro()
{
	Exit();
}

void GSIntro::Exit()
{
	// NOTE: Delete image
	GameStateBase::Exit();

	ResourceManager::DestroyInstance();
}

void GSIntro::Update(GLfloat deltatime)
{
	//The storyline picture moves up according to deltatime
	if (fTime < DELAY_TIME)
	{
		fTime += deltatime;
		pPictures[0]->SetPosition(Vector3(0.0f, -1600.0f, 0.0f) / DELAY_TIME * deltatime);
		pPictures[1]->SetPosition(Vector3(0.0f, -1600.0f, 0.0f) / DELAY_TIME * deltatime);
	}
	else 
	{
		GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU, 0);
	}
}

void GSIntro::MouseClick(int x, int y, bool isPressed)
{
	if (isPressed)
	{
		GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU, 0);
	}
}