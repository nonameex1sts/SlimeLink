#include "stdafx.h"
#include "GSLevelSelect.h"
#include "AudioManager.h"

GSLevelSelect::GSLevelSelect()
{
	GameStateBase::GameStateBase(StateType::STATE_LEVEL_SELECT);
	Init();
}

GSLevelSelect::~GSLevelSelect()
{
	Exit();
}

void GSLevelSelect::Init()
{
	// NOTE: read camera
	FILE* filePointer = fopen("../TrainingFramework/GSLevelSelect.txt", "r");
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

	Vector3 levelPos = Vector3(200.0f, 180.0f, 0.0f);
	Vector3 levelRotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 levelScale = Vector3(150.0f, 150.0f, 1.0f);
	Vector3 levelWidthEach = Vector3(450.0f, 0.0f, 0.0f);
	Vector3 levelHeightEach = Vector3(0.0f, 350.0f, 0.0f);

	pSelectLevel = new SelectLevelButton * [6];
	for (int i = 0; i < iRowPerPage; i++) 
	{
		for (int j = 0; j < (iLevelPerPage / iRowPerPage); j++) 
		{
			pSelectLevel[i*3 + j] = new SelectLevelButton(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), levelPos + levelHeightEach * i + levelWidthEach * j, levelRotation, levelScale, 0, 1);
			pSelectLevel[i * 3 + j]->SetCurrentLevel(i * 3 + j + 1);
		}
	}

	printf("GSLevelSelect init\n");
}

void GSLevelSelect::Exit()
{
	// NOTE: Delete camera
	delete pCamera;
	// NOTE: Delete button
	for (int i = 0; i < inumPics; i++) {
		delete pPictures[i];
	}
	delete pPictures;
	for (int i = 0; i < iLevelPerPage; i++) {
		delete pSelectLevel[i];
	}
	delete pSelectLevel;
	for (int i = 0; i < inumButtons; i++) {
		delete pButtons[i];
	}
	delete pButtons;
	printf("GSLevelSelect exit\n");
}

void GSLevelSelect::Pause()
{
	printf("GSLevelSelect pause\n");
	// NOTE: blank
}

void GSLevelSelect::Resume()
{
	AudioManager::GetInstance()->GetAudioById(0)->PlayMusic();
	printf("GSLevelSelect resume\n");
	// NOTE: blank
}

void GSLevelSelect::Update(GLfloat deltatime)
{
}

void GSLevelSelect::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSLevelSelect::UpdateLevel()
{
	for (int i = 0; i < iLevelPerPage; i++)
	{
		pSelectLevel[i]->SetCurrentLevel(iCurrentPage * iLevelPerPage + i + 1);
	}
}

void GSLevelSelect::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check back button if it got click or not
	if (isPressed)
	{
		for (int i = 0; i < iLevelPerPage; i++)
		{
			pSelectLevel[i]->MouseClick(x, y);
		}
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y, &iCurrentPage, iSumPage);
		}
		UpdateLevel();
		printf("%d\n", iCurrentPage);
	}
}

void GSLevelSelect::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSLevelSelect::Draw()
{
	for (int i = 0; i < inumPics; i++)
	{
		if (pPictures[i]->getActive())
		{
			pPictures[i]->Draw();
		}
	}
	for (int i = 0; i < iLevelPerPage; i++) {
		if (pSelectLevel[i]->getActive())
		{
			pSelectLevel[i]->Draw();
		}
	}
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
}