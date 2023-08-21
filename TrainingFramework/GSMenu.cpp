#include "stdafx.h"
#include "GSMenu.h"
#include "GameStateMachine.h"
#include "ElementManager.h"

GSMenu::GSMenu()
{
	GameStateBase::GameStateBase(StateType::STATE_MENU);
	Init();
}

GSMenu::~GSMenu()
{
	Exit();
}

void GSMenu::Init()
{
	// NOTE: Load image
	// NOTE: Load button
	ElementManager::CreateInstance();

	FILE* filePointer = fopen("../TrainingFramework/GSMenu.txt", "r");
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), fovY, nearPlane, farPlane, speed);


	/*Vector3 position = Vector3(560.0f, 480.0f, 0.0f);
	Vector3 position2 = Vector3(620.0f, 480.0f, 0.0f);
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(80.0f, 80.0f, 1.0f);
	buttonTest = new Button * [2];
	buttonTest[0] = new Button(ElementManager::GetInstance()->GetModelById(0), ElementManager::GetInstance()->GetTextureById(0), pCamera,
				ElementManager::GetInstance()->GetShaderById(0), position, rotation, scale);
	buttonTest[1] = new Button(ElementManager::GetInstance()->GetModelById(0), ElementManager::GetInstance()->GetTextureById(0), pCamera,
		ElementManager::GetInstance()->GetShaderById(0), position2, rotation, scale);*/

	fscanf(filePointer, "#Buttons: %d\n", &inumButtons);
	pButtons = new Button*[inumButtons];
	int id, modelId, textureId, shaderId;
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
		pButtons[i] = new Button(ElementManager::GetInstance()->GetModelById(modelId), ElementManager::GetInstance()->GetTextureById(textureId), pCamera,
			ElementManager::GetInstance()->GetShaderById(shaderId), position, rotation, scale);
	}
	fclose(filePointer);


	printf("GSMenu init\n");
}

void GSMenu::Exit()
{
	// NOTE: Delete button
	printf("GSMenu exit\n");
}

void GSMenu::Pause()
{
	// NOTE: blank
	printf("GSMenu pause\n");
}

void GSMenu::Resume()
{
	printf("GSMenu resume\n");
	// NOTE: blank
}

void GSMenu::Update(GLfloat deltatime)
{
}

void GSMenu::Key(int iKeyPressed)
{
	if (iKeyPressed == KEY_MOVE_RIGHT) {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY, 0);
	}
}

void GSMenu::MouseClick(int x, int y, bool isPressed)
{
	if (isPressed)
	{
		for (int i = 0; i < static_cast<int>(MenuButtonType::NUMBER_OF_BUTTONS); i++) 
		{
			// NOTE:: Check if that button is clicked
		}
	}
}

void GSMenu::MouseMove(int x, int y)
{
	// NOTE: blank
}

void GSMenu::Draw()
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->Draw();
	}
	/*for (int i = 0; i < 2; i++) {
		buttonTest[i]->Draw();
	}*/
	// NOTE: Draw image
	// NOTE: Draw button
}