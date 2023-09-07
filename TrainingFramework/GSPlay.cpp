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
	ReadButton();
	// Load level with the coresponding number
	Init(ilevelNumber);

	//Generate star number on trophy based on star of the level
	int* iStar = SceneManager::GetInstance()->GetStarIndex();
	pPictures[1]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[0] / 10 + 33));
	pPictures[2]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[0] % 10 + 33));

	pPictures[4]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[1] / 10 + 33));
	pPictures[5]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[1] % 10 + 33));

	pPictures[7]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[2] / 10 + 33));
	pPictures[8]->SetTexture(ResourceManager::GetInstance()->GetTextureById(iStar[2] % 10 + 33));
}

GSPlay::~GSPlay()
{
	Exit();
}

int GSPlay::GetLevelNumber()
{
	return ilevelNumber;
}

void GSPlay::ReadButton()
{
	FILE* filePointer = fopen("../TrainingFramework/GSPlay.txt", "r");
	// NOTE: read camera
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), fovY, nearPlane, farPlane, speed);

	int id, modelId, textureId, shaderId, buttonType, isActive;
	Vector3 position, rotation, scale;
	// NOTE: read buttons
	fscanf(filePointer, "#Buttons: %d\n", &inumButtons);
	pButtons = new Button * [inumButtons];
	for (int i = 0; i < inumButtons; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "MODEL %d\n", &modelId);
		fscanf(filePointer, "TEXTURE %d\n", &textureId);
		fscanf(filePointer, "SHADER %d\n", &shaderId);
		fscanf(filePointer, "POSITION %f, %f, %f\n", &position.x, &position.y, &position.z);
		fscanf(filePointer, "ROTATION %f, %f, %f\n", &rotation.x, &rotation.y, &rotation.z);
		fscanf(filePointer, "SCALE %f, %f, %f\n", &scale.x, &scale.y, &scale.z);
		fscanf(filePointer, "TYPE %d\n", &buttonType);
		fscanf(filePointer, "ACTIVE %d\n", &isActive);
		pButtons[i] = new Button(ResourceManager::GetInstance()->GetModelById(modelId), ResourceManager::GetInstance()->GetTextureById(textureId), pCamera,
			ResourceManager::GetInstance()->GetShaderById(shaderId), position, rotation, scale, buttonType, isActive);
	}

	// NOTE: read picture
	fscanf(filePointer, "#Pictures: %d\n", &inumPics);
	pPictures = new Picture * [inumPics];
	for (int i = 0; i < inumPics; i++)
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "MODEL %d\n", &modelId);
		fscanf(filePointer, "TEXTURE %d\n", &textureId);
		fscanf(filePointer, "SHADER %d\n", &shaderId);
		fscanf(filePointer, "POSITION %f, %f, %f\n", &position.x, &position.y, &position.z);
		fscanf(filePointer, "ROTATION %f, %f, %f\n", &rotation.x, &rotation.y, &rotation.z);
		fscanf(filePointer, "SCALE %f, %f, %f\n", &scale.x, &scale.y, &scale.z);
		fscanf(filePointer, "ACTIVE %d\n", &isActive);
		pPictures[i] = new Picture(ResourceManager::GetInstance()->GetModelById(modelId), ResourceManager::GetInstance()->GetTextureById(textureId), pCamera,
			ResourceManager::GetInstance()->GetShaderById(shaderId), position, rotation, scale, isActive);
	}

	fclose(filePointer);
}

void GSPlay::Init(int ilevelNumber)
{
	//Load level<ilevelNumber>

	SceneManager::CreateInstance(ilevelNumber);
}

void GSPlay::Exit()
{
	delete pCamera;
	// NOTE: Delete button
	for (int i = 0; i < inumButtons; i++) {
		delete pButtons[i];
	}
	delete pButtons;

	// NOTE: Delete picture
	for (int i = 0; i < inumPics; i++) {
		delete pPictures[i];
	}
	delete pPictures;
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
		if(ilevelNumber == NUM_OF_LEVELS)
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
		default:
			break;
		}

		SceneManager::GetInstance()->Key(keyPressed);

		fcheckKeyTime = 0.0f;
	}

	//Set the picture of number of moves based on number of moves in SceneManager
	pPictures[10]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() / 100 + 33));
	pPictures[11]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() % 100 / 10 + 33));
	pPictures[12]->SetTexture(ResourceManager::GetInstance()->GetTextureById(SceneManager::GetInstance()->GetNumberOfMoves() % 100 % 10 + 33));

	//When a star is lost, convert that picture to gray
	int iNumOfStarLost = 3 - SceneManager::GetInstance()->GetNumberOfStar();
	for (int i = 6; i > 6 - 3 * iNumOfStarLost; i -= 3) 
	{
		pPictures[i]->SetTexture(ResourceManager::GetInstance()->GetTextureById(86));
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
		//Reset set all number picture
		pPictures[10]->SetTexture(ResourceManager::GetInstance()->GetTextureById(33));
		pPictures[11]->SetTexture(ResourceManager::GetInstance()->GetTextureById(33));
		pPictures[12]->SetTexture(ResourceManager::GetInstance()->GetTextureById(33));

		for (int i = 6; i >= 0; i -= 3)
		{
			pPictures[i]->SetTexture(ResourceManager::GetInstance()->GetTextureById(43));
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

	delete isReset;
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
