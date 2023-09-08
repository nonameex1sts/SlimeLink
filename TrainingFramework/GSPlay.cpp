#include "stdafx.h"
#include "GSPlay.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameStateMachine.h"
#include "AudioManager.h"

GSPlay::GSPlay(int ilevelNumber)
{
	AudioManager::GetInstance()->GetAudioById(0)->StopMusic();
	this->ilevelNumber = ilevelNumber;

	// Load level with the coresponding number
	Init(ilevelNumber);

	//Generate star number on trophy based on star of the level
	int* iStar = SceneManager::GetInstance()->GetStarIndex();
	pPictures[1]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[0] / 10 + 17));
	pPictures[2]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[0] % 10 + 17));

	pPictures[4]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[1] / 10 + 17));
	pPictures[5]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[1] % 10 + 17));

	pPictures[7]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[2] / 10 + 17));
	pPictures[8]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[2] % 10 + 17));
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
	GameStateBase::Init("../TrainingFramework/GSPlay.txt", StateType::STATE_PLAY);

	SceneManager::CreateInstance(ilevelNumber);
}

void GSPlay::Exit()
{
	SceneManager::DestroyInstance();

	GameStateBase::Exit();
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

	//If the game has ended
	if (SceneManager::GetInstance()->GetEndedStatus()) {

		int iNumOfStarNotActive = 3 - SceneManager::GetInstance()->GetNumberOfStar();

		//Disable Pause and activate other buttons
		for (int i = 0; i < inumButtons; i++)
		{
			if (pButtons[i]->getType() == PAUSE) 
			{
				pButtons[i]->setActive(false);
			}
			else
			{
				pButtons[i]->setActive(true);
			}
		}

		//Deactivate Next Level button if this is the last level
		if(ilevelNumber == NUM_OF_LEVELS - 1)
		{
			for (int i = 0; i < inumButtons; i++)
			{
				if (pButtons[i]->getType() == NEXT_LEVEL)
				{
					pButtons[i]->setActive(false);
				}
			}
		}

		//Activate all picture
		for (int i = 0; i < inumPics - iNumOfStarNotActive; i++)
		{
			pPictures[i]->setActive(true);
		}
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
		case KEY_RESET:
			SceneManager::DestroyInstance();
			SceneManager::CreateInstance(ilevelNumber);
			ResetGameScreen();
			break;
		case KEY_PAUSE:
			GameStateMachine::GetInstance()->PushState(StateType::STATE_PAUSE, 1);
			break;
		default:
			break;
		}

		SceneManager::GetInstance()->Key(keyPressed);

		fcheckKeyTime = 0.0f;
	}

	//Set the picture of number of moves based on number of moves in SceneManager
	pPictures[10]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() / 100 + 17));
	pPictures[11]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() % 100 / 10 + 17));
	pPictures[12]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() % 100 % 10 + 17));

	//When a star is lost, convert that picture to gray
	int iNumOfStarLost = 3 - SceneManager::GetInstance()->GetNumberOfStar();
	for (int i = 6; i > 6 - 3 * iNumOfStarLost; i -= 3) 
	{
		pPictures[i]->SetTexture(ResourceManager::GetInstance()->GetTextureById(91));
	}
}

void GSPlay::MouseClick(int x, int y, bool isPressed)
{
	bool* isReset = new bool;
	*isReset = false;

	if (isPressed)
	{
		for (int i = 0; i < inumButtons; i++)
		{
			if (pButtons[i]->getActive())
			{
				pButtons[i]->MouseClickReset(x, y, ilevelNumber, isReset);
			}

			if (pButtons == nullptr)
			{
				break;
			}
		}
	}

	//If the reset button is pressed after the game has ended
	if (*isReset) {
		ResetGameScreen();
	}

	delete isReset;
}

void GSPlay::ResetGameScreen()
{
	//Reset set all number picture
	pPictures[10]->SetTexture(ResourceManager::GetInstance()->GetTextureById(17));
	pPictures[11]->SetTexture(ResourceManager::GetInstance()->GetTextureById(17));
	pPictures[12]->SetTexture(ResourceManager::GetInstance()->GetTextureById(17));

	for (int i = 6; i >= 0; i -= 3)
	{
		pPictures[i]->SetTexture(ResourceManager::GetInstance()->GetTextureById(16));
	}

	//Activate Pause, Reset and deactivate other buttons
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getType() == PAUSE || pButtons[i]->getType() == RESET)
		{
			pButtons[i]->setActive(true);
		}
		else
		{
			pButtons[i]->setActive(false);
		}
	}

	//Deactivate game ending picture
	for (int i = 13; i < inumPics; i++)
	{
		pPictures[i]->setActive(false);
	}
}

void GSPlay::MouseMove(int x, int y)
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->MouseMove(x, y);
	}
}

void GSPlay::Draw()
{
	SceneManager::GetInstance()->Draw();

	//Draw under opacity
	for (int i = 0; i < inumButtons - 3; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}


	for (int i = 0; i < inumPics; i++) 
	{
		if (pPictures[i]->getActive()) 
		{
			pPictures[i]->Draw();
		}
	}

	//Draw above opacity
	for (int i = inumButtons - 3; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
}
