#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"

SceneManager* SceneManager::ms_pInstance = nullptr;

SceneManager::SceneManager()
{
	FILE* filePointer = fopen("../TrainingFramework/SM.txt", "r");
	ResourceManager::CreateInstance();
	//Load data form SM.txt and initialize camera
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), fovY, nearPlane, farPlane, speed);

	//Load data form SM.txt and initialize objects
	fscanf(filePointer, "#Objects: %d\n", &inumObjects);
	pObjects = new Object* [inumObjects];

	int id, modelId, textureId, shaderId;
	Vector3 position, rotation, scale;
	for (int i = 0; i < inumObjects; i++) 
	{
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "MODEL %d\n", &modelId);
		fscanf(filePointer, "TEXTURE %d\n", &textureId);
		fscanf(filePointer, "SHADER %d\n", &shaderId);
		fscanf(filePointer, "POSITION %f, %f, %f\n", &position.x, &position.y, &position.z);
		fscanf(filePointer, "ROTATION %f, %f, %f\n", &rotation.x, &rotation.y, &rotation.z);
		fscanf(filePointer, "SCALE %f, %f, %f\n", &scale.x, &scale.y, &scale.z);

		pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(modelId), ResourceManager::GetInstance()->GetTextureById(textureId), pCamera, 
			ResourceManager::GetInstance()->GetShaderById(shaderId), position, rotation, scale);
	}

	fclose(filePointer);
}

void SceneManager::Update(ESContext* esContext, float deltaTime, unsigned char keyPressed)
{
	if (keyPressed & (1 << 0)) 
	{
		pCamera->MoveLeft(deltaTime);
	}
	if (keyPressed & (1 << 1)) 
	{
		pCamera->MoveForward(deltaTime);
	}
	if (keyPressed & (1 << 2)) 
	{
		pCamera->MoveRight(deltaTime);
	}
	if (keyPressed & (1 << 3)) 
	{
		pCamera->MoveBackward(deltaTime);
	}
	if (keyPressed & (1 << 4)) 
	{
		pCamera->RotateLeft(deltaTime);
	}
	if (keyPressed & (1 << 5)) 
	{
		pCamera->RotateUp(deltaTime);
	}
	if (keyPressed & (1 << 6))
	{
		pCamera->RotateRight(deltaTime);
	}
	if (keyPressed & (1 << 7)) 
	{
		pCamera->RotateDown(deltaTime);
	}
}

void SceneManager::Draw()
{
	for (int i = 0; i < inumObjects; i++) 
	{
		pObjects[i]->Draw();
	}
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < inumObjects; i++) 
	{
		delete pObjects[i];
	}
	delete pObjects;

	delete pCamera;
}