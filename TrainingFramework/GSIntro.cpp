#include "stdafx.h"
#include "GSIntro.h"
#include "GameStateMachine.h"
#include "ResourceManager.h"

GSIntro::GSIntro()
{
	AudioManager::GetInstance()->GetAudioById(0)->PlayMusic();
	ResourceManager::CreateInstance();
	Init("../TrainingFramework/GSIntro.txt", StateType::STATE_INTRO);
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

void GSIntro::Pause()
{
	// NOTE: blank
}

void GSIntro::Resume()
{
	// NOTE: blank
}

void GSIntro::Update(GLfloat deltatime)
{
	if (fTime < DELAY_TIME)
	{
		fTime += deltatime;
	}
	else 
	{
		GameStateMachine::GetInstance()->PushState(StateType::STATE_MENU, 0);
	}
}

void GSIntro::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSIntro::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: blank
}

void GSIntro::MouseMove(int x, int y)
{
	// NOTE: blank
}