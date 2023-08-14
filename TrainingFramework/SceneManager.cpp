#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(ResourceManager* resourceManager)
{
	FILE* filePointer = fopen("../TrainingFramework/SM.txt", "r");

	//Load data form SM.txt and initialize camera
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	camera = new Camera(Vector3(7.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), fovY, nearPlane, farPlane, speed);

	//Load data form SM.txt and initialize objects
	fscanf(filePointer, "#Objects: %d\n", &numObjects);
	objects = new Object* [numObjects];

	int id, modelId, textureId, shaderId;
	Vector3 position, rotation, scale;
	for (int i = 0; i < numObjects; i++) {
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "MODEL %d\n", &modelId);
		fscanf(filePointer, "TEXTURE %d\n", &textureId);
		fscanf(filePointer, "SHADER %d\n", &shaderId);
		fscanf(filePointer, "POSITION %f, %f, %f\n", &position.x, &position.y, &position.z);
		fscanf(filePointer, "ROTATION %f, %f, %f\n", &rotation.x, &rotation.y, &rotation.z);
		fscanf(filePointer, "SCALE %f, %f, %f\n", &scale.x, &scale.y, &scale.z);

		objects[i] = new Object(resourceManager->GetModelById(modelId), resourceManager->GetTextureById(textureId), camera, resourceManager->GetShaderById(shaderId), position, rotation, scale);
	}

	fclose(filePointer);
}

void SceneManager::Update(ESContext* esContext, float deltaTime, unsigned char keyPressed) {
	if (keyPressed & (1 << 0)) {
		camera->MoveLeft(deltaTime);
	}
	if (keyPressed & (1 << 1)) {
		camera->MoveForward(deltaTime);
	}
	if (keyPressed & (1 << 2)) {
		camera->MoveRight(deltaTime);
	}
	if (keyPressed & (1 << 3)) {
		camera->MoveBackward(deltaTime);
	}
	if (keyPressed & (1 << 4)) {
		camera->RotateLeft(deltaTime);
	}
	if (keyPressed & (1 << 5)) {
		camera->RotateUp(deltaTime);
	}
	if (keyPressed & (1 << 6)) {
		camera->RotateRight(deltaTime);
	}
	if (keyPressed & (1 << 7)) {
		camera->RotateDown(deltaTime);
	}
}

void SceneManager::Draw() {
	for (int i = 0; i < numObjects; i++) {
		objects[i]->Draw();
	}
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < numObjects; i++) {
		delete objects[i];
	}
	delete objects;

	delete camera;
}