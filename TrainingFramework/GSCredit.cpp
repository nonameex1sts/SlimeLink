#include "stdafx.h"
#include "GSCredit.h"

GSCredit::GSCredit()
{
	GameStateBase::GameStateBase(StateType::STATE_CREDIT);
	Init();
}

GSCredit::~GSCredit()
{
	Exit();
}

void GSCredit::Init()
{
	// NOTE: read camera
	FILE* filePointer = fopen("../TrainingFramework/GSCredit.txt", "r");
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), fovY, nearPlane, farPlane, speed);

	// NOTE: read buttons
	fscanf(filePointer, "#Buttons: %d\n", &inumButtons);
	pButtons = new Button * [inumButtons];
	int id, modelId, textureId, shaderId, buttonType, isActive;
	Vector3 position, rotation, scale;
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


	printf("GSCredit init\n");
}

void GSCredit::Exit()
{
	// NOTE: Delete camera
	delete pCamera;
	// NOTE: Delete button
	for (int i = 0; i < inumButtons; i++) {
		delete pButtons[i];
	}
	delete pButtons;
	printf("GSCredit exit\n");
}

void GSCredit::Pause()
{
	// NOTE: blank
}

void GSCredit::Resume()
{
	// NOTE: blank
}

void GSCredit::Update(GLfloat deltatime)
{
	//NOTE: blank
}

void GSCredit::Key(int iKeyPressed)
{
	// NOTE: blank
}

void GSCredit::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check back button if it got click or not
	if (isPressed)
	{
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y);
		}
	}
}

void GSCredit::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSCredit::Draw()
{
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}
}