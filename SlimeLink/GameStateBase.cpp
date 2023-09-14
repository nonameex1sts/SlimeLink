#include "stdafx.h"
#include "GameStateBase.h"
#include "GSMenu.h"
#include "GSHelp.h"
#include "GSCredit.h"
#include "GSLevelSelect.h"
#include "GSPlay.h"
#include "GSPause.h"

GameStateBase::GameStateBase()
{
}

GameStateBase::~GameStateBase()
{
}

void GameStateBase::Init(char* file, StateType e_type)
{
	FILE* filePointer;

	try
	{
		filePointer = fopen(file, "r");
	}
	catch (...)
	{
		printf("Cannot open state initiate file: %s\n", file);
	}

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
	pButtons = (Button**)malloc(sizeof(Button*) * inumButtons);

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

		pButtons[i] = (Button*)malloc(sizeof(Button));
		*(pButtons[i]) = Button(ResourceManager::GetInstance()->GetModelById(modelId), ResourceManager::GetInstance()->GetTextureById(textureId), pCamera,
			ResourceManager::GetInstance()->GetShaderById(shaderId), position, rotation, scale, buttonType, isActive);
	}

	// NOTE: read pictures
	fscanf(filePointer, "#Pictures: %d\n", &inumPics);
	pPictures = (Picture**)malloc(sizeof(Picture*) * inumPics);

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

		pPictures[i] = (Picture*)malloc(sizeof(Picture));
		*(pPictures[i]) = Picture(ResourceManager::GetInstance()->GetModelById(modelId), ResourceManager::GetInstance()->GetTextureById(textureId), pCamera,
			ResourceManager::GetInstance()->GetShaderById(shaderId), position, rotation, scale, isActive);
	}

	fclose(filePointer);

	this->e_type = e_type;
}

void GameStateBase::Exit()
{
	// NOTE: Delete camera
	delete pCamera;

	// NOTE: Delete button
	for (int i = 0; i < inumPics; i++) {
		free(pPictures[i]);
	}
	free(pPictures);
	
	// NOTE: Delete picture
	for (int i = 0; i < inumButtons; i++) {
		free(pButtons[i]);
	}
	free(pButtons);
}

void GameStateBase::Pause()
{
}

void GameStateBase::Resume()
{
}

void GameStateBase::Update(GLfloat deltatime)
{
}

void GameStateBase::Key(int iKeyPressed)
{
}

void GameStateBase::MouseClick(int x, int y, bool isPressed)
{
}

void GameStateBase::MouseMove(int x, int y)
{
}

// Draw pictures -> buttons
void GameStateBase::Draw()
{
	for (int i = 0; i < inumPics; i++)
	{
		if (pPictures[i]->getActive())
		{
			pPictures[i]->Draw();
		}
	}

	// BGM and SFX button switch between up and down status
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
}

StateType GameStateBase::GetStateType()
{
	return e_type;
}

GameStateBase* GameStateBase::CreateState(StateType type)
{
	GameStateBase* res;

	switch (type) {
	case StateType::STATE_MENU:
		res = new GSMenu;
		break;
	case StateType::STATE_LEVEL_SELECT:
		res = new GSLevelSelect;
		break;
	case StateType::STATE_HELP:
		res = new GSHelp;
		break;
	case StateType::STATE_CREDIT:
		res = new GSCredit;
		break;
	case StateType::STATE_PAUSE:
		res = new GSPause;
		break;
	default:
		res = nullptr;
		break;
	}

	return res;
}

GameStateBase* GameStateBase::CreateStatePlay(int ilevelNumber)
{
	GameStateBase* res;
	res = new GSPlay(ilevelNumber);
	return res;
}
