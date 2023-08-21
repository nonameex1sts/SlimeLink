#include "stdafx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>

SceneManager* SceneManager::ms_pInstance = nullptr;

SceneManager::SceneManager(int ilevelNumber) {
	ResourceManager::CreateInstance();

	//Read map file
	std::string link = "../Resources/Level/map" + std::to_string(ilevelNumber) + ".txt";
	FILE* filePointer = fopen(link.c_str(), "r");

	//Initialize camera
	float fovY, nearPlane, farPlane, speed;
	fscanf(filePointer, "#CAMERA\n");
	fscanf(filePointer, "NEAR %f\n", &nearPlane);
	fscanf(filePointer, "FAR %f\n", &farPlane);
	fscanf(filePointer, "FOV %f\n", &fovY);
	fscanf(filePointer, "SPEED %f\n", &speed);
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), fovY, nearPlane, farPlane, speed);

	//Width height of the map
	fscanf(filePointer, "Width: %d\n", &iWidth);
	fscanf(filePointer, "Height: %d\n", &iHeight);

	p_imapType = new int* [iHeight];
	for (int i = 0; i < iHeight; i++) {
		p_imapType[i] = new int[iWidth];
	}

	pObjects = new Object * [iWidth * iHeight];
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(SQUARE_SIZE, SQUARE_SIZE, 1.0f);

	for (int i = 0; i < iWidth * iHeight; i++) {
		int imapType;
		fscanf(filePointer, "%d ", &imapType);

		p_imapType[i / iWidth][i % iWidth] = imapType;

		Vector3 position = Vector3(SQUARE_SIZE/2, SQUARE_SIZE/2, 0.0f);
		position.x += SQUARE_SIZE * (i % iWidth);
		position.y += SQUARE_SIZE * (i / iWidth);

		//0-path, 1-wall, 2-player, 3-friend, 4-hole, 5-target
		if (imapType == 0 || imapType == 1)
		{
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}

		if (imapType == 2)
		{
			//Player
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);

			player = new Player(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(imapType), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale, true);

			printf("Player\n");
		}

		if (imapType == 3)
		{
			//Friend
		}

		if (imapType == 4)
		{
			//Hole
		}

		if (imapType == 5)
		{
			//Target
			pObjects[i] = new Object(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(0), pCamera,
				ResourceManager::GetInstance()->GetShaderById(0), position, rotation, scale);
		}
	}

	fscanf(filePointer, "Star: %f %f %f\n", &star.x, &star.y, &star.y);

	fclose(filePointer);
}

void SceneManager::Update(float deltaTime, unsigned char keyPressed)
{
	player->Key(keyPressed);
}

void SceneManager::Draw()
{
	for (int i = 0; i < iWidth * iHeight; i++)
	{
		pObjects[i]->Draw();
	}

	player->Draw();
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < iWidth * iHeight; i++)
	{
		delete pObjects[i];
	}
	delete pObjects;

	for (int i = 0; i < iHeight; i++)
	{
		delete p_imapType[i];
	}
	delete p_imapType;

	delete player;
	delete pCamera;
}