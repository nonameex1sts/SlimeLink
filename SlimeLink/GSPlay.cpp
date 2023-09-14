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
	int* iDigitOfEachStar = new int[3];
	iNumOfDigit = 0;

	//Calculate the number of digit
	for (int i = 0; i < 3; i++) {
		if (iStar[i] / 100 > 0)
		{
			iNumOfDigit += 3;
			iDigitOfEachStar[i] = 3;
		}
		else if (iStar[i] / 10 > 0)
		{
			iNumOfDigit += 2;
			iDigitOfEachStar[i] = 2;
		}
		else
		{
			iNumOfDigit += 1;
			iDigitOfEachStar[i] = 1;
		}
	}

	pDigit = (Picture**)malloc(sizeof(Picture*) * iNumOfDigit);
	for (int i = 0; i < iNumOfDigit; i++) {
		pDigit[i] = (Picture*)malloc(sizeof(Picture));
	}

	//Attributes of each digit
	Vector3 digitScale = Vector3(20.0f, 20.0f, 1.0f);
	Vector3 digitRotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 trophyPosition = Vector3(40.0f, 30.0f, 0.0f);

	Vector3 twoDigitOffset = Vector3(-9.0f, 0.0f, 0.0f);
	Vector3 threeDigitOffset = Vector3(-17.0f, 0.0f, 0.0f);
	Vector3 digitSpacing = Vector3(15.0f, 0.0f, 0.0f);

	int digitCounter = 0;

	//Instantiate each digit based on the score of each trophy
	for(int i=0; i<3; i++)
	{
		if (iDigitOfEachStar[i] == 3)
		{
			*(pDigit[digitCounter + 0]) = Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(iStar[i] / 100 + 17), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), trophyPosition + threeDigitOffset, digitRotation, digitScale, 1);

			*(pDigit[digitCounter + 1]) = Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(iStar[i] % 100 / 10 + 17), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), trophyPosition + threeDigitOffset + digitSpacing, digitRotation, digitScale, 1);

			*(pDigit[digitCounter + 2]) = Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(iStar[i] % 100 % 10 + 17), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), trophyPosition + threeDigitOffset + digitSpacing * 2, digitRotation, digitScale, 1);
		}
		else if (iDigitOfEachStar[i] == 2)
		{
			*(pDigit[digitCounter + 0]) = Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(iStar[i] / 10 + 17), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), trophyPosition + twoDigitOffset, digitRotation, digitScale, 1);

			*(pDigit[digitCounter + 1]) = Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(iStar[i] % 10 + 17), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), trophyPosition + twoDigitOffset + digitSpacing, digitRotation, digitScale, 1);
		}
		else
		{
			*(pDigit[digitCounter + 0]) = Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(iStar[i] + 17), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), trophyPosition, digitRotation, digitScale, 1);
		}

		digitCounter += iDigitOfEachStar[i];

		trophyPosition = trophyPosition + Vector3(80.0f, 0.0f, 0.0f);
	}

	delete iDigitOfEachStar;
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
	GameStateBase::Init("../SlimeLink/GSPlay.txt", StateType::STATE_PLAY);

	SceneManager::CreateInstance(ilevelNumber);
}

void GSPlay::Exit()
{
	SceneManager::DestroyInstance();

	for (int i = 0; i < iNumOfDigit; i++) {
		free(pDigit[i]);
	}
	free(pDigit);

	GameStateBase::Exit();
}

void GSPlay::Update(GLfloat deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);

	//The key only register after DELAY_KEY_TIME + DELAY_STATE_PLAYER, fcheckKeyTime to check that according to deltaTime
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
	pPictures[4]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() / 100 + 17));
	pPictures[5]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() % 100 / 10 + 17));
	pPictures[6]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() % 100 % 10 + 17));

	//When a star is lost, convert that picture to gray
	int iNumOfStarLost = 3 - SceneManager::GetInstance()->GetNumberOfStar();
	for (int i = 2; i > 2 - iNumOfStarLost; i --) 
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
			if (pButtons[i] == nullptr || inumButtons > 4 || inumButtons < 0)
			{
				break;
			}

			if (pButtons[i]->getActive())
			{
				pButtons[i]->MouseClickReset(x, y, ilevelNumber, isReset);
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
	pPictures[4]->SetTexture(ResourceManager::GetInstance()->GetTextureById(17));
	pPictures[5]->SetTexture(ResourceManager::GetInstance()->GetTextureById(17));
	pPictures[6]->SetTexture(ResourceManager::GetInstance()->GetTextureById(17));

	for (int i = 2; i >= 0; i --)
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
	for (int i = 7; i < inumPics; i++)
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

	for (int i = 0; i < inumPics -5; i++) 
	{
		if (pPictures[i]->getActive()) 
		{
			pPictures[i]->Draw();
		}
	}

	for (int i = 0; i < iNumOfDigit; i++)
	{
		pDigit[i]->Draw();
	}


	//Draw above opacity
	for (int i = inumPics - 5; i < inumPics; i++)
	{
		if (pPictures[i]->getActive())
		{
			pPictures[i]->Draw();
		}
	}

	for (int i = inumButtons - 3; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
}
