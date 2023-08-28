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
	ReadButton();
	// Load level with the coresponding number
	Init(ilevelNumber);
	GameStateBase::GameStateBase(StateType::STATE_PLAY);

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

	test = Animation(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(31), pCamera, ResourceManager::GetInstance()->GetShaderById(1), Vector3(100, 100, 0),
		Vector3(0, 0, 0), Vector3(100, 100, 100), 7, 7, 3, 0.1);

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
	printf("GSPlay exit\n");
	SceneManager::DestroyInstance();
}

void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
	printf("GSPlay Resume\n");
}

void GSPlay::Update(GLfloat deltaTime)
{
	SceneManager::GetInstance()->Update(deltaTime);

	test.Update(deltaTime);

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
	// NOTE: this is just for testing the animation
	if (check == 0)
	{
		test.SetCurrentAction(0);
		check = 1;
	}
	else
	{
		test.SetCurrentAction(1);
		check = 0;
	}
}

void GSPlay::MouseClick(int x, int y, bool isPressed)
{
	if (isPressed)
	{
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClickReset(x, y, ilevelNumber);
		}
	}
}

void GSPlay::MouseMove(int x, int y)
{
}

void GSPlay::Draw()
{
	SceneManager::GetInstance()->Draw();
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
	test.Draw();
}
