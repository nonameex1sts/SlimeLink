#include "stdafx.h"
#include "GSPlay.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameStateMachine.h"
#include "AudioManager.h"

GSPlay::GSPlay(int ilevelNumber)
{
	AudioManager::GetInstance()->GetAudioById(0)->StopMusic();
	printf("GSPlay init\n");
	this->ilevelNumber = ilevelNumber;
	GameStateBase::GameStateBase(StateType::STATE_PLAY);

	// Load level with the coresponding number
	Init(ilevelNumber);
}

GSPlay::~GSPlay()
{
	Exit();
}

int GSPlay::GetLevelNumber()
{
	return ilevelNumber;
}

void GSPlay::Init(int ilevelNumber)
{
	//Load level<ilevelNumber>

	SceneManager::CreateInstance(ilevelNumber);
}

void GSPlay::Exit()
{
	printf("GSPlay exit\n");
	SceneManager::DestroyInstance();
}

void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}

void GSPlay::Update(GLfloat deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);

	if (fcheckKeyTime <= DELAY_KEY_TIME + DELAY_STATE_PLAYER) {
		fcheckKeyTime += FRAME_TIME;
	}
}

void GSPlay::Key(int iKeyPressed)
{
	unsigned char keyPressed = 0;

	//0123 in bit mask is for left, up, right, down movement
	if (fcheckKeyTime > (DELAY_KEY_TIME + DELAY_STATE_PLAYER))
	{
		switch (iKeyPressed)
		{
		case KEY_MOVE_LEFT:
			keyPressed |= 1 << 0;
			break;
		case KEY_MOVE_FORWARD:
			keyPressed |= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			keyPressed |= 1 << 2;
			break;
		case KEY_MOVE_BACKWARD:
			keyPressed |= 1 << 3;
			break;
		case KEY_LEFT:
			keyPressed |= 1 << 0;
			break;
		case KEY_UP:
			keyPressed |= 1 << 1;
			break;
		case KEY_RIGHT:
			keyPressed |= 1 << 2;
			break;
		case KEY_DOWN:
			keyPressed |= 1 << 3;
			break;
		default:
			break;
		}

		SceneManager::GetInstance()->Key(keyPressed);

		fcheckKeyTime = 0.0f;
	}
}

void GSPlay::MouseClick(int x, int y, bool isPressed)
{
	if (isPressed)
	{
		GameStateMachine::GetInstance()->PopState();
	}
}

void GSPlay::MouseMove(int x, int y)
{
}

void GSPlay::Draw()
{
	SceneManager::GetInstance()->Draw();
}
