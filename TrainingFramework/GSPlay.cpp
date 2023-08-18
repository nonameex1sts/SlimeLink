#include "stdafx.h"
#include "GSPlay.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameStateMachine.h"

GSPlay::GSPlay(int ilevelNumber)
{
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

	SceneManager::CreateInstance();
}

void GSPlay::Exit()
{
	printf("GSPlay exit\n");
	ResourceManager::DestroyInstance();
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
	SceneManager::GetInstance()->Update(deltaTime, keyPressed);
	keyPressed = 0;

	if (fcheckKeyTime <= DELAY_KEY_TIME) {
		fcheckKeyTime += deltaTime;
	}
}

void GSPlay::Key(int iKeyPressed)
{
	if (fcheckKeyTime > DELAY_KEY_TIME)
	{
		switch (iKeyPressed)
		{
		case KEY_MOVE_LEFT:
			GameStateMachine::GetInstance()->PopState();
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
			keyPressed |= 1 << 4;
			break;
		case KEY_UP:
			keyPressed |= 1 << 5;
			break;
		case KEY_RIGHT:
			keyPressed |= 1 << 6;
			break;
		case KEY_DOWN:
			keyPressed |= 1 << 7;
			break;
		default:
			break;
		}

		fcheckKeyTime = 0.0f;
	}
}

void GSPlay::MouseClick(int x, int y, bool isPressed)
{
	if (isPressed)
	{
		printf("Click: %d %d\n", x, y);
	}
}

void GSPlay::MouseMove(int x, int y)
{
}

void GSPlay::Draw()
{
	SceneManager::GetInstance()->Draw();
}
